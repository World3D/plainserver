#include "common/engine/thread/db.h"

using namespace ps_common_engine::thread;

DB::DB(dbconnector_type_t connector_type) : 
  ps_common_db::Manager(connector_type) {
  isactive_ = false;
}

DB::~DB() {
  //do nothing
}

bool DB::init(const char *connection_or_dbname,
              const char *username,
              const char *password) {
  __ENTER_FUNCTION
    using namespace ps_common_db;
    isactive_  = Manager::init(connection_or_dbname, username, password);
    return isactive_;
  __LEAVE_FUNCTION
    return false;
}

void DB::run() {
  __ENTER_FUNCTION
    using namespace ps_common_db;
    while (isactive()) Manager::check_db_connect();
  __LEAVE_FUNCTION
}

bool DB::isactive() {
  return isactive_;
}

void DB::stop() {
  isactive_ = false;
}

void DB::quit() {
  //do nothing
}
