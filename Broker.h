#ifndef _BROKER_H_
#define _BROKER_H_

#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <vector>
#include <map>
#include <glib.h>

class Broker {
 private:
  RdKafka::Topic *topic_;
  RdKafka::Producer *producer_;
 public:
  Broker(RdKafka::Producer *producer, RdKafka::Topic *topic);
  ~Broker();
  void write(const std::string &data);
};

class KafkaDefine {
 private:
  RdKafka::Conf *conf_;
  RdKafka::Producer *producer_;
  std::vector<RdKafka::Topic*> topics_;
  std::map<Broker*, std::string> brokers_;
  GKeyFile *keyFile_;
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
 private:
  void kafkaConf();
  void kafkaProducer();
  RdKafka::Topic* kafkaTopic(const char group[]);
  void createBroker(const char group[], RdKafka::Topic *topic);
};


#endif
