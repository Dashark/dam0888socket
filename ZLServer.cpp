#include "ZLServer.h"

#include <cassert>
#include <syslog.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

#define NB_CONNECTION  5 //listen()函数等待连接队列的最大长度

ZLServer::IOModel::IOModel(const std::string &ip, int id, int ins, int outs): slaveID_(id), inputs_(ins), outputs_(outs) {

  assert(slaveID_ > 0);
  ip_ = ip;
}

ZLServer::IOModel::~IOModel() {

}

bool ZLServer::IOModel::read(modbus_t *ctx) {
  if(fd_ == -1)
    return false;
  uint8_t *buf = new uint8_t[inputs_.size()];
  if(!modbusRead(ctx, buf, inputs_.size()))
    return false;
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

bool ZLServer::IOModel::modbusRead(modbus_t *ctx, uint8_t buf[], int size) {
  int ret = 0;
  ret = modbus_set_socket(ctx, fd_); //设置modbus的文件描述编号
  if(ret == -1) {
    syslog(LOG_ERR, "modbus_set_socket failed! (%s)", strerror(errno));
    return false;
  }
  ret = modbus_set_slave(ctx, slaveID_);
  ret = modbus_read_input_bits(ctx, 0, size, buf);
  return true;
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
		fprintf (stderr, "set debug failed: %s\n", modbus_strerror (errno));
		modbus_free (modbus_ctx_);
	}
#endif

    /* set default slave number in the context */
  if(modbus_ctx_ != NULL) {
    /* set timeout for response */
    if (modbus_set_response_timeout (modbus_ctx_, 0, 35000) == -1) {
		  syslog (LOG_CRIT, "set timeout failed: %s\n", modbus_strerror (errno));
      modbus_free (modbus_ctx_);
      modbus_ctx_ = NULL;
    }
  }
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
  return socket_fd_;
}

int ZLServer::clientConnected() {
  if(socket_fd_ == -1)
    return -1;  //wrong server
  struct sockaddr_in *client = new struct sockaddr_in;
  socklen_t len = sizeof(struct sockaddr_in);
	int newfd = accept (socket_fd_, (struct sockaddr*)&client, &len);
	if (newfd == -1) {
    syslog (LOG_ERR, "Server accept error (fd = %d)", socket_fd_);
	} else {
    char *ip = inet_ntoa(client->sin_addr);
		syslog (LOG_INFO, "fd = %d, New connection from %s:%d on socket %d\n",
				socket_fd_, ip, client->sin_port, newfd);
    setIOModel(ip, newfd);
  }
  return newfd;
}

bool ZLServer::readAll() {
  for(IOModel* mod : models_) {
    bool ret = mod->read(modbus_ctx_);
    if(ret)
      //notify(mod->ip, mod.id, mod.addr);
      return ret;
  }
  return false;
}

void ZLServer::createIOModel(const std::string &ip, int id, int ins, int outs) {
  IOModel *iom = new ZLServer::IOModel(ip, id, ins, outs);
  models_.push_back(iom);
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
}

////////////////////////////////////////////////////////////////
ZLDefine::ZLDefine() {
  keyFile_ = g_key_file_new();
}

ZLDefine::~ZLDefine() {
  g_key_file_free(keyFile_);
}

ZLServer* ZLDefine::createServer() {
  GError *error = nullptr;
  if(!g_key_file_load_from_file(keyFile_, "zlmcu.ini", G_KEY_FILE_NONE, &error)) {
    syslog(LOG_CRIT, "failed to load zlmcu.ini. Process can't run!!! (%s)", error->message);
    return nullptr;
  }

  int port = g_key_file_get_integer(keyFile_, "Connection", "port", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Server's port. Process can't run!!!");
    return nullptr;
  }
  ZLServer *server = new ZLServer(port);
  addIOModels(server);
  return server;
}

void ZLDefine::addIOModels(ZLServer *server) {
  assert(keyFile_ != nullptr);
  GError *error = nullptr;
  int ins = g_key_file_get_integer(keyFile_, "IOModel", "inputs", &error);
  int outs = g_key_file_get_integer(keyFile_, "IOModel", "outputs", &error);
  int mods = g_key_file_get_integer(keyFile_, "IOModel", "models", &error);
  gchar *ip = g_key_file_get_string(keyFile_, "IOModel", "ip", &error);
  for(int i = 0; i < mods; i++) {
    server->createIOModel(ip, i+1, ins, outs);
  }
  g_free(ip);
}
