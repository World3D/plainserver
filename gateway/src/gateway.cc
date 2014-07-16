#include "common/base/time_manager.h"
#include "common/base/log.h"
#include "common/base/util.h"
#include "common/sys/process.h"
#include "engine/system.h"
#include "gateway.h"

#define PROCESS_ID_FILE "gateway.pid"

#if __LINUX__
void signal_handler(int32_t signal);
#elif __WINDOWS__
BOOL WINAPI signal_handler(DWORD event);
#endif

int32_t main(int32_t argc, char *argv[]) {
#if __WINDOWS__
  USE_PARAM(argc);
  USE_PARAM(argv);
  _CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
  system("color 02"); //color green
  system("mode con cols=120"); //cmd size
#endif
  /* process about { */
#if __LINUX__
  if (argc > 1 && 0 == strcmp(argv[1], "--daemon")) {
    ps_common_sys::process::daemon();
  } else if (argc > 1 && 0 == strcmp(argv[1], "--reloadscript")) {
    int32_t pid = ps_common_sys::process::getid(PROCESS_ID_FILE);
    DEBUGPRINTF("server(%d) will reload script", pid);
    return 0;
  } else if (argc > 1 && 0 == strcmp(argv[1], "--stop")) {
    bool result = ps_common_sys::process::waitexit(PROCESS_ID_FILE);
    return result ? 1 : 0;
  } else {
    ERRORPRINTF("----------------------------------------"
                "----------------------------------------");
    ERRORPRINTF("                                   [WARNING]");
    ERRORPRINTF(" server not run in daemon mode, "
                "it will be auto stop when user logout or session");
    ERRORPRINTF(" disconnect. should add daemon option to start server"
                " as daemon mode, such as:");
    DEBUGPRINTF("     %s --daemon", argv[0]);
    ERRORPRINTF("----------------------------------------"
                "----------------------------------------");
  }
#endif
  /* } process about */
#if __WINDOWS__
  WORD versionrequested;
  WSADATA data;
  int32_t error;
  versionrequested = MAKEWORD(2, 2);
  error = WSAStartup(versionrequested, &data);
#endif
  if (!ENGINE_SYSTEM_POINTER)
    g_engine_system = new engine::System();
  if (!ENGINE_SYSTEM_POINTER)
    ERRORPRINTF("[gateway] ENGINE_SYSTEM_POINTER is NULL");
  if (!ENGINE_SYSTEM_POINTER->init()) {
    return 1;
  }
  //初始化正确后再写入进程ID
  if (!ps_common_sys::process::writeid(PROCESS_ID_FILE)) {
    ERRORPRINTF("[gateway] process id file: %s write error", PROCESS_ID_FILE);
    return 1;
  }
#if __LINUX__  
  signal(SIGINT, signal_handler);
  signal(SIGUSR1, signal_handler);
#elif __WINDOWS__
  ps_common_base::util::disable_windowclose(); //屏蔽关闭按钮
  if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)signal_handler, TRUE) != TRUE) {
    ERRORPRINTF("[gateway] can't install signal handler");
    return 1;
  }
#endif  
  ENGINE_SYSTEM_POINTER->run(); //网络线程是来阻塞主线程的，所以不要轻易设置其独立线程模式
  SAFE_DELETE(g_engine_system);
  remove(PROCESS_ID_FILE);
  //engine_kernel.stop();
  return 0;
}

#if __LINUX__ /* { */
void signal_handler(int32_t signal) {
  //处理前台模式信号
  static uint32_t last_signaltime = 0;
  uint32_t currenttime = TIME_MANAGER_POINTER->get_current_time();
  if (signal == SIGINT) {
    if (currenttime - last_signaltime > 10 * 1000) {
      DEBUGPRINTF(
          "\r[gateway] (signal_handler) got SIGINT[%d] engine will reload!", 
          signal);
      //engine_kernel.stop();
    } else {
      WARNINGPRINTF(
          "\r[gateway] (signal_handler) got SIGINT[%d] engine will stop!", 
          signal);
      ENGINE_SYSTEM_POINTER->stop(); 
    }
  }
  //处理后台模式信号
  if (signal == SIGUSR1) {
    WARNINGPRINTF(
        "\r[gateway] (signal_handler) got SIGUSR1[%d] engine will stop!", 
        signal);
    ENGINE_SYSTEM_POINTER->stop();
  }
  last_signaltime = currenttime;
}
#elif __WINDOWS__ /* }{ */
BOOL WINAPI signal_handler(DWORD event) {
  static uint32_t last_signaltime = 0;
  uint32_t currenttime = TIME_MANAGER_POINTER->get_current_time();
  switch (event) {
    case CTRL_C_EVENT: {
      if (currenttime - last_signaltime > 10 * 1000) {
        DEBUGPRINTF(
            "[gateway] (signal_handler) CTRL+C received, engine will reload!");
      } else {
        WARNINGPRINTF(
            "[gateway] (signal_handler) CTRL+C received, engine will stop!");
        ENGINE_SYSTEM_POINTER->stop();
      }
      break;
    }
    default:
      break;
  }
  last_signaltime = currenttime;
  return TRUE;
}
#endif /* } */
