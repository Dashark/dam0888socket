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

void Connection::notify() {
  for(Device *dev : devices_) {
    dev->update();
  }
}
