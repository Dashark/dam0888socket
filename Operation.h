#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <string>
#include <vector>
#include <glib.h>
#include "Messager.hpp"
#include "json.hpp"
class ZLServer;
using json = nlohmann::json;
class Operation{
protected:
 const int ioport_;
 const std::string name_;
 const int ioaddr_;
 const std::string type_;
public:
 Operation(const char name[], int port, int addr,const char type[]);
 virtual ~Operation();
 virtual std::string stateStr()=0;
 virtual std::string stateStr(Messager *mes)=0;
 virtual bool execute(char state)=0;
 virtual bool execute(const uint16_t state[])=0;
 virtual bool execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state)=0;
 bool equalPort(int port) const {
   return ioport_ == port ? true : false;
 }
 bool equalAddr(int addr) const {
   return ioaddr_ == addr ? true : false;
 }
 bool equalName(const std::string name) const {
   return name_ == name ? true : false;
 }
 bool isRead() const {
   return type_.compare("read")==0;
 }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ReadOperation:public Operation{
 private:
  char state_;
 public:
  ReadOperation(const char name[],int port, int addr,const char type[]);
  virtual ~ReadOperation();
  virtual bool execute(char state);
  virtual bool execute(const uint16_t state[]);
  bool execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state){};
  virtual std::string stateStr();
  virtual std::string stateStr(Messager *mes);
 protected:
  bool upSingal(char state);
  bool downSingal(char state);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SmOperation:public Operation{
 private:
  const uint16_t *state_;
  int times;
 public:
  SmOperation(const char name[],int port, int addr,const char type[]);
  virtual ~SmOperation();
  virtual bool execute(const uint16_t state[]);
  virtual bool execute(char state);
  bool execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state){};
  virtual std::string stateStr();
  virtual std::string stateStr(Messager *mes);
 protected:
   std::string readU(const uint16_t state[],int startaddr);
   std::string readI(const uint16_t state[],int startaddr);
   std::string readPt(const uint16_t state[],int startaddr);
   std::string readImpEp(const uint16_t state[],int startaddr);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WriteOperation:public Operation{
 private:
  const uint16_t *state_;
  int times_;
  int state_now;
 public:
  WriteOperation(const char name[],int port, int addr,const char type[]);
  virtual ~WriteOperation();
  virtual bool execute(const uint16_t state[]);
  virtual bool execute(char state);
  virtual bool execute(ZLServer* server,const std::string &ip,const std::string &name,const std::string &state);
  virtual std::string stateStr();
  virtual std::string stateStr(Messager *mes);
 protected:
   int OpenOrOff(std::string state);
   bool flashing(int times);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UpOperation : public ReadOperation {
 private:

 public:
  UpOperation(const char name[], int port, int addr,const char type[]);
  virtual ~UpOperation();
  virtual bool execute(char state);
  virtual bool execute(const uint16_t state[]);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class OperationDefine {
 private:
  GKeyFile *keyFile_;
 public:
  OperationDefine();
  ~OperationDefine();
  std::vector<Operation*> create(const json operate, const std::string &type);
 private:
  Operation* createOperation(const char dev_type[], const char name[], int port, int addr,const char op_type[]);

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
