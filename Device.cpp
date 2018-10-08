#include "Device.h"

#include <syslog.h>

Device::Device(const char ip[], const char id[]):ip_(ip), id_(id) {

}

void Device::update(int sid, const std::vector<char> &stats) {

}

///////////////////////////////////////////////////////////////////////
DeviceFactory::DeviceFactory() {
  keyFile_ = g_key_file_new();
}

DeviceFactory::~DeviceFactory() {
  g_key_file_free(keyFile_);
}

std::vector<Device*> DeviceFactory::createDevices() {
  GError *error = NULL;
  std::vector<Device*> devs;
  if(!g_key_file_load_from_file(keyFile_, "devices.ini", G_KEY_FILE_NONE, &error)) {
    syslog(LOG_CRIT, "Device configure failed! (%s)", error->message);
    return devs; //TODO sth will do
  }
  gchar **groups = g_key_file_get_groups(keyFile_, NULL);
  while(groups != NULL) {
    gchar* id = g_key_file_get_string(keyFile_, *groups, "id", &error);
    gchar* ip = g_key_file_get_string(keyFile_, *groups, "ip", &error);
    Device *dev = new Device(ip, id);
    devs.push_back(dev);
    //TODO create operators of device.
  }
  return devs;
}
