#include "Connection.h"

#include <cassert>

Connection::Connection() {

}

void Connection::attach(Device *device) {
  assert(device != nullptr);
  devices_.push_back(device);
}

void Connection::detach(Device *device) {

}

void Connection::notify(const std::string &ip, int id,
                        const std::vector<char> &buf) {
  for(Device *dev : devices_) {
    if(dev->equalIP(ip))
      dev->update(id, buf);
  }
}
