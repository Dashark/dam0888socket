#ifndef _ZLSERVER_H_
#define _ZLSERVER_H_

#include "Connection.h"

#include <modbus.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <glib.h>
#include "json.hpp"
using json = nlohmann::json;

class ZLServer : public Connection {
 private:
/////////////////////////////////////这是io模块的提前声明///////////////////////////////////////////////////////////////////
class IOModel {
 public:
  const int slaveID_;
  std::vector<char> inputs_, outputs_;
  uint16_t *notifys_;
  std::string ip_;
  int fd_;
  modbus_t *ctx_;
 public:
  IOModel(const std::string &ip, int id, int ins, int outs);
  ~IOModel();
  bool equal(const std::string &ip) const {
    return ip_ == ip ? true : false;
  }
  /*bool equal(int fd) const {
    return fd_ == fd ? true : false;
    }*/
  bool equal(int id) const {
    return slaveID_ == id ? true : false;
  }
  bool read(modbus_t *ctx);
  void write(modbus_t *ctx,int addr,int state);
  bool setFileDesc(int fd);
 private:
  int modbusRead(modbus_t *ctx, uint8_t buf[], int size);
  int modbusWrite(modbus_t *ctx,int addr,int state);
};

////////////////////////////////////这是智能电表的提前声明//////////////////////////////////////////////////////////////////
class SmartMeter {
 public:
  const int slaveID_;
  uint16_t *parameter_, *electricityData_, *energyData_,*notifys_;
  std::string ip_;
  int fd_;

 public:
  SmartMeter(const std::string &ip, int id);
  ~SmartMeter();
  bool equal(const std::string &ip) const {
    return ip_ == ip ? true : false;
  }
  bool equal(int id) const {
    return slaveID_ == id ? true : false;
  }
  bool read(modbus_t *ctx);
  bool setFileDesc(int fd);
 private:
  int modbusRead(modbus_t *ctx, uint16_t buf[], int start_,int size);
};

////////////////////////////////////这是卓蓝server的提前声明//////////////////////////////////////////////////////////////
  const int port_;
  int socket_fd_;
  sockaddr_in sockaddr_;
  std::vector<IOModel*> models_;
  std::vector<IOModel*>::iterator moditer_;

  std::vector<SmartMeter*> sMeters_;
  std::vector<SmartMeter*>::iterator smteriter_;

  modbus_t *modbus_ctx_;
 public:
  ZLServer(int port);
  ~ZLServer();
  int listenZL();
  int clientConnected();
  bool readAll();
  bool write(const std::string &ip,int id,int addr,int state);
  void createIOModel(const std::string &ip, int id, int ins, int outs);
  void createSmartMeter(const std::string &ip, int id);
 private:
  IOModel* findIOModel(const std::string &ip);
  IOModel* findIOModel(const std::string &ip,int id);
  void setIOModel(const std::string &ip, int fd);

  SmartMeter* findSmartMeter(const std::string &ip);
  SmartMeter* findSmartMeter(const std::string &ip,int id);
  void setSmartMeter(const std::string &ip, int fd);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ZLDefine {
 private:
  json js_;
 public:
  ZLDefine();
  ~ZLDefine();
  ZLServer* createServer();
 private:
  void addIOModels(ZLServer *server);
  void addSmartMeters(ZLServer *server);
};

#endif
