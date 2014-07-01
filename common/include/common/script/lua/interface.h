/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id system.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2014/06/26 16:48
 * @uses script lua module system class(script interface)
 *       lua脚本系统基础接口，如需扩展，继承该类
 */
#ifndef PS_COMMON_SCRIPT_LUA_INTERFACE_H_
#define PS_COMMON_SCRIPT_LUA_INTERFACE_H_

#include "common/script/lua/config.h"
#include "common/base/hashmap/template.h"
#include "common/script/cache/base.h" 
#include "common/script/lua/vm.h"
#include "common/script/lua/stack.h"

namespace ps_common_script {

namespace lua {

class Interface {

 public:
   Interface();
   ~Interface();


 public:
   static bool lua_reloadscript_always_;
   static bool lua_recordscript_step_;
   static const char *kLuaScriptStepFileName;
   static const int32_t kLuaScriptCountMax;

 public:
   void init();
   void release();
   bool find_function(lua_State *L, const char *name);
   bool verify_function(lua_State *L, const char **names);
   void enter_runstep(int32_t scriptid, 
                      const char *functionname);
   void leave_runstep(int32_t scriptid, 
                      const char *functionname);
   bool reloadscript(int32_t scriptid);
   void *getscript_byid(int32_t scriptid);
   bool addscript(int32_t scriptid, void *data);
   static cache::Base *getscript_filedata(int32_t scriptid);

 public:
   bool loadscript(const char *filename);
   void set_globalfile(const char *filename);
   void set_rootpath(const char *path);
   void set_workpath(const char *path);

 public:
   static bool check_paramnumber(lua_State *L, int32_t count);
   static bool is_paramnumber(lua_State *L, 
                              int32_t index, 
                              const char *function_name);
   static bool is_paramstring(lua_State *L,
                              int32_t index,
                              const char *function_name);
   static int32_t getscript_stepid(lua_State *L);
   static void mark_scriptname(lua_State *L, const char* scriptname);
   static void check_scriptvalid(void *file, 
                                 int32_t scriptid, 
                                 const char *function_name);
   //static void dumpstack();

 public:
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2,
                              int64_t param3);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2,
                              int64_t param3,
                              int64_t param4);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2,
                              int64_t param3,
                              int64_t param4,
                              int64_t param5);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2,
                              int64_t param3,
                              int64_t param4,
                              int64_t param5,
                              int64_t param6);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              int64_t param2,
                              int64_t param3,
                              int64_t param4,
                              int64_t param5,
                              int64_t param6,
                              int64_t param7);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              float param2,
                              float param3);
   int64_t run_scriptfunction(int32_t scriptid, 
                              const char *function_name,
                              int64_t param0,
                              int64_t param1,
                              const char *param2,
                              const char *param3);

 public:
   const char *get_rootpath();

 protected:
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            int64_t param3,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            int64_t param3,
                            int64_t param4,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            int64_t param3,
                            int64_t param4,
                            int64_t param5,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            int64_t param3,
                            int64_t param4,
                            int64_t param5,
                            int64_t param6,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            int64_t param2,
                            int64_t param3,
                            int64_t param4,
                            int64_t param5,
                            int64_t param6,
                            int64_t param7,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            float param2,
                            float param3,
                            bool load = true);
   int64_t run_filefunction(const char *filename, 
                            const char *function_name,
                            int64_t param0,
                            int64_t param1,
                            const char *param2,
                            const char *param3,
                            bool load = true);

 private:
   VM VM_;
   ps_common_base::hashmap::Template<int32_t, void *> script_loaded_;
   char global_filename_[FILENAME_MAX];

};
  
}; //namespace lua

}; //namespace ps_common_script


#endif //PS_COMMON_SCRIPT_LUA_INTERFACE_H_
