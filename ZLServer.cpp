
#include "ZLServer.h"
#include <fstream>
#include <cassert>
#include <syslog.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>
#include "json.hpp"
#include "ElectricMeter.h"
using json = nlohmann::json;
#define NB_CONNECTION  5 //listen()函数等待连接队列的最大长度

ZLServer::IOModel::IOModel(const std::string &ip, int id, int ins, int outs): slaveID_(id), inputs_(ins), outputs_(outs) {

  assert(slaveID_ > 0);
  ip_ = ip;
  fd_ = -1;
}

ZLServer::IOModel::~IOModel() {

}

bool ZLServer::IOModel::read(modbus_t *ctx) {
  if(fd_ == -1)
    return false;
    //这里是电表数据的接入点
    int newfd=fd_;
    ElectricMeter *em=new ElectricMeter(9,newfd,ctx);
    em->creatElectricMeter();

  uint8_t *buf = new uint8_t[inputs_.size()];
  if(modbusRead(ctx, buf, inputs_.size()) <= 0) {
    return false;
  }

  int i = 0;
  bool ret = false;
  for(auto& bit : inputs_) {
    if(bit != buf[i]) {
      bit = buf[i];
      ret = true;
    }
    i += 1;
  }
  delete[] buf;
  return ret;
}

int ZLServer::IOModel::modbusRead(modbus_t *ctx, uint8_t buf[], int size) {
  assert(ctx != nullptr && fd_ != -1);
  int ret = 0;
  ret = modbus_set_socket(ctx, fd_); //设置modbus的文件描述编号
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_set_socket failed! (%s)", strerror(errno));
    return ret;
  }

  ret = modbus_set_slave(ctx, slaveID_);
  //printf("%d\n", slaveID_);
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_set_slave failed! (%s)", strerror(errno));
    return ret;
  }
  ret = modbus_read_input_bits(ctx, 0, size, buf);
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_read_input_bits failed! (%s)", strerror(errno));
    return ret;
  }
  return ret;
}

void ZLServer::IOModel::write(modbus_t *ctx) {
  /*int i = 0;
  for(auto& bit : outputs_) {
    bit = buf[i];
    i += 1;
  }
  */
}

bool ZLServer::IOModel::modbusWrite(modbus_t *ctx, char buf[], int size) {
  return false;
}

bool ZLServer::IOModel::setFileDesc(int fd) {
  fd_ = fd;
  return true;
}

///////////////////////////ZLServer Implement//////////////////////////////////////////////////////
ZLServer::ZLServer(int port):port_(port) {
  assert(port_ > 1024);
	modbus_ctx_ = modbus_new_rtu ("/dev/ttyUSB0", 9600, 'N', 8, 1); //波特率9600,比特位8，校验位1，无等价位

#ifdef DEBUG
	/* set debug flag of the context */
	if (modbus_set_debug (modbus_ctx_, 1) == -1) {
		syslog (LOG_DEBUG, "set debug failed: %s\n", modbus_strerror (errno));
		modbus_free (modbus_ctx_);
	}
#endif

    /* set default slave number in the context */
  if(modbus_ctx_ != NULL) {
    /* set timeout for response */
    if (modbus_set_response_timeout (modbus_ctx_, 0, 150000) == -1) {
		  syslog (LOG_CRIT, "set timeout failed: %s\n", modbus_strerror (errno));
      modbus_free (modbus_ctx_);
      modbus_ctx_ = NULL;
    }
  }
}

ZLServer::~ZLServer() {

}

int ZLServer::listenZL() {
	struct sockaddr_in server_zlmcu = {0};
	/*--- zlmcu的socket连接设置 ---*/
	socket_fd_ = socket (AF_INET, SOCK_STREAM, 0);
	if (socket_fd_ == -1) {
		syslog(LOG_CRIT, "cannot create socket for ZLMCU!\n");
		return socket_fd_;
	}
	syslog (LOG_INFO, "socket of ZLMCU is successed = %d\n", socket_fd_);

	server_zlmcu.sin_family = AF_INET;
	server_zlmcu.sin_addr.s_addr = inet_addr("0.0.0.0"); //INADDR_ANY
	server_zlmcu.sin_port = htons (port_);

	if (bind (socket_fd_, (struct sockaddr*)&server_zlmcu, sizeof(server_zlmcu)) != 0) {
		syslog (LOG_CRIT, "cannot bind socket:");
		close (socket_fd_);
    socket_fd_ = -1;
		return socket_fd_;
	}

	if (listen (socket_fd_, NB_CONNECTION) != 0) {
		syslog (LOG_CRIT, "cannot listen on socket!\n");
		close (socket_fd_);
    socket_fd_ = -1;
		return socket_fd_;
	}
  moditer_ = models_.end();
  return socket_fd_;
}

int ZLServer::clientConnected() {
  if(socket_fd_ == -1)
    return -1;  //wrong server
  struct sockaddr_in *client = new struct sockaddr_in;
  socklen_t len = sizeof(struct sockaddr_in);
	int newfd = accept (socket_fd_, (struct sockaddr*)client, &len);
	if (newfd == -1) {
    syslog (LOG_ERR, "Server accept error (fd = %d)", socket_fd_);
	} else {
    char *ip = inet_ntoa(client->sin_addr);
		syslog (LOG_INFO, "fd = %d, New connection from %s:%d on socket %d\n",
				socket_fd_, ip, client->sin_port, newfd);
    setIOModel(ip, newfd);
  }
  delete client;
  return newfd;
}

bool ZLServer::readAll() {
  moditer_ = moditer_ == models_.end() ? models_.begin() : moditer_;
  bool ret = false;
  IOModel* mod = (*moditer_);
  if(mod != nullptr) {
    ret = mod->read(modbus_ctx_);
    if(ret)
      notify(mod->ip_, mod->slaveID_, mod->inputs_);
    ++moditer_;  //point to next model

    //下面是执行电表的方法

  }

  return ret;
}

void ZLServer::createIOModel(const std::string &ip, int id, int ins, int outs) {
  assert(id > 0);
  IOModel *iom = new ZLServer::IOModel(ip, id, ins, outs);
  models_.push_back(iom);
  moditer_ = models_.begin();
}

ZLServer::IOModel* ZLServer::findIOModel(const std::string &ip) {
  for(IOModel *io : models_) {
    if(io->equal(ip))
      return io;
  }
  return nullptr;
}

void ZLServer::setIOModel(const std::string &ip, int fd) {
  for(IOModel *iom : models_) {
    if(iom->equal(ip)) {
      iom->setFileDesc(fd);
    }
  }
  //modbus_set_socket(modbus_ctx_, fd);
}

////////////////////////////////////////////////////////////////
ZLDefine::ZLDefine() {
  std::ifstream i("config.json");
    i >> js_;
}

ZLDefine::~ZLDefine() {
}


ZLServer* ZLDefine::createServer() {
  if(js_["zlmcu"]==""){
   syslog(LOG_CRIT, "failed to load configuration of zlmcu. Process can't run!!!");
    return nullptr;
   }
  std::string str_port=js_["port"];
  int port=std::stoi(str_port);
   if(js_["port"]==""){
    syslog(LOG_ERR, "failed to load Server's port. Process can't run!!!");
    return nullptr;
  }
  ZLServer *server = new ZLServer(port);
  addIOModels(server);
  return server;
}

void ZLDefine::addIOModels(ZLServer *server) {
  std::string str_ins=js_["zlmcu"]["inputs"];
  int ins=std::stoi((std::string)str_ins);
  std::string str_outs=js_["zlmcu"]["outputs"];
  int outs=std::stoi(str_outs);
  std::string str_mods=js_["zlmcu"]["models"];
  int mods=std::stoi(str_mods);
   std::string sip=js_["zlmcu"]["ip"];
  for(int i = 0; i < mods; i++) {
    server->createIOModel(sip.c_str(), i+1, ins, outs);
  }
}
