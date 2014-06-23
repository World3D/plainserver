/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id api.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.it@gmail.com>
 * @date 2014/06/19 14:25
 * @uses socket apis
 */
#ifndef PS_COMMON_NET_SOCKET_API_H_
#define PS_COMMON_NET_SOCKET_API_H_

#include "common/net/socket/config.h"

#if __LINUX__
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#elif __WINDOWS__
#include <winsock.h>
#include <ws2tcpip.h>
#endif
#include <errno.h>

#define SOCKET_ERROR_WOULD_BLOCK -100

//解决系统函数名和命名空间冲突
int32_t sys_socket(int32_t domain, int32_t type, int32_t protocol);

namespace ps_common_net {

namespace socket {

namespace api {

int32_t socketex(int32_t domain, int32_t type, int32_t protocol);

bool bindex(int32_t socketid, 
            const struct sockaddr* name, 
            uint32_t namelength);

bool connectex(int32_t socketid, 
               const struct sockaddr* name, 
               uint32_t namelength);

bool listenex(int32_t socketid, uint32_t backlog);

int32_t acceptex(int32_t socketid, 
                 struct sockaddr* addr, 
                 uint32_t* addrlength);

bool getsockopt_exb(int32_t socketid, 
                    int32_t level, 
                    int32_t optname, 
                    void* optval, 
                    uint32_t* optlength);

uint32_t getsockopt_exu(int32_t socketid, 
                        int32_t level, 
                        int32_t optname, 
                        void* optval, 
                        uint32_t* optlength);

bool setsockopt_ex(int32_t socketid,
                   int32_t level,
                   int32_t optname,
                   const void* optval,
                   uint32_t optlength);

int32_t sendex(int32_t socketid, 
               const void* buffer, 
               uint32_t length, 
               uint32_t flag);

int32_t sendto_ex(int32_t socketid, 
                  const void* buffer, 
                  int32_t length, 
                  uint32_t flag, 
                  const struct sockaddr* to, 
                  int32_t tolength);

int32_t recvex(int32_t socketid, 
               void* buffer, 
               uint32_t length, 
               uint32_t flag);

int32_t recvfrom_ex(int32_t socketid, 
                    void* buffer, 
                    int32_t length, 
                    uint32_t flag, 
                    struct sockaddr* from, 
                    uint32_t* fromlength);

bool closeex(int32_t socketid);

bool ioctlex(int32_t socketid, int64_t cmd, uint64_t* argp);

bool get_nonblocking_ex(int32_t socketid);

bool set_nonblocking_ex(int32_t socketid, bool on);

uint32_t availableex(int32_t socketid);

bool shutdown_ex(int32_t socketid, int32_t how);

int32_t selectex(int32_t maxfdp, 
                 fd_set* readset, 
                 fd_set* writeset, 
                 fd_set* exceptset, 
                 struct timeval* timeout);

int32_t getsockname_ex(int32_t socketid, 
                       struct sockaddr* name, 
                       int32_t* namelength);

int32_t getlast_errorcode();
void getlast_errormessage(char* buffer, uint16_t length);

}; //namespace api

}; //namespace socket

}; //namespace ps_common_net

#endif //PS_COMMON_NET_SOCKET_API_H_
