
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
#include "Device.h"
using json = nlohmann::json;
#define NB_CONNECTION  5 //listen()函数等待连接队列的最大长度
///////////////////////////////////////这一部分是io模块的server方法/////////////////////////////////////////////////////////////
ZLServer::IOModel::IOModel(const std::string &ip, int id, int ins, int outs): slaveID_(id), inputs_(ins), outputs_(outs) {

  notifys_=new uint16_t[ins];
  assert(slaveID_ > 0);
  ip_ = ip;
  fd_ = -1;
}

ZLServer::IOModel::~IOModel() {

}

bool ZLServer::IOModel::read(modbus_t *ctx) {
  if(fd_ == -1)
    return false;
  uint8_t *buf = new uint8_t[sizeof(notifys_)];
  if(modbusRead(ctx, buf, sizeof(notifys_)) <= 0) {
    return false;
  }
  bool ret = false;
  for(int i=0;i<sizeof(notifys_);i++) {
    if(notifys_[i] != buf[i]) {
      notifys_[i] = buf[i];
      ret = true;
    }
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
    syslog(LOG_INFO, "IO模块读取失败,请检查接线和配置");
    syslog(LOG_ERR, "modbus_read_input_bits failed! (%s)", strerror(errno));
    return ret;
  }
  return ret;
}

void ZLServer::IOModel::write(modbus_t *ctx,int addr,int state) {
  if(fd_ == -1)
    return ;
  syslog(LOG_INFO,"id:%d addr:%d  state:%d",slaveID_,addr,state);
  modbusWrite(ctx,addr,state);
}

int ZLServer::IOModel::modbusWrite(modbus_t *ctx, int addr, int state) {
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
  //ret = modbus_write_bits(ctx, 0, size, buf);
  ret=modbus_write_bit(ctx,addr,state);
  if(ret == -1) {
    syslog(LOG_INFO, "IO模块写入失败,请检查接线和配置");
    syslog(LOG_ERR, "modbus_write_bit failed! (%s)", strerror(errno));
    return ret;
  }
  return ret;
}

bool ZLServer::IOModel::setFileDesc(int fd) {
  fd_ = fd;
  return true;
}
////////////////////////////智能电表的server模块/////////////////////////////////////////////////////////////////////////////
ZLServer::SmartMeter::SmartMeter(const std::string &ip, int id): slaveID_(id) {

  assert(slaveID_ > 0);
  ip_ = ip;
  fd_ = -1;
  parameter_= new uint16_t[2];
  electricityData_= new uint16_t[20];
  energyData_= new uint16_t[2];
  notifys_=new uint16_t[24];
}

ZLServer::SmartMeter::~SmartMeter() {

}

bool ZLServer::SmartMeter::read(modbus_t *ctx) {
  if(fd_ == -1)
    return false;
  uint16_t *buf1 = new uint16_t[2];
  if(modbusRead(ctx,buf1,0x06,2) > 0){
    for(int i=0;i<2;i++) notifys_[i]=buf1[i];delete[] buf1;buf1=NULL;
  }
  else return false;
  uint16_t *buf2 = new uint16_t[20];
  if(modbusRead(ctx, buf2,0x2006, 20) > 0) {
  for(int i=0;i<20;i++) notifys_[i+2]=buf2[i];delete[] buf2;buf2=NULL;
  }
  else return false;
  uint16_t *buf3 = new uint16_t[2];
  if(modbusRead(ctx, buf3, 0x401E, 2) > 0) {
    for(int i=0;i<2;i++) notifys_[i+22]=buf3[i];delete[] buf3;buf3=NULL;
  }
  else return false;
  if(modbusRead(ctx,parameter_,0x06,2) <= 0) {
    return false;
  }
  //uint16_t *buf2 = new uint16_t[20];
  if(modbusRead(ctx, electricityData_,0x2006, 20) <= 0) {
    return false;
  }
  //uint16_t *buf3 = new uint16_t[2];
  if(modbusRead(ctx, energyData_, 0x401E, 2) <= 0) {
    return false;
  }
  return true;
}

int ZLServer::SmartMeter::modbusRead(modbus_t *ctx, uint16_t buf[], int start_,int size) {
  assert(ctx != nullptr && fd_ != -1);
  int ret = 0;
  ret = modbus_set_socket(ctx, fd_); //设置modbus的文件描述编号
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_set_socket failed! (%s)", strerror(errno));
    return ret;
  }
  ret = modbus_set_slave(ctx, slaveID_);
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_set_slave failed! (%s)", strerror(errno));
    return ret;
  }
  ret = modbus_read_registers (ctx,start_,size, buf);
  if(ret == -1) {
    syslog(LOG_INFO, "电表模块读取失败,请检查接线和配置");
    syslog(LOG_ERR, "modbus_read_registers failed! (%s)", strerror(errno));
    return ret;
  }
  return ret;
}

bool ZLServer::SmartMeter::setFileDesc(int fd) {
  fd_ = fd;
  return true;
}

///////////////////////////ZLServer Implement/////////////////////////////////////////////////////////////////////////////
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
  smteriter_=sMeters_.end();
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
    setSmartMeter(ip, newfd);
  }
  delete client;
  return newfd;
}

bool ZLServer::readAll() {
    bool ret = false;
  if(models_.size()<1) return ret;
  moditer_ = moditer_ == models_.end() ? models_.begin() : moditer_;
  IOModel* mod = (*moditer_);
  if(mod != nullptr) {
    mod->ctx_=modbus_ctx_;
    usleep(4000);
    ret = mod->read(modbus_ctx_);

    if(ret)
      {
        notify(mod->ip_, mod->slaveID_, mod->notifys_);
        //writenotify(mod->ip_, mod->slaveID_, mod->writenotify_);
      }
    ++moditer_;  //point to next model

  }
  if(sMeters_.size()<1) return ret;
  smteriter_ = smteriter_ == sMeters_.end() ? sMeters_.begin() : smteriter_;
    SmartMeter* sm = (*smteriter_);
  if(sm != nullptr) {
    usleep(4000);
    ret = sm->read(modbus_ctx_);
    if(ret)
     notify(sm->ip_, sm->slaveID_, sm->notifys_);
    ++smteriter_;  //point to next model

  }
  return ret;
}

bool ZLServer::write(const std::string &ip,int id,int addr,int state){
  IOModel* mod = findIOModel(ip,id);
  usleep(4000);
  mod->write(modbus_ctx_,addr,state);
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

ZLServer::IOModel* ZLServer::findIOModel(const std::string &ip,int id) {
  for(IOModel *io : models_) {
    if(io->equal(ip)&&io->equal(id))
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

void ZLServer::createSmartMeter(const std::string &ip, int id) {
  assert(id > 0);
  SmartMeter *sm = new ZLServer::SmartMeter(ip, id);
  sMeters_.push_back(sm);
  smteriter_=sMeters_.begin();
}

ZLServer::SmartMeter* ZLServer::findSmartMeter(const std::string &ip) {
  for(SmartMeter *sm : sMeters_) {
    if(sm->equal(ip))
      return sm;
  }
  return nullptr;
}

ZLServer::SmartMeter* ZLServer::findSmartMeter(const std::string &ip,int id) {
  for(SmartMeter *sm : sMeters_) {
    if(sm->equal(ip))
      return sm;
  }
  return nullptr;
}

void ZLServer::setSmartMeter(const std::string &ip, int fd) {
  for(SmartMeter *sm : sMeters_) {
    if(sm->equal(ip)) {
      sm->setFileDesc(fd);
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
  addSmartMeters(server);
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

void ZLDefine::addSmartMeters(ZLServer *server) {
  std::string sip=js_["zlmcu"]["ip"];
  for (auto& element : js_["devices"]){
  std::string str_type=element["type"];
  char* type=(char*)str_type.c_str();
  if(strcmp(type,"electricMeter")==0)
  {
    for(auto& ele :element["operate"])
    {
    std::string str_port=ele["ioport"];
    int id=std::stoi(str_port);
    //syslog(LOG_INFO,"电表在此处创建id:%d",id);
    server->createSmartMeter(sip,id);
    }
  }
}
}
