#include "Operation.h"
#include <string>
#include <syslog.h>
#include <sstream>
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
Operation::Operation(const char name[], int port, int addr):ioport_(port), ioaddr_(addr), name_(name) {
  state_ = 0;

}

Operation::~Operation() {

}

bool Operation::execute(char state) {
  bool ret = false;
  ret |= upSingal(state);
  ret |= downSingal(state);
  return ret;
}

std::string Operation::stateStr() {
  std::string all = "\"" + name_ + "\":\"" + (state_ == 0 ? "OFF" : "ON") + "\"";
  return all;
}

std::string Operation::stateStr(Messager *mes) {
  mes->setKV(name_, (state_ == 0 ? "OFF" : "ON"));
  return "";
}

bool Operation::upSingal(char state) {
  bool ret = false;
  if(state_ == 0 && state == 1) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}

bool Operation::downSingal(char state) {
  bool ret = false;
  if(state_ == 1 && state == 0) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}
//////////////////////////////////////////////////////////////////////////
UpOperation::UpOperation(const char name[], int port, int addr):Operation(name, port, addr) {

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


std::vector<Operation*> OperationDefine::create(const json operate, const std::string &type) {
  std::vector<Operation*> ops; 
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
	    Operation *op = createOperation(type.c_str(), name, port, addr);
	   ops.push_back(op);
	 }
  }
  

  return ops;
}

Operation* OperationDefine::createOperation(const char type[], const char name[], int port, int addr) {
  std::string ts(type);

  if(ts == "agv") {
    return new UpOperation(name, port, addr);
  }
  return new Operation(name, port, addr);
}
