#ifndef _H3CSERVER_H_
#define _H3CSERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <glib.h>
#include "json.hpp"
using json = nlohmann::json;

class H3CServer {
 private:
class ClientModel {
 public:
  const int slaveID_;
  std::string ip_;
  int fd_;

 public:
  ClientModel(const std::string &ip, int id);
  ~ClientModel();
  bool equal(const std::string &ip) const {
    // return ip_ == ip ? true : false;
    return true;
  }
  /*bool equal(int fd) const {
    return fd_ == fd ? true : false;
    }*/
  bool equal(int id) const {
    // return slaveID_ == id ? true : false;
    return true;
  }

  void writeInfo(const std::string &info);
  bool setFileDesc(int fd);

};

  const int port_;
  int socket_fd_;
  sockaddr_in sockaddr_;
  std::vector<ClientModel*> models_;
  std::vector<ClientModel*>::iterator moditer_;

 public:
  H3CServer(int port);
  ~H3CServer();
  int listenH3C();
  int clientConnected();
  //bool readAll();  //TODO it's callback func
  bool write(const std::string &info);
  void createClientModel(const std::string &ip, int id);
  void setClientModel(const std::string &ip, int fd);
 private:
  ClientModel* findClientModel(const std::string &ip);

};

class H3CDefine {
 private:
  json js_;
  void initH3C(H3CServer *server);
  void alarmH3C(int id);
 public:
  H3CDefine();
  ~H3CDefine();
  H3CServer* createServer();
 private:
  void addClientModels(H3CServer *server);
};

#endif
