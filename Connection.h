#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <vector>
#include <string>
#include "Device.h"

class Connection {
 private:
  std::vector<Device*> devices_;
 public:
  Connection();
  void attach(Device *device);
  void detach(Device *device);
  void notify(const std::string &ip, int id,
              const std::vector<char> &buf);
};

#endif
