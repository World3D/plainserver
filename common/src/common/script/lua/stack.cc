#include "common/base/string.h"
#include "common/base/log.h"
#include "common/script/lua/stack.h"

namespace ps_common_script {

namespace lua {

StackStep::StackStep() {
  __ENTER_FUNCTION
    reset();
  __LEAVE_FUNCTION
}

StackStep::~StackStep() {
  __ENTER_FUNCTION
    reset();
  __LEAVE_FUNCTION
}

void StackStep::reset() {
  __ENTER_FUNCTION
    scriptid_ = ID_INVALID;
    memset(functionname_, 0, sizeof(functionname_));
  __LEAVE_FUNCTION
}

Stack Stack::run_[SCRIPT_LUA_SCENE_MAX];

Stack::Stack() {
  __ENTER_FUNCTION
    reset();
  __LEAVE_FUNCTION
}

Stack::~Stack() {
  __ENTER_FUNCTION
    reset();
 __LEAVE_FUNCTION
}

void Stack::reset() {
  __ENTER_FUNCTION
    currentstep_ = 0;
    for (int32_t i = 0; i < SCRIPT_LUA_STACK_STEP_MAX; ++i) {
      step_[i].reset();
    }
  __LEAVE_FUNCTION
}

bool Stack::stepenter(const char* functionname, int32_t scriptid) {
  __ENTER_FUNCTION
    using namespace ps_common_base;
    if (currentstep_ >= SCRIPT_LUA_STACK_STEP_MAX) {
      SLOW_ERRORLOG("luaerror",
                    "[script][lua] (Stack::stepenter)"
                    " out of stack: %s %d",
                    functionname,
                    scriptid);
      return false;
    }
    step_[currentstep_].scriptid_ = scriptid;
    string::safecopy(step_[currentstep_].functionname_, 
                     functionname, 
                     SCRIPT_LUA_STACK_FUNCTION_LENGTH_MAX);
    ++currentstep_;
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool Stack::stepleave() {
  __ENTER_FUNCTION
    if (currentstep_ <= 0) {
      SLOW_ERRORLOG("luaerror",
                    "[script][lua] (Stack::stepleave) low stack");
      return false;
    }
    --currentstep_;
    return true;
  __LEAVE_FUNCTION
    return false;
}

} //namespace lua

} //namespace ps_common_script
