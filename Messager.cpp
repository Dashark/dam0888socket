#include "Messager.hpp"
#include <iostream>
//#include "json.hpp"

//using json = nlohmann::json;

Messager::Messager() {
  js_ = R"(
         {
           "kafkaType" : "XXXType",
           "data" : {
                "mpos" : "xxxx-xxx-xx-xx-xx",
                "astep" : "xxxx-xxx-xx-xx-xx",
                "time" : "2018/08/08 09:10:10"
            } 
         }

    )"_json;

  js_["kafkaType"] = "123";


}

void Messager::setID(const std::string &id) {
  js_["data"]["mpos"] = id;
}

bool Messager::setAStep(const std::string &step) {
  js_["data"]["astep"] = step;
  return true;
}

bool Messager::setTime(const std::string &time) {
  js_["data"]["time"] = time;
  return true;
}

void Messager::dump() {
  std::cout << js_ << std::endl;
}
