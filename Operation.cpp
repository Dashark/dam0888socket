#include "Operation.h"

#include <syslog.h>

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
  return upSingal(state);
}

//////////////////////////////////////////////////////////////////////////
OperationDefine::OperationDefine() {
  keyFile_ = g_key_file_new();
}

OperationDefine::~OperationDefine() {
  g_key_file_free(keyFile_);
}

std::vector<Operation*> OperationDefine::create(const std::string &group, const std::string &type) {
  std::string opfile("op_");
  opfile += group;
  opfile += ".ini";
  syslog(LOG_INFO, "Current Operation Conf : %s", opfile.c_str());

  GError *error = NULL;
  std::vector<Operation*> ops;
  if(!g_key_file_load_from_file(keyFile_, opfile.c_str(), G_KEY_FILE_NONE, &error)) {
    syslog(LOG_CRIT, "Device configure failed! (%s)", error->message);
    return ops; //TODO sth will do
  }
  gchar **groups = g_key_file_get_groups(keyFile_, NULL);
  while(*groups != NULL) {
    int port = g_key_file_get_integer(keyFile_, *groups, "ioport", &error);
    int addr = g_key_file_get_integer(keyFile_, *groups, "ioaddr", &error);
    Operation *op = createOperation(type.c_str(), *groups, port, addr);
    ops.push_back(op);
    groups += 1;
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
