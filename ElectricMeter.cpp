#include <glib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <modbus.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <syslog.h>
#include "json.hpp"
using json = nlohmann::json;
#include "ElectricMeter.h"

ElectricMeter::ElectricMeter(int id,int fd,modbus_t *modbus_rtu_ctx)
{
  this->id=id;
  this->fd=fd;
  this->modbus_rtu_ctx=modbus_rtu_ctx;
  js_= R"({
  "data": {
  "Ua":0,
  "Ub":0,
  "Uc":0,
  "Ia":0,
  "Ib":0,
  "Ic":0,
  "Pa":0,
  "Pb":0,
  "Pc":0,
  "Pt":0,
  "ImpEp":0
  },
  "id": 0,
  "electricMeterid": 0
   })"_json;
}

ElectricMeter::~ElectricMeter()
{

}

//这是采集电表数据的方法;采集的数据会写入js_之中;
int ElectricMeter::pd666_callback ()
{

            if (modbus_set_socket (modbus_rtu_ctx,fd) == -1) { //设置modbus的文件描述编号
                fprintf (stderr, "modbus_set_socket falied @ fd = %d\n",fd);
                return -1;
            };
            if (modbus_set_slave (modbus_rtu_ctx,id) == -1) { // PD666-3S4数显表设置的ID
                fprintf (stderr, "modbus_set_slave falied @ ID = %d\n", id);
                return -1;
            }

            int IrAt = 0, UrAt = 0; //电流互感器, 电压互感器变比
            uint16_t parameter[2] = {0};
            int rc = modbus_read_registers (modbus_rtu_ctx, 0x06, 2, parameter);
            if (rc > 0) {
                IrAt = parameter[0];
                UrAt = parameter[1];
                printf ("IrAt = %d  UrAt = %d\n", IrAt, UrAt);
            } else {

                return -1;
            }

            uint16_t electricityData[20] = {0}; //二次测电量数据
            rc = modbus_read_registers (modbus_rtu_ctx, 0x2006, 20, electricityData);
            if (rc > 0) {
                js_["Ua"] = modbus_get_float_dcba (&electricityData[0]) * UrAt * 0.1 * 0.1;
                //float Ua = modbus_get_float_dcba (&electricityData[0]) * UrAt * 0.1 * 0.1;
                js_["Ub"] = modbus_get_float_dcba (&electricityData[2]) * UrAt * 0.1 * 0.1;
                //float Ub = modbus_get_float_dcba (&electricityData[2]) * UrAt * 0.1 * 0.1;
                js_["Uc"] = modbus_get_float_dcba (&electricityData[4]) * UrAt * 0.1 * 0.1;
              //  float Uc = modbus_get_float_dcba (&electricityData[4]) * UrAt * 0.1 * 0.1;
              //  printf ("Ua = %f  Ub = %f  Uc = %f\n", Ua, Ub, Uc); //电压

                js_["Ia"] = modbus_get_float_dcba (&electricityData[6]) * IrAt * 0.001;
              //  float Ia = modbus_get_float_dcba (&electricityData[6]) * IrAt * 0.001;
                js_["Ib"] = modbus_get_float_dcba (&electricityData[8]) * IrAt * 0.001;
              //  float Ib = modbus_get_float_dcba (&electricityData[8]) * IrAt * 0.001;
                js_["Ic"] = modbus_get_float_dcba (&electricityData[10]) * IrAt * 0.001;
              //  float Ic = modbus_get_float_dcba (&electricityData[10]) * IrAt * 0.001;
              //  printf ("Ia = %f  Ib = %f  Ic = %f\n", Ia, Ib, Ic); //电流

                js_["Pt"] = modbus_get_float_dcba (&electricityData[12]) * UrAt * IrAt * 0.1 * 0.1;
                js_["Pa"] = modbus_get_float_dcba (&electricityData[14]) * UrAt * IrAt * 0.1 * 0.1;
                js_["Pb"] = modbus_get_float_dcba (&electricityData[16]) * UrAt * IrAt * 0.1 * 0.1;
                js_["Pc"] = modbus_get_float_dcba (&electricityData[18]) * UrAt * IrAt * 0.1 * 0.1;
              //  printf ("Pt = %f, Pa = %f  Pb = %f  Pc = %f\n", Pt, Pa, Pb, Pc); //功率
            } else {
                return -1;
            }

            uint16_t energyData[2] = {0}; //正向有功总电能
            rc = modbus_read_registers (modbus_rtu_ctx, 0x401E, 2, energyData);
            if (rc > 0) {
                js_["ImpEp"] = modbus_get_float_dcba (energyData) * UrAt * IrAt*0.1;
              //  printf ("ImpEp = %f\n\n\n\n\n", ImpEp);
            } else {
               printf("rc<=0----2");
                return -1;
           }

}

void ElectricMeter::creatElectricMeter(){
  syslog(LOG_INFO, "现在开始查询电表数据");
  //char* c_id=id;
  syslog(LOG_INFO, "fd:%d",fd);

 pd666_callback ();
    std::string str_js_=js_.dump();
    syslog(LOG_INFO, "json:%s",str_js_.c_str());

}
