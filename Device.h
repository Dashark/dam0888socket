#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <vector>
#include <glib.h>
#include "Operation.h"
#include "Broker.h"
#include "Messager.hpp"

class Device {
 private:
  const std::string ip_;
  const std::string id_;
  const std::string type_;
  std::vector<Operation*> opers_;
  std::vector<Broker*> brokers_;
  std::vector<Messager*> messagers_;
 public:
  Device(const char ip[], const char id[],const char type[]);
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
  void update(int sid, const uint16_t stats[]);
  std::string stateStr();
  std::string stateStr(Messager *mes);
  std::string stateStrSmartMeter(Messager *mes);
 private:
  void clearOpers();
};

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
