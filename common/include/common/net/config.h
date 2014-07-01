/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id config.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-31 17:34:43
 * @uses server and client net model base config file
 */
#ifndef PS_COMMON_NET_CONFIG_H_
#define PS_COMMON_NET_CONFIG_H_

#include "common/base/config.h"

#define NET_OVER_SERVER_MAX 256
#define NET_ONESTEP_ACCEPT_DEFAULT 50 //ÿ֡���������ӵ�Ĭ��ֵ

namespace ps_common_net {

namespace packet {
class Base;
class Factory;
class FactoryManager;
}; //namespace packet

namespace connection {
class Base;
class Server;
class Pool;
class Manager;
}; //namespace connection

namespace socket {

class Base;
class Server;
class Stream;
class InputStream;
class OutputStream;

typedef struct {
  char* buffer;
  uint32_t bufferlength;
  uint32_t bufferlength_max;
  uint32_t headlength;
  uint32_t taillength;
} streamdata_t;

typedef struct {
  unsigned char* in;
  uint32_t insize;
  unsigned char* out;
  uint32_t outsize;
  unsigned char const* key;
  uint32_t keysize;
  uint32_t param[2];
} encodeparam_t;

}; //namespace socket

}; //namespace ps_common_net

#endif //PS_COMMON_NET_CONFIG_H_
