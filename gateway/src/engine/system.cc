#include "common/base/log.h"
#include "common/application/setting.h"
#include "engine/system.h"

engine::System *g_engine_system = NULL;

template <> 
engine::System *ps_common_base::Singleton<engine::System>::singleton_ = NULL;

namespace engine {

System *System::getsingleton_pointer() {
  return singleton_;
}

System &System::getsingleton() {
  Assert(singleton_);
  return *singleton_;
}

System::System() {
  //do nothing
}

System::~System() {
  //do nothing
}

ps_common_db::Manager *System::get_dbmanager() {
  __ENTER_FUNCTION
    ps_common_db::Manager *dbmanager = NULL;
    bool is_usethread = getconfig_boolvalue(ENGINE_CONFIG_DB_RUN_ASTHREAD);
    if (is_usethread) {
      dbmanager = dynamic_cast<ps_common_db::Manager *>(db_thread_);
    } else {
      dbmanager = db_manager_;
    }
    return dbmanager;
  __LEAVE_FUNCTION
    return NULL;
}

bool System::init() {
  __ENTER_FUNCTION
    DEBUGPRINTF("[engine] (System::init) start base module");
    if (!Kernel::init_base()) {
      SLOW_ERRORLOG("engine", 
                    "[engine] (System::init) base module failed");
      return false;
    }
    SLOW_LOG("engine", "[engine] (System::init) base module success");
    SLOW_LOG("engine", "[engine] (System::init) start setting module");
    if (!init_setting()) {
      SLOW_ERRORLOG("engine", 
        "[engine] (System::init) setting module failed");
      return false;
    }
    setconfig(ENGINE_CONFIG_BASEMODULE_HAS_INIT, true); //for kernel
    SLOW_LOG("engine", "[engine] (System::init) setting module success");
    bool result = Kernel::init();
    return result;
  __LEAVE_FUNCTION
    return false;
}

bool System::init_setting() {
  __ENTER_FUNCTION
    if (!APPLICATION_SETTING_POINTER)
      g_application_setting = new ps_common_application::Setting();
    if (!APPLICATION_SETTING_POINTER) return false;
    bool result = APPLICATION_SETTING_POINTER->init();
    return result;
  __LEAVE_FUNCTION
    return false;
}

} //namespace engine
