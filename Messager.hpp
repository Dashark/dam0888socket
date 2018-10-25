#ifndef _MESSAGER_H_
#define _MESSAGER_H_

#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Messager {
private:
  json js_;
public:
  Messager();
  void setID(const std::string &id);
  bool setAStep(const std::string &step);
  bool setTime(const std::string &time);
  void dump();
};

#endif
