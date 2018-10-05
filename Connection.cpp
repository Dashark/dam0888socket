#include "Connection.h"

#include <assert>

Connection::Connection() {

}

void Connection::attach(Device *device) {
  assert(device != NULL);
  devices_.push_back(device);
}

void Connection::detach(Device *device) {

}

void Connection::notify() {
  for(auto dev : devices_) {
    dev->update();
  }
}
