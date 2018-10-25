#include "Broker.h"

#include <syslog.h>
#include <cassert>

Broker::Broker(RdKafka::Producer *producer, RdKafka::Topic *topic) {
  producer_ = producer;
  topic_ = topic;
}

Broker::~Broker() {

}

void Broker::write(const std::string &data) {
  assert(producer_ != nullptr);
  assert(topic_ != nullptr);
  /*
   * Produce message
   */
  RdKafka::ErrorCode resp =
    producer_->produce(topic_, RdKafka::Topic::PARTITION_UA,
                      RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                      const_cast<char *>(data.c_str()), data.size(),
                      NULL, NULL);
  if (resp != RdKafka::ERR_NO_ERROR)
	  syslog(LOG_ERR, "Produce failed: %s", RdKafka::err2str(resp).c_str());
  producer_->poll(0);

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
    return false; //there's no kafka model.
  }

  kafkaConf();
  kafkaProducer();
  int gi = 1;
  gchar *tbuf = g_strdup_printf("Topic%02d", gi);
  RdKafka::Topic *topic = kafkaTopic(tbuf);
  while(topic != nullptr) {
    createBroker(tbuf, topic);
    topics_.push_back(topic);
    g_free(tbuf);
    gi += 1; //next topic config
    tbuf = g_strdup_printf("Topic%02d", gi);
    topic = kafkaTopic(tbuf);
  }
  g_free(tbuf);
  return true;
}

void KafkaDefine::kafkaConf() {
  assert(keyFile_ != nullptr);
  std::string errstr;
  GError *error = nullptr;
  gchar* host = g_key_file_get_string(keyFile_, "Broker", "host", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Kafka broker. Please check the configure!!!");
    return;// nullptr;
  }
  conf_ = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  conf_->set("bootstrap.servers", host, errstr); //not sure it's correct
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
    return;
  }
  syslog(LOG_INFO, "Created producer %s", producer_->name().c_str());

}

RdKafka::Topic* KafkaDefine::kafkaTopic(const char group[]) {
  assert(producer_ != nullptr);
  std::string errstr;
  GError *error = nullptr;
  gchar* tstr = g_key_file_get_string(keyFile_, group, "topic", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Kafka topic in group %s. Please check the configure!!! (%s)", group, error->message);
    return nullptr;
  }
  /*
   * Create topic handle.
   */
  RdKafka::Topic *topic = RdKafka::Topic::create(producer_, tstr,
				   nullptr, errstr);
  if (!topic) {
    syslog(LOG_ERR, "Failed to create topic: %s", errstr.c_str());
    g_free(tstr);
    return nullptr;
  }
  g_free(tstr);
  return topic;
}

void KafkaDefine::createBroker(const char group[], RdKafka::Topic *topic) {
  assert(topic != nullptr);
  GError *error = nullptr;
  gchar* devs = g_key_file_get_string(keyFile_, group, "devices", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Kafka devices in group %s. Please check the configure!!! (%s)", group, error->message);
    return;// nullptr;
  }
  Broker *bk = new Broker(producer_, topic);
  brokers_.insert(std::pair<Broker*, std::string>(bk, devs));
  g_free(devs);
}

