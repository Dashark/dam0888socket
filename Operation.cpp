#include "Operation.h"

#include <syslog.h>

Operation::Operation(const char name[], int port, int addr):ioport_(port), ioaddr_(addr), name_(name) {
  state_ = 0;
}

void Operation::execute(char state) {
  if(state_ != state) {
    state_ = state;
    syslog(LOG_INFO, "Operation %s : %d", name_.c_str(), state_);
  }
}

std::string Operation::stateStr() const {
  std::string all = "\"" + name_ + "\":\"" + (state_ == 0 ? "OFF" : "ON") + "\"";
  syslog(LOG_INFO, "Operation String : %s", all.c_str());
  return all;
}
//////////////////////////////////////////////////////////////////////////
OperationDefine::OperationDefine() {
  keyFile_ = g_key_file_new();
}

OperationDefine::~OperationDefine() {
  g_key_file_free(keyFile_);
}

std::vector<Operation*> OperationDefine::create(const std::string &file) {
  GError *error = NULL;
  std::vector<Operation*> ops;
  if(!g_key_file_load_from_file(keyFile_, file.c_str(), G_KEY_FILE_NONE, &error)) {
    syslog(LOG_CRIT, "Device configure failed! (%s)", error->message);
    return ops; //TODO sth will do
  }
  gchar **groups = g_key_file_get_groups(keyFile_, NULL);
  while(*groups != NULL) {
    int port = g_key_file_get_integer(keyFile_, *groups, "ioport", &error);
    int addr = g_key_file_get_integer(keyFile_, *groups, "ioaddr", &error);
    Operation *op = new Operation(*groups, port, addr);
    ops.push_back(op);
    groups += 1;
  }
  return ops;
}
