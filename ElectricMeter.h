#ifndef CIRCLE_H
#define CIRCLE_H


#include <modbus.h>
#include "json.hpp"
using json = nlohmann::json;
//我的代码写在这里
class ElectricMeter{
private:
  double id;
  int fd;
  modbus_t *modbus_rtu_ctx;
  int socket_fd_;
  json js_;
public:
  ElectricMeter(int id,int fd,modbus_t *modbus_rtu_ctx);
  virtual ~ElectricMeter();
  void creatElectricMeter();
  int pd666_callback();
};



#endif
