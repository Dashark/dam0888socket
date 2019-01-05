#include "Device.h"
#include <string>
#include <syslog.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include "json.hpp"
#include <iostream>
#include <modbus.h>
using json = nlohmann::json;
Device::Device(const char ip[], const char id[],const char type[]):ip_(ip), id_(id),type_(type) {

}

Device::~Device() {
  clearOpers();
}

void Device::update(int sid, const std::vector<char> &stats) {
  int idx = 0;
  bool newst = false;
  for(char s : stats) {
    for(IoOperation *oper : opers_) {
    //     syslog(LOG_INFO, "模块数据与操作比对 模块id: %d,这个操作执行到%,IoOperation的地址",sid,idx,oper->ioaddr_);
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

void Device::update(int sid,const uint16_t parameter[],const uint16_t electricityData[],const uint16_t energyData[]){
  bool newst = false;
    for(IoOperation *oper : opers_) {
      syslog(LOG_INFO,"查询需要的id");
      if(oper->equalPort(sid)) {
        newst =true;
        syslog(LOG_INFO,"查到了需要的id");
        break; //TODO one state for one operation
      }
    }
  if(newst) {
    syslog(LOG_INFO,"进入消息的遍历");
    for(Messager *mes : messagers_) {
      syslog(LOG_INFO,"消息的遍历");
      if(mes != nullptr) {
        syslog(LOG_INFO,"开始执行stateStrSmartMeter()");
        stateStrSmartMeter(mes);
        for(Broker *bk : brokers_) {
          if(bk != nullptr) {
            mes->send(bk);
          }
        }
      }
    }
  }


syslog(LOG_INFO, "电表查询 : %d",sid);
   int IrAt = 0, UrAt = 0; //电流互感器, 电压互感器变比
   json js_m;
      IrAt = parameter[0];
      UrAt = parameter[1];

      js_m["Ua"] = modbus_get_float_dcba (&electricityData[0]) * UrAt * 0.1 * 0.1;
      js_m["Ub"] = modbus_get_float_dcba (&electricityData[2]) * UrAt * 0.1 * 0.1;
      js_m["Uc"] = modbus_get_float_dcba (&electricityData[4]) * UrAt * 0.1 * 0.1;

      js_m["Ia"] = modbus_get_float_dcba (&electricityData[6]) * IrAt * 0.001;
      js_m["Ib"] = modbus_get_float_dcba (&electricityData[8]) * IrAt * 0.001;
      js_m["Ic"] = modbus_get_float_dcba (&electricityData[10]) * IrAt * 0.001;


      js_m["Pt"] = modbus_get_float_dcba (&electricityData[12]) * UrAt * IrAt * 0.1 * 0.1;
      js_m["Pa"] = modbus_get_float_dcba (&electricityData[14]) * UrAt * IrAt * 0.1 * 0.1;
      js_m["Pb"] = modbus_get_float_dcba (&electricityData[16]) * UrAt * IrAt * 0.1 * 0.1;
      js_m["Pc"] = modbus_get_float_dcba (&electricityData[18]) * UrAt * IrAt * 0.1 * 0.1;

      js_m["ImpEp"] = modbus_get_float_dcba (energyData) * UrAt * IrAt*0.1;
   syslog(LOG_INFO,js_m.dump().c_str());

}

std::string Device::stateStr() {
  std::string all = "{\"kafkaType\":\"x\",\"data\":{\"mpos\":\"" + id_ + "\"";
  for(IoOperation* oper : opers_) {
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
  for(IoOperation* oper : opers_) {
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

std::string Device::stateStrSmartMeter(Messager *mes) {
  mes->setID(id_);
  mes->setKV("minwei","好男人");
  mes->setKV("minwei","好男人");
  mes->setKV("minwei","好男人");
  mes->setKV("minwei","好男人");
  for(IoOperation* oper : opers_) {
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
  for(IoOperation* oper : opers_)
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
      char* id=(char*)str_id.c_str();
      syslog(LOG_CRIT,"Device has loded !!! id: %s",id);
      std::string str_ip=element["ip"];
      char* ip=(char*)str_ip.c_str();
      std::string str_type=element["type"];
      char* type=(char*)str_type.c_str();

    Device *dev = new Device(ip, id,type);
    Broker *bro = kafDef_->getBroker(id);
    dev->attach(bro);
    Messager *mes = kafDef_->getMessager(id);
    dev->attach(mes);
    devs.push_back(dev);
    std::vector<IoOperation*> ops = opdef.create(element["operate"], type);
    dev->setOpers(ops);
  }
  return devs;
}
