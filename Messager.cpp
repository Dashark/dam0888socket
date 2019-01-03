#include "Messager.hpp"
#include <iostream>
//#include "json.hpp"
#include <syslog.h>

//using json = nlohmann::json;

Messager::Messager() {

}

Messager::~Messager() {

}

//////////////////////////////////////////////////////////////////////////
Messager* MessagerDefine::create(const std::string &name) {
  if(name == "AGVButtonMessager")
    return new AGVButtonMessager();
  if(name == "DeviceStatusMessager")
    return new DeviceStatusMessager();
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////
AGVButtonMessager::AGVButtonMessager() {
  js_ = R"(
         {
           "kafkaType" : "XXXType",
           "data" : {
                "mpos" : "xxxx-xxx-xx-xx-xx",
                "astep" : "xxxx-xxx-xx-xx-xx",
                "time" : "2018/08/08 09:10:10"
            }
         }

    )"_json;

  js_["kafkaType"] = "123";


}

AGVButtonMessager::~AGVButtonMessager() {

}

void AGVButtonMessager::setID(const std::string &id) {
  js_["data"]["mpos"] = id;
}

bool AGVButtonMessager::setAStep(const std::string &step) {
  js_["data"]["astep"] = step;
  return true;
}

bool AGVButtonMessager::setTime(const std::string &time) {
  js_["data"]["time"] = time;
  return true;
}

bool AGVButtonMessager::setKV(const std::string &key, const std::string &val) {
    js_["data"][key] = val;
    return true;
}
bool AGVButtonMessager::setDID(const std::string &did){
  js_["data"]["devicesid"] = json::parse(did);
  return true;
}
void AGVButtonMessager::dump() {
  syslog(LOG_INFO, "Message String : %s", js_.dump().c_str());
}

bool AGVButtonMessager::send(Broker *bro) {
  bro->write(js_.dump());
  return true;
}

/////////////////////////////////////////////////////////////////////////

DeviceStatusMessager::DeviceStatusMessager() {
  js_ = R"(
         {
           "kafkaType" : "XXXType",
           "data" : {
                "deviceid" : "xxxx-xxx-xx-xx-xx",
                "time" : "2018/08/08 09:10:10"
            }
         }

    )"_json;

  js_["kafkaType"] = "123";


}

DeviceStatusMessager::~DeviceStatusMessager() {

}

void DeviceStatusMessager::setID(const std::string &id) {
  js_["data"]["deviceid"] = id;
}

bool DeviceStatusMessager::setAStep(const std::string &step) {
  js_["data"]["astep"] = step;
  return true;
}

bool DeviceStatusMessager::setTime(const std::string &time) {
  js_["data"]["time"] = time;
  return true;
}

bool DeviceStatusMessager::setKV(const std::string &key, const std::string &val) {
    js_["data"][key] = val;
    return true;
}

bool DeviceStatusMessager::setDID(const std::string &did){
  return true;
}

void DeviceStatusMessager::dump() {
  syslog(LOG_INFO, "Message String : %s", js_.dump().c_str());
}

bool DeviceStatusMessager::send(Broker *bro) {
  bro->write(js_.dump());
  return true;
}
