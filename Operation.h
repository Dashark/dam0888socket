#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <string>
#include <glib.h>

class Operation {
 private:
  const int ioport_;
  const int ioaddr_;
 public:
  Operation(int port, int addr);
  bool equalPort(int port) const {
    return ioport_ == port ? true : false;
  }
  bool equalAddr(int addr) const {
    return ioaddr_ == addr ? true : false;
  }
  void execute();
};

class OperationDefine {
 private:
  GKeyFile *keyFile_;
 public:
  Operation* create();
};

#endif
