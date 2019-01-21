#ifndef _DEVICE_H_
#define _DEVICE_H_
class Connection;
#include <string>
#include <vector>
#include <glib.h>
#include "Operation.h"
#include "Broker.h"
#include "Messager.hpp"
class ZLServer;
class Device {
protected:
  const std::string ip_;
  const std::string id_;
  const std::string type_;
  const std::string relationship_;
  std::vector<Operation*> opers_;
  std::vector<Broker*> brokers_;
  std::vector<Messager*> messagers_;
  ZLServer* server_;
 public:
  Device(const char ip[], const char id[],const char type[],const char relationship[]);
  ~Device();
  ////////////////////////////////////////////
  Device* equalIP(const std::string &ip) {
    return ip_ == ip ? this : nullptr;
  }
  Device* equalID(const std::string &id) {
    return id_ == id ? this : nullptr;
  }

  Device* equalType(const std::string &type) {
    return type_ == type ? this : nullptr;
  }
  void setServer(ZLServer* server) {
    server_=server;
  }
  void setOpers(std::vector<Operation*> &opers) {
    clearOpers();
    opers_ = opers;
  }
  void attach(Broker *brok) {
    if(brok != nullptr)
      brokers_.push_back(brok);
  }
  void attach(Messager *mes) {
    if(mes != nullptr)
      messagers_.push_back(mes);
  }

  //////////////////////////////////////////////////////
  virtual void update(int sid, const uint16_t stats[]);

  std::string stateStr();
  std::string stateStr(Messager *mes);
  std::string stateStrSmartMeter(Messager *mes);
 private:
  void clearOpers();
};
///////////////////////////////////////////下面是闪烁灯的创建////////////////////////////////////////////////////////////////////////////////

  class AGVLight:public Device{
  private:

  public:
    AGVLight(const char ip[], const char id[],const char type[],const char relationship[]);
    ~AGVLight();
    virtual void update(int sid, const uint16_t stats[]);
  };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SmartMeter:public Device{
private:
public:
  SmartMeter(const char ip[], const char id[],const char type[],const char relationship[]);
  ~SmartMeter();
  virtual void update(int sid, const uint16_t stats[]);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DeviceFactory {
 private:
  GKeyFile *keyFile_;
  KafkaDefine *kafDef_;
 public:
  DeviceFactory();
  ~DeviceFactory();

  std::vector<Device*> createDevices();
};

#endif
