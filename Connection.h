#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <vector>
#include <string>
#include "Device.h"

class Connection {
 private:
  std::vector<Device*> devices_;
  int times;
 public:
  Connection();
  void attach(Device *device);
  void detach(Device *device);
  void notify(const std::string &ip, int id,
              const std::vector<char> &buf);
  void notify(const std::string &ip, int id,
              const uint16_t parameter[],const uint16_t electricityData[],const uint16_t energyData[]);
};

#endif
