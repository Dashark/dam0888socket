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
 public:
  Broker();
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
};


#endif
