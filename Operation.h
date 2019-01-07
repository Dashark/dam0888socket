#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <string>
#include <vector>
#include <glib.h>

#include "Messager.hpp"
#include "json.hpp"
using json = nlohmann::json;
class Operation{
protected:
 const int ioport_;
 const std::string name_;
 const int ioaddr_;
 const std::string deviceid_;
public:
 Operation(const char name[], int port, int addr,const char deviceid[]);
 virtual ~Operation();
 virtual std::string stateStr()=0;
 virtual std::string stateStr(Messager *mes)=0;
 virtual bool execute(char state)=0;
 virtual bool execute(const uint16_t state[])=0;
 bool equalPort(int port) const {
   return ioport_ == port ? true : false;
 }
 bool equalAddr(int addr) const {
   return ioaddr_ == addr ? true : false;
 }

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IoOperation:public Operation{
 private:
  char state_;
 public:
  IoOperation(const char name[],int port, int addr,const char deviceid[]);
  virtual ~IoOperation();
  virtual bool execute(char state);
  virtual bool execute(const uint16_t state[]);
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
  SmOperation(const char name[],int port, int addr,const char deviceid[]);
  virtual ~SmOperation();
  virtual bool execute(const uint16_t state[]);
  virtual bool execute(char state);
  virtual std::string stateStr();
  virtual std::string stateStr(Messager *mes);
 protected:
   std::string readU(const uint16_t state[],int startaddr);
   std::string readI(const uint16_t state[],int startaddr);
   std::string readPt(const uint16_t state[],int startaddr);
   std::string readImpEp(const uint16_t state[],int startaddr);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UpOperation : public IoOperation {
 private:

 public:
  UpOperation(const char name[], int port, int addr,const char deviceid[]);
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
  Operation* createOperation(const char type[], const char name[], int port, int addr,const char deviceid[]);

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
