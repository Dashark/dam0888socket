
#include "H3CServer.h"
#include <fstream>
#include <cassert>
#include <syslog.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
#include <arpa/inet.h>
#include "json.hpp"

using json = nlohmann::json;
#define NB_CONNECTION  5 //listen()函数等待连接队列的最大长度

H3CServer::ClientModel::ClientModel(const std::string &ip, int id): slaveID_(id) {

  assert(slaveID_ > 0);
  ip_ = ip;
  fd_ = -1;
}

H3CServer::ClientModel::~ClientModel() {

}

void H3CServer::ClientModel::write(const std::string &info) {
  /*int i = 0;
  for(auto& bit : outputs_) {
    bit = buf[i];
    i += 1;
  }
  */
}

bool H3CServer::ClientModel::setFileDesc(int fd) {
  fd_ = fd;
  return true;
}

///////////////////////////H3CServer Implement//////////////////////////////////////////////////////
H3CServer::H3CServer(int port):port_(port) {
  assert(port_ > 1024);

}

H3CServer::~H3CServer() {

}

int H3CServer::listenH3C() {
	struct sockaddr_in server_zlmcu = {0};
	/*--- zlmcu的socket连接设置 ---*/
	socket_fd_ = socket (AF_INET, SOCK_STREAM, 0);
	if (socket_fd_ == -1) {
		syslog(LOG_CRIT, "cannot create socket for H3CMCU!\n");
		return socket_fd_;
	}
	syslog (LOG_INFO, "socket of H3CMCU is successed = %d\n", socket_fd_);

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

int H3CServer::clientConnected() {
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
    setClientModel(ip, newfd);  //TODO Jave client....
  }
  delete client;
  return newfd;
}

void H3CServer::createClientModel(const std::string &ip, int id) {
  assert(id > 0);
  ClientModel *iom = new H3CServer::ClientModel(ip, id);
  models_.push_back(iom);
  moditer_ = models_.begin();
}

H3CServer::ClientModel* H3CServer::findClientModel(const std::string &ip) {
  for(ClientModel *io : models_) {
    if(io->equal(ip))
      return io;
  }
  return nullptr;
}

void H3CServer::setClientModel(const std::string &ip, int fd) {
  for(ClientModel *iom : models_) {
    if(iom->equal(ip)) {
      iom->setFileDesc(fd);
    }
  }
}

////////////////////////////////////////////////////////////////
H3CDefine::H3CDefine() {
  std::ifstream i("config.json");
    i >> js_;
}

H3CDefine::~H3CDefine() {
}

//TODO  init H3C cameras
H3CServer* H3CDefine::createServer() {
  if(js_["client"]==""){
   syslog(LOG_CRIT, "failed to load configuration of zlmcu. Process can't run!!!");
    return nullptr;
   }
  std::string str_port=js_["port"];
  int port=std::stoi(str_port);
   if(js_["port"]==""){
    syslog(LOG_ERR, "failed to load Server's port. Process can't run!!!");
    return nullptr;
  }
  H3CServer *server = new H3CServer(port);
  addClientModels(server);
  return server;
}

//TODO this is Java client
void H3CDefine::addClientModels(H3CServer *server) {

   std::string sip=js_["client"]["ip"];
   server->createClientModel(sip.c_str(), 1);
}
