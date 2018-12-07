#include "Device.h"
#include <string>
#include <syslog.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
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
    for(Messager *mes : messagers_) {
      if(mes != nullptr) {
        stateStr(mes);
        for(Broker *bk : brokers_) {
          if(bk != nullptr) {
            mes->send(bk);
          }
        }
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

std::string Device::stateStr(Messager *mes) {
  mes->setID(id_);
  for(Operation* oper : opers_) {
    assert(oper != nullptr);
    oper->stateStr(mes);
  }

  gchar *time_str = NULL;
  GDateTime *time = NULL;
  time = g_date_time_new_now_local();
  time_str = g_date_time_format(time, "%Y/%m/%d %H:%M:%S");
  mes->setTime(time_str);
  g_free(time_str);
  g_date_time_unref(time);

  mes->dump();
  return "";
}

void Device::clearOpers() {
  for(Operation* oper : opers_)
    delete oper;
  opers_.clear();
}

///////////////////////////////////////////////////////////////////////
DeviceFactory::DeviceFactory() {
  kafDef_ = new KafkaDefine();
}

DeviceFactory::~DeviceFactory() {
  delete kafDef_;
}

std::vector<Device*> DeviceFactory::createDevices() {
  kafDef_->load();
  std::vector<Device*> devs;
   std::ifstream i("config.json");
    json js_;
    i >> js_;
  if(js_["devices"]==""){
    syslog(LOG_CRIT, "Device configure fail!");
    return devs; //TODO sth will do
  }
  else 
  {
    syslog(LOG_CRIT, "Device configure success!");
  }
  OperationDefine opdef;
    for (auto& element : js_["devices"]){ 
      std::string str_id=element["id"];
      char* id=(char*)str_id.data();
      syslog(LOG_CRIT,"Device has loded !!! id: %s",id);
      std::string str_ip=element["ip"];
      char* ip=(char*)str_ip.data();
      std::string str_type=element["type"];
      char* type=(char*)str_type.data();
        
    Device *dev = new Device(ip, id);
    Broker *bro = kafDef_->getBroker(id);
    dev->attach(bro);
    Messager *mes = kafDef_->getMessager(id);
    dev->attach(mes);
    devs.push_back(dev);
    std::vector<Operation*> ops = opdef.create(element["operate"], type);
    dev->setOpers(ops);
  }
  return devs;
}

