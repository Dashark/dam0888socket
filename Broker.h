#ifndef _BROKER_H_
#define _BROKER_H_

#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <vector>
#include <map>
#include <glib.h>

#include "Messager.hpp"
#include "json.hpp"
using json = nlohmann::json;
class Broker {
 private:
  RdKafka::Topic *topic_;
  RdKafka::Producer *producer_;
 public:
  Broker(RdKafka::Producer *producer, RdKafka::Topic *topic);
  ~Broker();
  void write(const std::string &data);
};
class Messager;
class KafkaDefine {
 private:
  RdKafka::Conf *conf_;
  RdKafka::Producer *producer_;
  std::vector<RdKafka::Topic*> topics_;
  std::map<Broker*, std::string> brokers_;
  std::map<Messager*, std::string> messagers_;
  GKeyFile *keyFile_;
  json js_;
 public:
  KafkaDefine();
  ~KafkaDefine();
  bool load();
  Broker* getBroker(const char id[]) {
    for(auto& kv : brokers_) {
      if(kv.second.find(id) != std::string::npos)
        return kv.first;
    }
    return nullptr;
  }
  Messager* getMessager(const char id[]) {
    for(auto& kv : messagers_) {
      if(kv.second.find(id) != std::string::npos)
        return kv.first;
    }
    return nullptr;
  }
 private:
  void kafkaConf();
  void kafkaProducer();
  RdKafka::Topic* kafkaTopic(json js_topic);
  void createBroker(json js_topic, RdKafka::Topic *topic);
  Messager* createMessager(json js_topic);
};


#endif
