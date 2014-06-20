#include "server/common/net/connection/manager.h"

namespace pap_server_common_net {

namespace connection {

Manager::Manager() {
  count_ = 0;
  uint16_t i;
  for (i = 0; i < CONNECTION_MAX; ++i) {
    connectionids_[i] = ID_INVALID;
  }
}

Manager::~Manager() {
  __ENTER_FUNCTION
    cleanup();
  __LEAVE_FUNCTION
}

void Manager::cleanup() {
  count_ = 0;
  uint16_t i;
  //for (i = 0; i < sizeof(connectionids_); ++i) {
  //上面的注释是一个错误的用法，它代表数组的大小，却不是数组的容量
  for (i = 0; i < CONNECTION_MAX; ++i) {
    connectionids_[i] = ID_INVALID;
  }
}

bool Manager::heartbeat(uint32_t time) {
  __ENTER_FUNCTION
    USE_PARAM(time);
    bool result = true;
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::add(Base* connection) {
  __ENTER_FUNCTION
    Assert(connection);
    if (ID_INVALID == connectionids_[count_]) {
      connectionids_[count_] = connection->getid();
      connection->set_managerid(count_);
      ++count_;
      Assert(count_ < CONNECTION_MAX);
    }
    else {
      Assert(false);
    }
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Manager::add(int16_t id) {
  __ENTER_FUNCTION
    USE_PARAM(id);
    //not used
    Assert(false);
  __LEAVE_FUNCTION
    return false;
}

void Manager::remove(int16_t id) {
  __ENTER_FUNCTION
    //remember this function will completed in child
    Assert(count_ > 0);
    USE_PARAM(id);
  __LEAVE_FUNCTION
}

int16_t* Manager::get_allid() {
  return connectionids_;
}

uint16_t Manager::getcount() {
  return count_;
}

bool Manager::hash() {
  bool result = connectionids_[0] != ID_INVALID;
  return result;
}

} //namespace connection

} //namespace pap_server_common_net
