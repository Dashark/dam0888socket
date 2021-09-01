
#include "H3CServer.h"
#include <fstream>
#include <cassert>
#include <syslog.h>
#include <unistd.h>
#include <string>

#include <sstream>
#include <arpa/inet.h>
#include <stdio.h>
#include "json.hpp"

using json = nlohmann::json;
#define NB_CONNECTION  5 //listen()函数等待连接队列的最大长度

H3CServer::ClientModel::ClientModel(const std::string &ip, int id): slaveID_(id) {

  assert(slaveID_ > 0);
  ip_ = ip;
  fd_ = -1;
}

H3CServer::ClientModel::~ClientModel() {

}

void H3CServer::ClientModel::writeInfo(const std::string &info) {
  if (fd_ != -1) {
    if (::write(fd_, info.c_str(), info.size()) <= 0) {
      syslog(LOG_ERR, "write info error %d", errno);
    }
  }
}

bool H3CServer::ClientModel::setFileDesc(int fd) {
  fd_ = fd;
  return true;
}

///////////////////////////H3CServer Implement//////////////////////////////////////////////////////
H3CServer::H3CServer(int port):port_(port) {
  assert(port_ > 1024);

}

H3CServer::~H3CServer() {
  for(ClientModel *io : models_) {
    delete io;
  }

}

int H3CServer::listenH3C() {
	struct sockaddr_in server_zlmcu = {0};
	/*--- zlmcu的socket连接设置 ---*/
	socket_fd_ = socket (AF_INET, SOCK_STREAM, 0);
	if (socket_fd_ == -1) {
		syslog(LOG_CRIT, "cannot create socket for H3CMCU!\n");
		return socket_fd_;
	}
	syslog (LOG_INFO, "socket of H3CMCU is successed = %d\n", socket_fd_);

	server_zlmcu.sin_family = AF_INET;
	server_zlmcu.sin_addr.s_addr = inet_addr("0.0.0.0"); //INADDR_ANY
	server_zlmcu.sin_port = htons (port_);

	if (bind (socket_fd_, (struct sockaddr*)&server_zlmcu, sizeof(server_zlmcu)) != 0) {
		syslog (LOG_CRIT, "cannot bind socket:");
		close (socket_fd_);
    socket_fd_ = -1;
		return socket_fd_;
	}

	if (listen (socket_fd_, NB_CONNECTION) != 0) {
		syslog (LOG_CRIT, "cannot listen on socket!\n");
		close (socket_fd_);
    socket_fd_ = -1;
		return socket_fd_;
	}
  moditer_ = models_.end();
  return socket_fd_;
}

int H3CServer::clientConnected() {
  if(socket_fd_ == -1)
    return -1;  //wrong server
  struct sockaddr_in *client = new struct sockaddr_in;
  socklen_t len = sizeof(struct sockaddr_in);
  int newfd = accept (socket_fd_, (struct sockaddr*)client, &len);
  if (newfd == -1) {
    syslog (LOG_ERR, "Server accept error (fd = %d)", socket_fd_);
  } else {
    char *ip = inet_ntoa(client->sin_addr);
    syslog (LOG_INFO, "fd = %d, New connection from %s:%d on socket %d\n",
            socket_fd_, ip, client->sin_port, newfd);
    setClientModel(ip, newfd);  //TODO Jave client....
  }
  delete client;
  return newfd;
}

void H3CServer::createClientModel(const std::string &ip, int id) {
  assert(id > 0);
  ClientModel *iom = new H3CServer::ClientModel(ip, id);
  models_.push_back(iom);
  moditer_ = models_.begin();
}

H3CServer::ClientModel* H3CServer::findClientModel(const std::string &ip) {
  for(ClientModel *io : models_) {
    if(io->equal(ip))
      return io;
  }
  return nullptr;
}

void H3CServer::setClientModel(const std::string &ip, int fd) {
  for(ClientModel *iom : models_) {
    if(iom->equal(-1)) {
      iom->setFileDesc(fd);
      break;
    }
  }
}

void H3CServer::closeClientModel(int fd) {
  std::vector<ClientModel*>::iterator it = models_.begin();
  for(; it < models_.end(); ++it) {
    if((*it)->equal(fd)) {
      (*it)->setFileDesc(-1);
      break;
    }
  }
}
  
bool H3CServer::write(const std::string &info) {
  for(ClientModel *iom : models_) {
    iom->writeInfo(info);
  }
  return true;
}

////////////////////////////////////////////////////////////////
#include "idm_netsdk.h"
VOID CALLBACK IDM_DEV_Message_Callback (
                                          LONG    lUserID,
                                          ULONG   ulCommand,
                                          VOID    *pBuffer,
                                          ULONG   ulBufferSize,
                                          IDM_DEV_ALARM_DEVICE_INFO_S *pstAlarmDeviceInfo,
                                          VOID    *pUserData
                                          )
{
  //printf("CAllBack Triggered\n");
  H3CServer *server = static_cast<H3CServer*>(pUserData);
  IDM_DEV_ALARM_EVENT_S *pinfo = (IDM_DEV_ALARM_EVENT_S *)pBuffer;
  std::string jstr;
  if ((0 != pinfo->stEvent.ulBufferSize) && (nullptr != pinfo->stEvent.pBuffer)) {
    json j = json::parse(pinfo->stEvent.pBuffer);
    j["userId"] = lUserID;
    //jstr = 
    //j["Info"] = jstr;
    //printf("Json: \n%s\n",j.dump().c_str());
    syslog(LOG_INFO, "Send data to userID %d", lUserID);
    server->write(j.dump());
  }

}

VOID CALLBACK IDM_DEV_Exception_Callback(
    LONG lUserID,
    LONG lHandle,
    ULONG ulType,
    VOID *pUserData) {

  syslog(LOG_ERR, "IDM_DEV_Exception_Callback userID %d", lUserID);
  syslog(LOG_ERR, "IDM_DEV_Exception_Callback Handle %d", lHandle);
  syslog(LOG_ERR, "IDM_DEV_Exception_Callback Type %d", ulType);
  H3CDefine *def = (H3CDefine*)pUserData;
  if (0 == ulType || 3 == ulType) {
    IDM_DEV_StopAlarmUp(lHandle);
    IDM_DEV_Logout(lUserID);
    def->logoutH3C(lUserID);
  }
}

H3CDefine::H3CDefine() {
  std::ifstream i("config.json");
  i >> js_;
}

H3CDefine::~H3CDefine() {
  for (Camera &cam : cams) {
    IDM_DEV_StopAlarmUp(cam.alarmHandle);
    IDM_DEV_Logout(cam.userID);
  }
  IDM_DEV_Cleanup();
}

//TODO  init H3C cameras
void H3CDefine::initH3C(H3CServer *server) {
  IDM_DEV_Init();
  IDM_DEV_SaveLogToFile(3, 0, "/home/huawei/");

  int ret = IDM_DEV_SetAlarmCallback(0, IDM_DEV_Message_Callback,(void *)server);
  syslog(LOG_INFO, "IDM_DEV_SetAlarmCallback ret %d", ret);
  ret = IDM_DEV_SetExceptionCallback(IDM_DEV_Exception_Callback, (void *)this);
  syslog(LOG_INFO, "IDM_DEV_SetExceptionCallback ret %d", ret);
  int id = 0;
  for (auto &camj : js_["h3cameras"]) {
    Camera cam;
    cam.configID = id;
    cam.userID = -1;
    cam.alarmHandle = -1;
    cam.ip = camj["ip"];
    cam.user = camj["user"];
    cam.password = camj["password"];
    cam.port = camj["port"];
    cams.push_back(cam);
    id += 1;
  }
}
void H3CDefine::loginH3C() {
  for (Camera &cam : cams) {
    if (cam.userID != -1) continue;
    syslog(LOG_WARNING, "loginH3C to %d", cam.configID);
    IDM_DEV_USER_LOGIN_INFO_S loginInfo = {0};
    IDM_DEV_DEVICE_INFO_S devInfo;
    sprintf(loginInfo.szDeviceIP, "%s", cam.ip.c_str());
    sprintf(loginInfo.szUsername, "%s", cam.user.c_str());
    sprintf(loginInfo.szPassword, "%s", cam.password.c_str());
    loginInfo.usPort = std::stoi(cam.port);
    int userID = -1;
    int ret = IDM_DEV_Login(loginInfo, &devInfo, &userID);
    syslog(LOG_INFO, "IDM_DEV_Login ret %d && %d", ret, userID);
    if (IDM_SUCCESS == ret) {
      cam.userID = userID;
    }
  }
}
void H3CDefine::alarmH3C() {
  for (Camera& cam : cams) {
    if (-1 == cam.userID || -1 != cam.alarmHandle) continue;
    syslog(LOG_WARNING, "alarmH3C to %ld", cam.userID);
    std::string sub = "{\"channel_no_list\":[65535],\"event_types\":[0],\"event_levels\":[2]}";
    IDM_DEV_ALARM_PARAM_S stAlarmParam = {0};
    LONG lAlarmHandle = 0;
    stAlarmParam.ulLevel = 0;
    stAlarmParam.pcSubscribes = const_cast<char *>(sub.c_str());
    stAlarmParam.ulSubscribesLen = sub.length();
    stAlarmParam.ucType = 0;
    stAlarmParam.ucLinkMode = 0;// 0xFF;
    int ret = IDM_DEV_StartAlarmUp(cam.userID, stAlarmParam, &lAlarmHandle);
    syslog(LOG_INFO, "IDM_DEV_StartAlarmUp ret %d", ret);
    if (IDM_SUCCESS == ret) {
      cam.alarmHandle = lAlarmHandle;
    }
  }
}
void H3CDefine::logoutH3C(int id) {
  for (Camera &cam : cams) {
    if (cam.userID == id) {
      syslog(LOG_WARNING, "logoutH3C to %ld", cam.userID);
      cam.userID = -1;
      cam.alarmHandle = -1;
      break;
    }
  }
}

H3CServer* H3CDefine::createServer() {
  if(js_["client"]==""){
   syslog(LOG_CRIT, "failed to load configuration of zlmcu. Process can't run!!!");
    return nullptr;
   }

  std::string str_port=js_["port"];
  int port=std::stoi(str_port);
   if(js_["port"]==""){
    syslog(LOG_ERR, "failed to load Server's port. Process can't run!!!");
    return nullptr;
  }
  H3CServer *server = new H3CServer(port);
  addClientModels(server);

  return server;
}

//TODO this is Java client
void H3CDefine::addClientModels(H3CServer *server) {

   std::string sip=js_["client"]["ip"];
   server->createClientModel(sip.c_str(), 1);
   server->createClientModel(sip.c_str(), 2);
   server->createClientModel(sip.c_str(), 3);
   server->createClientModel(sip.c_str(), 4);
   server->createClientModel(sip.c_str(), 5);
}
