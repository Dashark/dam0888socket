#include "Connection.h"
#include <syslog.h>
#include <cassert>

Connection::Connection() {
times=0;
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
void Connection::notify(const std::string &ip, int id,const uint16_t parameter[],const uint16_t electricityData[],const uint16_t energyData[]){
  if(times>=100) {
    for(Device *dev : devices_)
    {
        if(dev->equalType("electricMeter"))
          dev->update(id,parameter,electricityData,energyData);
    }
    times=0;
    return ;
  }
  times++;
}
