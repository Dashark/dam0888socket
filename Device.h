#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <vector>
#include <glib.h>

class Device {
 private:
  const std::string ip_;
  const std::string id_;
 public:
  Device(const char ip[], const char id[]);
  Device* equalIP(const std::string &ip) const {
    return ip_ == ip ? true :false;
  }
  Device* equalID(const std::string &id) const {
    return id_ == id ? true : false;
  }
  void update(int sid, int addr, const std::vector<char> &stats);
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
