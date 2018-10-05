#include "ZLServer.h"

#include <assert>

ZLServer::IOModel::IOModel(int id, int ins, int outs):slaveID_(id), inputs_(ins), outputs_(outs) {

  assert(slaveID_ > 0);

}

IOModel::~IOModel() {

}

bool ZLServer::IOModel::identify(int id) {
  if(id_ == id)
    return true;

  return false;
}

bool ZLServer::IOModel::read(modbus_t *ctx) {
  if(fd_ == -1)
    return false;
  char buf[inputs_.size()];
  if(!modbusRead(buf, inputs_.size()))
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
  return ret;
}

bool ZLServer::IOModel::modbusRead(char buf[], int size) {
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
  int i = 0;
  for(auto& bit : outputs_) {
    bit = buf[i];
    i += 1;
  }
}

bool ZLServer::IOModel::modbusWrite(char buf[], int size) {
  return false;
}

ZLServer::ZLServer(int port):port_(port) {
  assert(port_ > 1024);
	modbus_ctx_ = modbus_new_rtu ("/dev/ttyUSB0", 9600, 'N', 8, 1); //波特率9600,比特位8，校验位1，无等价位

#ifdef DEBUG
	/* set debug flag of the context */
	if (modbus_set_debug (modbus_ctx, 1) == -1) {
		fprintf (stderr, "set debug failed: %s\n", modbus_strerror (errno));
		modbus_free (modbus_ctx_);
	}
#endif

    /* set default slave number in the context */
  if(modbus_ctx_ != NULL) {
    /* set timeout for response */
    if (modbus_set_response_timeout (modbus_ctx, 0, 35000) == -1) {
		  syslog (LOG_CRIT, "set timeout failed: %s\n", modbus_strerror (errno));
      modbus_free (modbus_ctx_);
      modbus_ctx_ = NULL;
    }
  }
}

int ZLServer::listen() {
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

int clientConnected(int fd) {
  if(socket_fd_ != fd)
    return -1;  //wrong server
  struct sockaddr_in *client = new struct sockaddr_in;
	int newfd = accept (socket_fd_, (struct sockaddr*)&client, &len);
	if (newfd == -1) {
    syslog (LOG_ERR, "Server accept error (fd = %d)", socket_fd_);
	} else {
		syslog (LOG_INFO, "fd = %d, New connection from %s:%d on socket %d\n",
				socket_fd_, inet_ntoa(client->sin_addr), client->sin_port, newfd);
  }
    return newfd;
}

bool ZLServer::readAll() {
  for(IOModel* mod : models_) {
    bool ret = mod->read(modbus_ctx_);
    if(ret)
      notify(mod.ip, mod.id, mod.addr);
  }
}
