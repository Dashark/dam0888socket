#include "Device.h"

#include <syslog.h>

Device::Device(const char ip[], const char id[]):ip_(ip), id_(id) {

}

void Device::update(int sid, const std::vector<char> &stats) {
  int idx = 0;
  for(char s : stats) {
    for(Operation *oper : opers_) {
      if(oper->equalPort(sid) && oper->equalAddr(idx)) {
        oper->execute(s);
        break; //TODO one state for one operation
      }
    }
    idx += 1;
  }
}

std::string Device::stateStr() const {
  std::string all = "{\"kafkaType\":\"x\",\"data\":{\"deviceid\":\"" + id_ + "\"";
  for(Operation* oper : opers_) {
    all += ",";
    all += oper->stateStr();
  }
  gchar *time_str = NULL;
  //GTimeVal time_val;
  GDateTime *time = NULL;
  time = g_date_time_new_now_local();
  time_str = g_date_time_format(time, "%Y/%m/%d %H:%M:%S");
  all += ",\"timestamp\":\"" + std::string(time_str) + "\"}}";
  g_free(time_str);
  g_date_time_unref(time);
  syslog(LOG_INFO, "Device String : %s", all.c_str());
  return all;
}

void Device::clearOpers() {
  for(Operation* oper : opers_)
    delete oper;
  opers_.clear();
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
  OperationDefine opdef;
  gchar **groups = g_key_file_get_groups(keyFile_, NULL);
  while(*groups != NULL) {
    gchar* id = g_key_file_get_string(keyFile_, *groups, "id", &error);
    gchar* ip = g_key_file_get_string(keyFile_, *groups, "ip", &error);
    Device *dev = new Device(ip, id);
    devs.push_back(dev);
    //TODO create operators of device.
    char opfile[64];
    g_snprintf(opfile, 64, "op_%s.ini", (*groups));
    syslog(LOG_INFO, "Current Operation Conf : %s", opfile);
    std::vector<Operation*> ops = opdef.create(opfile);
    dev->setOpers(ops);
    groups += 1;
  }
  return devs;
}

