#include "server/common/net/connection/base.h"
#include "server/common/base/log.h"
#include "server/common/base/time_manager.h"
#include "common/net/packet/factorymanager.h"

namespace pap_server_common_net {

namespace connection {

#if defined(_PAP_BILLING) /* { */
const char* g_kModelName = "billing";    
const uint8_t g_kModelSaveLogId = kBillingLogFile;
#elif defined(_PAP_LOGIN) /* }{ */
const char* g_kModelName = "login";
const uint8_t g_kModelSaveLogId = kLoginLogFile;
#elif defined(_PAP_WORLD) /* }{ */
const char* g_kModelName = "world";
const uint8_t g_kModelSaveLogId = kWorldLogFile;
#elif defined(_PAP_SERVER) /* }{ */
const char* g_kModelName = "server";
const uint8_t g_kModelSaveLogId = kServerLogFile;
#endif /* } */

Base::Base(bool flag_isserver) {
  __ENTER_FUNCTION
    id_ = ID_INVALID;
    userid_ = ID_INVALID;
    managerid_ = ID_INVALID;
    socket_ = new pap_common_net::socket::Base();
    Assert(socket_);
    if (!flag_isserver) {
      socket_inputstream_ = new pap_common_net::socket::InputStream(socket_);
      Assert(socket_inputstream_);
      socket_outputstream_ = new pap_common_net::socket::OutputStream(socket_);
      Assert(socket_outputstream_);
    }
    else {
      socket_inputstream_ = new pap_common_net::socket::InputStream(
          socket_,
          SOCKETINPUT_BUFFERSIZE_DEFAULT,
          64 * 1024 * 1024
          );
      Assert(socket_inputstream_);
      socket_outputstream_ = new pap_common_net::socket::OutputStream(
          socket_,
          SOCKETOUTPUT_BUFFERSIZE_DEFAULT,
          64 * 1024 * 1024);
      Assert(socket_outputstream_);
    }
    isempty_ = true;
    isdisconnect_ = false;
    packetindex_ = 0;
  __LEAVE_FUNCTION
}

Base::~Base() {
  __ENTER_FUNCTION
    SAFE_DELETE(socket_outputstream_);
    SAFE_DELETE(socket_inputstream_);
    SAFE_DELETE(socket_);
  __LEAVE_FUNCTION
}

bool Base::processinput() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    bool result = false;
    if (isdisconnect()) return true;
    try {
      uint32_t fillresult = socket_inputstream_->fill();
      if (static_cast<int32_t>(fillresult) <= SOCKET_ERROR) {
        char errormessage[FILENAME_MAX];
        memset(errormessage, '\0', sizeof(errormessage));
        socket_inputstream_->getsocket()->getlast_errormessage(
            errormessage, 
            static_cast<uint16_t>(sizeof(errormessage) - 1));
        Log::save_log(g_kModelName,
                      "[net](%d) connection::Base::processinput()"
                      " socket_inputstream_->fill() result: %d %s",
                      g_time_manager->tm_todword(), 
                      fillresult,
                      errormessage);
        result = false;
      }
      else {
        result = true;
      }
    }
    catch(...) {
      SaveErrorLog();
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::processoutput() {
  __ENTER_FUNCTION
    using namespace pap_server_common_base;
    bool result = false;
    if (isdisconnect()) return true;
    try {
      uint32_t size = socket_outputstream_->reallength();
      if (0 == size) return true;
      uint32_t flushresult = socket_outputstream_->flush();
      if (static_cast<int32_t>(flushresult) <= SOCKET_ERROR) {
        char errormessage[FILENAME_MAX];
        memset(errormessage, '\0', sizeof(errormessage));
        socket_inputstream_->getsocket()->getlast_errormessage(
            errormessage, 
            static_cast<uint16_t>(sizeof(errormessage) - 1));
        Log::save_log(g_kModelName,
                      "[net](%d) Base::processoutput()"
                      " socket_outputstream_->flush() result: %d %s",
                      g_time_manager->tm_todword(), 
                      flushresult,
                      errormessage);
        result = false;
      }
      else {
        result = true;
      }
    }
    catch(...) {
      SaveErrorLog();
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::processcommand(bool option) {
  __ENTER_FUNCTION
    using namespace pap_common_net;
    bool result = false;
    char packetheader[PACKET_HEADERSIZE] = {'\0'};
    uint16_t packetid;
    uint32_t packetcheck, packetsize, packetindex;
    packet::Base* packet = NULL;
    if (isdisconnect()) return true;
    try {
      if (option) { //执行选项操作
      }
      const uint8_t kExecuteCountPreTick = 12; //每帧可以执行的消息数量上限
      uint32_t i;
      for (i = 0; i < kExecuteCountPreTick; ++i) {
        if (!socket_inputstream_->peek(&packetheader[0], PACKET_HEADERSIZE)) {
          //数据不能填充消息头
          break;
        }
        memcpy(&packetid, &packetheader[0], sizeof(uint16_t));
        memcpy(&packetcheck, &packetheader[sizeof(uint16_t)], sizeof(uint32_t));
        packetsize = GET_PACKETLENGTH(packetcheck);
        packetindex = GET_PACKETINDEX(packetcheck);
        if (!packet::FactoryManager::isvalid_packetid(packetid)) {
          return false;
        }
        try {
          //check packet length
          if (socket_inputstream_->reallength() < 
              PACKET_HEADERSIZE + packetsize) {
            //message not receive full
            break;
          }
          //check packet size
          if (packetsize > 
              g_packetfactory_manager->getpacket_maxsize(packetid)) {
            char temp[FILENAME_MAX] = {0};
            snprintf(temp, 
                     sizeof(temp) - 1, 
                     "packet size error, packetid = %d", 
                     packetid);
            AssertEx(false, temp);
            return false;
          }
          //create packet
          packet = g_packetfactory_manager->createpacket(packetid);
          if (NULL == packet) return false;
          packet->setindex(static_cast<int8_t>(packetindex));
          
          //read packet
          result = socket_inputstream_->readpacket(packet);
          if (false == result) {
            g_packetfactory_manager->removepacket(packet);
            return result;
          }
          bool needremove = true;
          bool exception = false;
          uint32_t executestatus = 0;
          try {
            resetkick();
            try {
              executestatus = packet->execute(this);
            }
            catch(...) {
              SaveErrorLog();
              executestatus = kPacketExecuteStatusError;
            }
            if (kPacketExecuteStatusError == executestatus) {
              if (packet) g_packetfactory_manager->removepacket(packet);
              return false;
            }
            else if (kPacketExecuteStatusBreak == executestatus) {
              if (packet) g_packetfactory_manager->removepacket(packet);
              break;
            }
            else if (kPacketExecuteStatusContinue == executestatus) {
              //continue read last packet
            }
            else if (kPacketExecuteStatusNotRemove == executestatus) {
              needremove = false;
            }
            else if (kPacketExecuteStatusNotRemoveError == executestatus) {
              return false;
            }
            else {
              //unknown status
            }
          }
          catch(...) {
            SaveErrorLog();
            exception = true;
          }
          if (packet && needremove) 
            g_packetfactory_manager->removepacket(packet);
          if (exception) return false;
        }
        catch(...) {
          SaveErrorLog();
          return false;
        }
      }
    }
    catch(...) {
      SaveErrorLog();
      return false;
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Base::sendpacket(pap_common_net::packet::Base* packet) {
  __ENTER_FUNCTION
    bool result = false;
    if (isdisconnect()) return true;
    if (socket_outputstream_ != NULL) {
      packet->setindex(++packetindex_);
#if defined(_PAP_SERVER)
      uint32_t before_writesize = socket_outputstream_->reallength();
#endif
      result = socket_outputstream_->writepacket(packet);
      Assert(result);
#if defined(_PAP_SERVER)
      uint32_t after_writesize = socket_outputstream_->reallength();
      if (packet->getsize() != after_writesize - before_writesize - 6) {
        g_log->fast_save_log(g_kModelSaveLogId,
                             "[net] Base::sendpacket() size error"
                             "id = %d(write: %d, should: %d)",
                             pakcet->getid(),
                             after_writesize - before_writesize - 6,
                             pakcet->getsize());
      }
      if (kPacketIdSCCharacterIdle == packet->getid()) {
        //save heartbeat log
      }
#endif
    }
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Base::heartbeat(uint32_t time, uint32_t flag) {
  USE_PARAM(time);
  USE_PARAM(flag);
  return true;
}

int16_t Base::getid() {
  return id_;
}

void Base::setid(int16_t id) {
  id_ = id;
}

int16_t Base::get_userid() {
  return userid_;
}

void Base::set_userid(int16_t id) {
  userid_ = id;
}

int16_t Base::get_managerid() {
  return managerid_;
}

void Base::set_managerid(int16_t id) {
  managerid_ = id;
}

pap_common_net::socket::Base* Base::getsocket() {
  return socket_;
}

void Base::disconnect() {
  __ENTER_FUNCTION
    socket_->close();
  __LEAVE_FUNCTION
}

bool Base::isvalid() {
  __ENTER_FUNCTION
    if (NULL == socket_) return false;
    bool result = false;
    result = socket_->isvalid();
    return result;
  __LEAVE_FUNCTION
    return false;
}

void Base::cleanup() {
  __ENTER_FUNCTION
    socket_->close();
    socket_inputstream_->cleanup();
    socket_outputstream_->cleanup();
    set_managerid(ID_INVALID);
    set_userid(ID_INVALID);
    packetindex_ = 0;
    setdisconnect(false);
  __LEAVE_FUNCTION
}

bool Base::isempty() {
  return isempty_;
}

void Base::setempty(bool status) {
  isempty_ = status;
}

bool Base::isdisconnect() {
  return isdisconnect_;
}

void Base::setdisconnect(bool status) {
  isdisconnect_ = status;
}

void Base::resetkick() {
  //do nothing
}

} //namespace connection

} //namespace pap_server_common_net
