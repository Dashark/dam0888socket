#include "Broker.h"

#include <syslog.h>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using json = nlohmann::json;
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
  //keyFile_ = g_key_file_new();
  conf_ = nullptr;
  producer_ = nullptr;
}

KafkaDefine::~KafkaDefine() {
 // g_key_file_free(keyFile_);
  if(conf_ != nullptr)
    delete conf_;
  if(producer_ != nullptr)
    delete producer_;
}

bool KafkaDefine::load() {
 // GError *error = nullptr;

   std::ifstream i("config.json");
    i >> js_;
   json test;
    if(js_["kafka"]=="")
    {
    syslog(LOG_WARNING, "failed to load kafka.ini. There's no Kafka model! ");
     return false;
    }
   kafkaConf();
   kafkaProducer();
   RdKafka::Topic *topic ;
   for (auto& element : js_["kafka"]["topic"])
  {
   
      topic = kafkaTopic(element);
      createBroker(element,topic);
      topics_.push_back(topic);
  }

 

  return true;
}

void KafkaDefine::kafkaConf() {
  std::string errstr;
 if(js_["kafka"]["host"]=="") {
    syslog(LOG_ERR, "failed to load Kafka broker. Please check the configure!!!");
    return;// nullptr;
  }
  std::string str_host=js_["kafka"]["host"];
  char* host=(char*)str_host.data();
   syslog(LOG_ERR, "loaded Kafka host: %s",host);
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

RdKafka::Topic* KafkaDefine::kafkaTopic(json js_topic) {
  assert(producer_ != nullptr);
  std::string errstr;

  if(js_topic["topic"] =="") {
    syslog(LOG_ERR, "failed to load Kafka topic %s.", js_topic.dump().data());
    return nullptr;
  }
 
  std::string str_tstr=js_topic["topic"];
   char* tstr=(char*)str_tstr.data();
  
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
  
  return topic;
}

void KafkaDefine::createBroker(json js_topic,RdKafka::Topic *topic) {

  if(js_topic["devices"]==""){
   syslog(LOG_ERR, "failed to load Kafka devices,topic: %s.", js_topic["name"].dump().data());
    return;// nullptr;
  }
  std::string str_devs=js_topic["devices"];
  char* devs=(char*)str_devs.data();
  syslog(LOG_ERR, "loaded Kafka devices ids: %s.",devs);
  Broker *bk = new Broker(producer_, topic);
  brokers_.insert(std::pair<Broker*, std::string>(bk, devs));
  Messager *mes = createMessager(js_topic);
  if(mes != nullptr)
    messagers_.insert(std::pair<Messager*, std::string>(mes, devs));
 
}

Messager* KafkaDefine::createMessager(json js_topic) {
  
  if(js_topic["json"]== "") {
 
    syslog(LOG_ERR, "failed to load Kafka json");
    return nullptr;
  }

  std::string str_json=js_topic["json"];
  char* json=(char*)str_json.data();
  syslog(LOG_ERR, "loaded Kafka json: %s",json);
  
  Messager *mes = MessagerDefine::create(json);
  return mes;
}
