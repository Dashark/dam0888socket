#include "Operation.h"
#include <string>
#include <syslog.h>
#include <sstream>
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
Operation::Operation(const char name[], int port):ioport_(port), name_(name) {


}

Operation::~Operation() {

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


IoOperation::IoOperation(const char name[], int port, int addr,const char deviceid[]):ioport_(port), ioaddr_(addr), name_(name),deviceid_(deviceid) {
  state_ = 0;

}

IoOperation::~IoOperation() {

}

bool IoOperation::execute(char state) {
  bool ret = false;
  ret |= upSingal(state);
  ret |= downSingal(state);
  return ret;
}

std::string IoOperation::stateStr() {
  std::string all = "\"" + name_ + "\":\"" + (state_ == 0 ? "OFF" : "ON") + "\"";
  return all;
}

std::string IoOperation::stateStr(Messager *mes) {
  mes->setKV(name_, (state_ == 0 ? "OFF" : "ON"));
  mes->setDID(deviceid_);
  return "";
}

bool IoOperation::upSingal(char state) {
  bool ret = false;
  if(state_ == 0 && state == 1) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}

bool IoOperation::downSingal(char state) {
  bool ret = false;
  if(state_ == 1 && state == 0) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}
//////////////////////////////////////////////////////////////////////////
UpOperation::UpOperation(const char name[], int port, int addr,const char deviceid[]):IoOperation(name, port, addr,deviceid) {

}

UpOperation::~UpOperation() {

}

bool UpOperation::execute(char state) {
  downSingal(state);
  return upSingal(state);
}

//////////////////////////////////////////////////////////////////////////
OperationDefine::OperationDefine() {
  keyFile_ = g_key_file_new();
}

OperationDefine::~OperationDefine() {
  g_key_file_free(keyFile_);
}


std::vector<IoOperation*> OperationDefine::create(const json operate, const std::string &type) {
  std::vector<IoOperation*> ops;
   //判断操作本身是否为空,operate可以是字符串,当其为空是空字符串
  if(operate=="")
  {
    syslog(LOG_CRIT, "Device operation missing!");
  }
 else
  {
       syslog(LOG_CRIT, "Device operation has loaded!");
	for (auto& element : operate){
	    std::string str_name=element["name"];
	    char* name=(char*)str_name.c_str();
      std::string str_port=element["ioport"];
	    int port=std::stoi(str_port);
      std::string str_addr=element["ioaddr"];
	    int addr=std::stoi(str_addr);
      std::string str_devicesid=element["devicesid"].dump();
	    char* devicesid=(char*)str_devicesid.c_str();
	    IoOperation *op = createOperation(type.c_str(), name, port, addr,devicesid);
	   ops.push_back(op);
	 }
  }


  return ops;
}

IoOperation* OperationDefine::createOperation(const char type[], const char name[], int port, int addr,const char deviceid[]) {
  std::string ts(type);

  if(ts == "agv") {
    return new UpOperation(name, port, addr,deviceid);
  }
  return new IoOperation(name, port, addr,deviceid);
}
