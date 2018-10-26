#include "Device.h"

#include <syslog.h>
#include <cassert>
Device::Device(const char ip[], const char id[]):ip_(ip), id_(id) {

}

Device::~Device() {
  clearOpers();
}

void Device::update(int sid, const std::vector<char> &stats) {
  int idx = 0;
  bool newst = false;
  for(char s : stats) {
    for(Operation *oper : opers_) {
      if(oper->equalPort(sid) && oper->equalAddr(idx)) {
        newst |= oper->execute(s);
        break; //TODO one state for one operation
      }
    }
    idx += 1;
  }
  if(newst) {
    for(Broker *bk : brokers_) {
      if(bk != nullptr) {
        std::string st = stateStr();
        if(!st.empty())
          bk->write(st);
      }
    }
  }
}

std::string Device::stateStr() {
  std::string all = "{\"kafkaType\":\"x\",\"data\":{\"mpos\":\"" + id_ + "\"";
  for(Operation* oper : opers_) {
    all += ",";
    assert(oper != nullptr);
    all += oper->stateStr();
  }

  gchar *time_str = NULL;
  //GTimeVal time_val;
  GDateTime *time = NULL;
  time = g_date_time_new_now_local();
  time_str = g_date_time_format(time, "%Y/%m/%d %H:%M:%S");
  all += ",\"time\":\"" + std::string(time_str) + "\"}}";
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
  kafDef_ = new KafkaDefine();
}

DeviceFactory::~DeviceFactory() {
  g_key_file_free(keyFile_);
  delete kafDef_;
}

std::vector<Device*> DeviceFactory::createDevices() {
  GError *error = NULL;
  kafDef_->load();
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
    gchar* type = g_key_file_get_string(keyFile_, *groups, "type", &error);
    Device *dev = new Device(ip, id);
    Broker *bro = kafDef_->getBroker(id);
    dev->attach(bro);
    devs.push_back(dev);

    std::vector<Operation*> ops = opdef.create((*groups), type);
    dev->setOpers(ops);
    groups += 1;
  }
  return devs;
}

