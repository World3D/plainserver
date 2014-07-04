/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id base.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.it@gmail.com>
 * @date 2014/06/19 14:51
 * @uses socket base class
 */
#ifndef PS_COMMON_NET_SOCKET_BASE_H_
#define PS_COMMON_NET_SOCKET_BASE_H_

#include "common/net/socket/api.h"

namespace ps_common_net {

namespace socket {

class Base {
 
 public:
   Base();
   Base(const char* host, uint16_t port);
   virtual ~Base();

 public:
   int32_t socketid_;
   char host_[IP_SIZE];
   uint16_t port_;

 public: //socket base operate functions
   bool create();
   void close();
   bool connect(); //use self host_ and port_
   bool connect(const char* host, uint16_t port);
   bool reconnect(const char* host, uint16_t port);
   int32_t send(const void* buffer, uint32_t length, uint32_t flag = 0);
   int32_t receive(void* buffer, uint32_t length, uint32_t flag = 0);
   uint32_t available() const;
   int32_t accept(uint16_t port, const char *host = NULL);
   int32_t fastaccept();
   bool bind(const char *ip = NULL);
   bool bind(uint16_t port, const char *ip = NULL);
   bool listen(uint32_t backlog);
   static int32_t select(int32_t maxfdp, 
                         fd_set* readset, 
                         fd_set* writeset, 
                         fd_set* exceptset,
                         timeval* timeout);

 public: //socket check and set functions
   uint32_t getlinger() const;
   bool setlinger(uint32_t lingertime);
   bool is_reuseaddr() const;
   bool set_reuseaddr(bool on = true);
   uint32_t getlast_errorcode() const;
   void getlast_errormessage(char* buffer, uint16_t length) const;
   bool iserror() const; //socket if has error
   bool is_nonblocking() const;
   bool set_nonblocking(bool on = true);
   uint32_t getreceive_buffersize() const;
   bool setreceive_buffersize(uint32_t size);
   uint32_t getsend_buffersize() const;
   bool setsend_buffersize(uint32_t size);
   uint16_t getport() const;
   uint64_t getu64host() const;
   bool isvalid() const;
   int32_t getid() const;

};

}; //namespace socket

}; //namespace ps_common_net

#include "common/net/socket/extend.inl"

#endif //PS_COMMON_NET_SOCKET_BASE_H_
