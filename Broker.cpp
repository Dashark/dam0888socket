#include "Broker.h"

#include <syslog.h>

Broker::Broker() {

}

Broker::~Broker() {

}

void Broker::write(const std::string &data) {

}


/////////////////////////////////////////////////////////
KafkaDefine::KafkaDefine() {
  keyFile_ = g_key_file_new();
}

KafkaDefine::~KafkaDefine() {
  g_key_file_free(keyFile_);
}

bool KafkaDefine::load() {
  GError *error = nullptr;
  if(!g_key_file_load_from_file(keyFile_, "kafka.ini", G_KEY_FILE_NONE, &error)) {
    syslog(LOG_WARNING, "failed to load kafka.ini. There's no Kafka model! (%s)", error->message);
    g_free(error);
    return nullptr;
  }

  gchar* host = g_key_file_get_string(keyFile_, "Broker", "host", &error);
  if(error != nullptr) {
    syslog(LOG_ERR, "failed to load Kafka broker. Please check the configure!!!");
    g_free(error);
    return nullptr;
  }
  //ZLServer *server = new ZLServer(port);
  //addIOModels(server);
  //return server;

  return false;
}
