#include "Device.h"
#include <string>
#include <syslog.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <sys/time.h>
#include "json.hpp"
#include "ZLServer.h"
#include <iostream>
using json = nlohmann::json;
Device::Device(const char ip[], const char id[],const char type[],const char relationship[]):ip_(ip), id_(id),type_(type),relationship_(relationship) {

}

Device::~Device() {
  clearOpers();
}

void Device::update(int sid,const uint16_t stats[]) {
  if(equalType("controllableDevice")) syslog(LOG_INFO,"是按钮灯的函数哦%d",sid);
  bool newst = false;
    int idx = 0;
    for(int i=0;i<sizeof(stats);i++) {
      for(Operation *oper : opers_) {
        if(oper->equalPort(sid) && oper->equalAddr(idx)&&oper->isRead()) {
          newst |= oper->execute(stats[i]);
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
  mes->setDID(relationship_);
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

std::string Device::stateStrSmartMeter(Messager *mes) {
  mes->setID(id_);
  mes->setDID(relationship_);
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AGVLight::AGVLight(const char ip[], const char id[],const char type[],const char relationship[]):Device(ip,id,type,relationship) {
syslog(LOG_INFO,"现在创建可操控设备:%s",id);
}

AGVLight::~AGVLight() {

}
void AGVLight::update(int sid,const uint16_t stats[])
{
//  syslog(LOG_INFO,"现在调用的是按钮灯的函数哦%d",sid);
  for(Operation *oper : opers_) {
    if(oper->equalName("lightflashing")) {
        oper->execute(server_,ip_,"light1","off");
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SmartMeter::SmartMeter(const char ip[], const char id[],const char type[],const char relationship[]):Device(ip,id,type,relationship) {
syslog(LOG_INFO,"现在创建电表设备:%s",id);
}
SmartMeter::~SmartMeter(){

}
void SmartMeter::update(int sid,const uint16_t stats[])
{
  //syslog(LOG_INFO,"现在调用的是电表的函数哦%d",sid);
  bool newst = false;
  for(Operation *oper : opers_) {
    if(oper->equalPort(sid)&&oper->isRead()) {
      if(oper->execute(stats))
        newst=true;
         }
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
      char* id=(char*)str_id.c_str();
      syslog(LOG_CRIT,"Device has loded !!! id: %s",id);
      std::string str_ip=element["ip"];
      char* ip=(char*)str_ip.c_str();
      std::string str_type=element["type"];
      char* type=(char*)str_type.c_str();
      std::string str_relationship=element["relationship"].dump();
      char* relationship=(char*)str_relationship.c_str();
    Device *dev;
    if(strcmp(type,"controllableDevice")==0)
    dev = new AGVLight(ip, id,type,relationship);
    else if(strcmp(type,"electricMeter")==0)
     dev = new SmartMeter(ip, id,type,relationship);
    else
    dev = new Device(ip, id,type,relationship);
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
