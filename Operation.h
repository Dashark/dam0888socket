#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <string>
#include <vector>
#include <glib.h>

#include "Messager.hpp"
#include "json.hpp"
using json = nlohmann::json;
class IoOperation {
 private:
  const int ioport_;
  const int ioaddr_;
  const std::string name_;
  const std::string deviceid_;
  char state_;
 public:
  IoOperation(const char name[], int port, int addr,const char deviceid[]);
  virtual ~IoOperation();
  bool equalPort(int port) const {
    return ioport_ == port ? true : false;
  }
  bool equalAddr(int addr) const {
    return ioaddr_ == addr ? true : false;
  }
  virtual bool execute(char state);
  virtual std::string stateStr();
  virtual std::string stateStr(Messager *mes);
 protected:
  bool upSingal(char state);
  bool downSingal(char state);
};

class UpOperation : public IoOperation {
 private:

 public:
  UpOperation(const char name[], int port, int addr,const char deviceid[]);
  virtual ~UpOperation();
  virtual bool execute(char state);

};

class OperationDefine {
 private:
  GKeyFile *keyFile_;
 public:
  OperationDefine();
  ~OperationDefine();
  std::vector<IoOperation*> create(const json operate, const std::string &type);
 private:
  IoOperation* createOperation(const char type[], const char name[], int port, int addr,const char deviceid[]);

};

#endif
