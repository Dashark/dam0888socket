#ifndef _MESSAGER_H_
#define _MESSAGER_H_

#include <string>
#include "json.hpp"
#include "Broker.h"
using json = nlohmann::json;
class Broker;
class Messager {
private:

public:
  Messager();
  virtual ~Messager();
  virtual void setID(const std::string &id) = 0;
  virtual bool setAStep(const std::string &step) = 0;
  virtual bool setTime(const std::string &time) = 0;
  virtual bool setKV(const std::string &key, const std::string &val) = 0;
  virtual bool setDID(const std::string &did) = 0;
  virtual bool send(Broker *bro) = 0;
  virtual void dump() = 0;
};

class AGVButtonMessager : public Messager {
private:
  json js_;
public:
  AGVButtonMessager();
  virtual ~AGVButtonMessager();
  virtual void setID(const std::string &id);
  virtual bool setAStep(const std::string &step);
  virtual bool setTime(const std::string &time);
  virtual bool setKV(const std::string &key, const std::string &val);
  virtual bool setDID(const std::string &did);
  virtual bool send(Broker *bro);
  virtual void dump();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DeviceStatusMessager : public Messager {
private:
  json js_;
public:
  DeviceStatusMessager();
  virtual ~DeviceStatusMessager();
  virtual void setID(const std::string &id);
  virtual bool setAStep(const std::string &step);
  virtual bool setTime(const std::string &time);
  virtual bool setKV(const std::string &key, const std::string &val);
  virtual bool setDID(const std::string &did);
  virtual bool send(Broker *bro);
  virtual void dump();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SmartMeterMessager : public Messager {
private:
  json js_;
public:
  SmartMeterMessager();
  virtual ~SmartMeterMessager();
  virtual void setID(const std::string &id);
  virtual bool setAStep(const std::string &step);
  virtual bool setTime(const std::string &time);
  virtual bool setKV(const std::string &key, const std::string &val);
  virtual bool setDID(const std::string &did);
  virtual bool send(Broker *bro);
  virtual void dump();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MessagerDefine {
public:
  static Messager* create(const std::string &name);
};
#endif
