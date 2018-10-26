#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <string>
#include <vector>
#include <glib.h>

class Operation {
 private:
  const int ioport_;
  const int ioaddr_;
  const std::string name_;
  char state_;
 public:
  Operation(const char name[], int port, int addr);
  virtual ~Operation();
  bool equalPort(int port) const {
    return ioport_ == port ? true : false;
  }
  bool equalAddr(int addr) const {
    return ioaddr_ == addr ? true : false;
  }
  virtual bool execute(char state);
  virtual std::string stateStr();
 protected:
  bool upSingal(char state);
  bool downSingal(char state);
};

class UpOperation : public Operation {
 private:

 public:
  UpOperation(const char name[], int port, int addr);
  virtual ~UpOperation();
  virtual bool execute(char state);

};

class OperationDefine {
 private:
  GKeyFile *keyFile_;
 public:
  OperationDefine();
  ~OperationDefine();
  std::vector<Operation*> create(const std::string &group, const std::string &type);
 private:
  Operation* createOperation(const char type[], const char name[], int port, int addr);

};

#endif
