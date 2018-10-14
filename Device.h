#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <vector>
#include <glib.h>
#include "Operation.h"
#include "Broker.h"

class Device {
 private:
  const std::string ip_;
  const std::string id_;
  std::vector<Operation*> opers_;
  std::vector<Broker*> brokers_;
 public:
  Device(const char ip[], const char id[]);
  ////////////////////////////////////////////
  Device* equalIP(const std::string &ip) {
    return ip_ == ip ? this : nullptr;
  }
  Device* equalID(const std::string &id) {
    return id_ == id ? this : nullptr;
  }
  void setOpers(std::vector<Operation*> &opers) {
    clearOpers();
    opers_ = opers;
  }
  //////////////////////////////////////////////////////
  void update(int sid, const std::vector<char> &stats);
 private:
  void clearOpers();
};

class DeviceFactory {
 private:
  GKeyFile *keyFile_;
 public:
  DeviceFactory();
  ~DeviceFactory();

  std::vector<Device*> createDevices();
};

#endif
