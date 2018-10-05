#ifndef _ZLSERVER_H_
#define _ZLSERVER_H_

#include "Connection.h"

#include <modbus.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class ZLServer : public Connection {
 private:
class IOModel {
 private:
  const int slaveID_;
  std::vector<char> inputs_, outputs_;
  std::string ip_;
  int fd_;

 public:
  IOModel(const char ip[], int id, int ins, int outs);
  ~IOModel();
  bool equal(const char ip[]) const;
  bool equal(int fd) const;
  bool equal(int id);
  bool read(modbus_t *ctx);
  void write(modbus_t *ctx);
 private:
  bool modbusRead(char buf[], int size);
  bool modbusWrite(char buf[], int size);
};

  const int port_;
  int socket_fd_;
  sockaddr_in sockaddr_;
  std::vector<IOModel*> models_;
  modbus_t *modbus_ctx_;
 public:
  ZLServer(int port);
  ~ZLServer();
  int listen();
  int clientConnected(int fd);
  bool readAll();
};



#endif
