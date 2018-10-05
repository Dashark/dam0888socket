#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>

class Device {
 private:
  const std::string id_;
 public:
  Device(char id[]);
  void update();
};

#endif
