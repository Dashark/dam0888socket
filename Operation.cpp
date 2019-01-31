#include "Operation.h"
#include <string>
#include <glib.h>
#include <glib/gprintf.h>
#include <syslog.h>
#include <sstream>
#include <modbus.h>
#include "json.hpp"
#include "ZLServer.h"
#include <iostream>
using json = nlohmann::json;
Operation::Operation(const char name[], int port, int addr,const char type[]):name_(name),ioport_(port), ioaddr_(addr),type_(type) {
}

Operation::~Operation() {

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ReadOperation::ReadOperation(const char name[], int port, int addr,const char type[]):Operation(name,port,addr,type){
state_ = 0;
}

ReadOperation::~ReadOperation() {

}

bool ReadOperation::execute(char state) {
  bool ret = false;

   ret |= upSingal(state);
   ret |= downSingal(state);
  return ret;
}

bool ReadOperation::execute(const uint16_t state[]) {

}

std::string ReadOperation::stateStr() {
  std::string all = "\"" + name_ + "\":\"" + (state_ == 0 ? "OFF" : "ON") + "\"";
  return all;
}

std::string ReadOperation::stateStr(Messager *mes) {
  mes->setKV(name_, (state_ == 0 ? "OFF" : "ON"));
  return "";
}

bool ReadOperation::upSingal(char state) {
  bool ret = false;
  if(state_ == 0 && state == 1) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}

bool ReadOperation::downSingal(char state) {
  bool ret = false;
  if(state_ == 1 && state == 0) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
    ret = true;
  }
  return ret;
}
//////////////////////////////////////////////////////////////////////////
SmOperation::SmOperation(const char name[], int port, int addr,const char type[]):Operation(name,port,addr,type){
state_ = 0;
times=0;
}

SmOperation::~SmOperation() {

}

bool SmOperation::execute(const uint16_t state[]) {
  state_=state;
  if(times>100)
  {
    times=0;
    return true;
  }
  times++;
  return false;
}
bool SmOperation::execute(char state) {
  return false;
}

std::string SmOperation::stateStr() {
  std::string all = "\"" + name_ + "\":\"" + (state_ == 0 ? "OFF" : "ON") + "\"";
  return all;
}

std::string SmOperation::stateStr(Messager *mes) {
  //读取电压
  mes->setKV("Ua", readU(state_,2));
  mes->setKV("Ub", readU(state_,4));
  mes->setKV("Uc", readU(state_,6));
  //读取电流
  mes->setKV("Ia", readI(state_,8));
  mes->setKV("Ib", readI(state_,10));
  mes->setKV("Ic", readI(state_,12));
  //读取功率
  mes->setKV("Pt", readPt(state_,14));
  mes->setKV("Pa", readPt(state_,16));
  mes->setKV("Pb", readPt(state_,18));
  mes->setKV("Pc", readPt(state_,20));
  //读取总功率
  mes->setKV("ImpEp", readImpEp(state_,22));

  return "";
}

std::string SmOperation::readU(const uint16_t state[],int startaddr){
  std::ostringstream oss;
  int UrAt = state[1]; //电压互感器变比
  oss<<modbus_get_float_dcba (&state[startaddr]) * UrAt * 0.1 * 0.1;
  return oss.str();
}
std::string SmOperation::readI(const uint16_t state[],int startaddr){
  std::ostringstream oss;
  int IrAt = state[0]; //电流互感器变比
  oss<<modbus_get_float_dcba (&state[startaddr]) * IrAt * 0.001;
  return oss.str();
}
std::string SmOperation::readPt(const uint16_t state[],int startaddr){
  int IrAt = 0, UrAt = 0; //电流互感器, 电压互感器变比
  std::ostringstream oss;
  IrAt = state[0];
  UrAt = state[1];
  oss<<modbus_get_float_dcba (&state[startaddr]) * UrAt * IrAt * 0.1 * 0.1;
  return oss.str();
}
std::string SmOperation::readImpEp(const uint16_t state[],int startaddr){
  int IrAt = 0, UrAt = 0; //电流互感器, 电压互感器变比
  std::ostringstream oss;
  IrAt = state[0];
  UrAt = state[1];
  oss<<modbus_get_float_dcba (&state[startaddr]) * UrAt * IrAt*0.1;
  return oss.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WriteOperation::WriteOperation(const char name[], int port, int addr,const char type[]):Operation(name,port,addr,type){
state_ = 0;
times_=0;
state_now=false;
}

WriteOperation::~WriteOperation() {

}

bool WriteOperation::execute(const uint16_t state[]) {

}
bool WriteOperation::execute(char state) {
}
bool WriteOperation::execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state)
{
   devip=ip;
   server_=server;
   if(name.compare(name))return false;
   else{
  //  if(flashing(2))
  //  server->write(ip,ioport_,ioaddr_,state_now);
   }
}

std::string WriteOperation::stateStr() {
}

std::string WriteOperation::stateStr(Messager *mes) {
}
 int WriteOperation::OpenOrOff(std::string state){
   syslog(LOG_INFO,"The device:%s has been %s",name_.c_str(),state.c_str());
  (state=="on")?state_now=1:state_now=0;
  server_->write(devip,ioport_,ioaddr_,state_now);
 }

bool WriteOperation::change()
{
  (state_now==1)?OpenOrOff("off"):OpenOrOff("on");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
OnWOperation::OnWOperation(const char name[], int port, int addr,const char type[]):WriteOperation(name,port,addr,type){
  syslog(LOG_INFO,"The lighton has been created");
}
OnWOperation::~OnWOperation(){}
bool OnWOperation::execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state){
  OpenOrOff("on");
}
///////////////////////////////////////////////////////关////////////////////////////////////////////////////////////////////
OffWOperation::OffWOperation(const char name[], int port, int addr,const char type[]):WriteOperation(name,port,addr,type){
  syslog(LOG_INFO,"The lightoff has been created");
}
OffWOperation::~OffWOperation(){}
bool OffWOperation::execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state){
  OpenOrOff("off");
}
//////////////////////////////////////////////////闪烁////////////////////////////////////////////////////////////////////
FlashingWOperation::FlashingWOperation(const char name[], int port, int addr,const char type[]):WriteOperation(name,port,addr,type){
  syslog(LOG_INFO,"The flashing has been created");
  flashing_type=false;
  state_ = 0;
  times_=0;
  state_now=false;
}
FlashingWOperation::~FlashingWOperation(){
}
bool FlashingWOperation::execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state){
  server_=server;
  devip=ip;
  flashing_type=true;
  startFlashing(3);//闪烁的频率
}

void FlashingWOperation::startFlashing(int times){
  if(times_>times)
  {
    change();
    times_=0;
    return ;
  }
    times_++;
}


void FlashingWOperation::stopFlashing(){
//  thread_type=false;
//  times_=0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UpOperation::UpOperation(const char name[], int port, int addr,const char type[]):ReadOperation(name, port, addr,type) {

}

UpOperation::~UpOperation() {

}

bool UpOperation::execute(char state) {
  downSingal(state);
  return upSingal(state);
}

bool UpOperation::execute(const uint16_t state[]) {

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
      std::string str_type=element["type"];
	    char* op_type=(char*)str_type.c_str();
	    Operation *op = createOperation(type.c_str(), name, port, addr,op_type);
	   ops.push_back(op);
	 }
  }
  return ops;
}

Operation* OperationDefine::createOperation(const char dev_type[], const char name[], int port, int addr,const char op_type[]) {
  std::string ts(dev_type);

  if(ts == "agv") {
    return new UpOperation(name, port, addr,op_type);
  }
  else if(ts=="electricMeter")
  {
    return new SmOperation(name, port, addr,op_type);
  }
  else if(ts=="controllableDevice"){
      std::string ne(name);
      if(ne=="lighton")
      return new OnWOperation(name, port, addr,op_type);
      if(ne=="lightoff")
      return new OffWOperation(name, port, addr,op_type);
      if(ne=="lightflashing")
      return new FlashingWOperation(name, port, addr,op_type);
      return new WriteOperation(name, port, addr,op_type);
  }
  return new ReadOperation(name, port, addr,op_type);
}
