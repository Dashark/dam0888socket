#include "Broker.h"

#include <syslog.h>
#include <cassert>

Broker::Broker(RdKafka::Topic *topic) {
  topic_ = topic;
}

Broker::~Broker() {

}

void Broker::write(const std::string &data) {

}


/////////////////////////////////////////////////////////
KafkaDefine::KafkaDefine() {
  keyFile_ = g_key_file_new();
  conf_ = nullptr;
  producer_ = nullptr;
}

KafkaDefine::~KafkaDefine() {
  g_key_file_free(keyFile_);
  if(conf_ != nullptr)
    delete conf_;
  if(producer_ != nullptr)
    delete producer_;
}

bool KafkaDefine::load() {
  GError *error = nullptr;
  if(!g_key_file_load_from_file(keyFile_, "kafka.ini", G_KEY_FILE_NONE, &error)) {
    syslog(LOG_WARNING, "failed to load kafka.ini. There's no Kafka model! (%s)", error->message);
    g_free(error);
    return nullptr; //there's no kafka model.
  }

  //ZLServer *server = new ZLServer(port);
  //addIOModels(server);
  //return server;

  return false;
}

void KafkaDefine::kafkaConf() {
  assert(keyFile_ != nullptr);
  std::string errstr;
  GError *error = nullptr;
  gchar* host = g_key_file_get_string(keyFile_, "Broker", "host", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Kafka broker. Please check the configure!!!");
    g_free(error);
    return;// nullptr;
  }
  conf_ = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  conf_->set("bootstrap.servers", host, errstr);
}

void KafkaDefine::kafkaProducer() {
  assert(conf_ != nullptr);
  std::string errstr;
  /*
   * Create producer using accumulated global configuration.
   */
  producer_ = RdKafka::Producer::create(conf_, errstr);
  if (!producer_) {
    syslog(LOG_ERR, "Failed to create producer: %s", errstr.c_str());

  }
  syslog(LOG_INFO, "Created producer %s", producer_->name().c_str());

}

RdKafka::Topic* KafkaDefine::kafkaTopic(const char name[]) {
  assert(producer_ != nullptr);
  std::string errstr;
  /*
   * Create topic handle.
   */
  RdKafka::Topic *topic = RdKafka::Topic::create(producer_, name,
				   nullptr, errstr);
  if (!topic) {
    syslog(LOG_ERR, "Failed to create topic: %s", errstr.c_str());

  }
  return topic;
}

void KafkaDefine::createBroker(const char devs[], RdKafka::Topic *topic) {
  assert(topic != nullptr);
  Broker *bk = new Broker(topic);
  brokers_.insert(std::pair<Broker*, std::string>(bk, devs));
}

