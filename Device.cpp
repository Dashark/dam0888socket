#include "Device.h"

Device::Device(const char ip[], const char id[]):ip_(ip), id_(id) {

}

void Device::update(int sid, int addr, const std::vector<char> &stats) {

}

///////////////////////////////////////////////////////////////////////
DeviceFactory::DeviceFactory() {
  keyFile_ = g_key_file_new();
}

DeviceFactory::~DeviceFactory() {
  g_key_file_free(keyFile_);
}

std::vector<Device*> createDevices() {
  std::vector<Device*> devs;
  return devs;
}
