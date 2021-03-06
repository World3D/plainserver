/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id gatewaylogin.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2014/06/23 19:14
 * @uses plain server packets id define of gateway and login server
 */
#ifndef PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_GATEWAYLOGIN_H_
#define PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_GATEWAYLOGIN_H_

#include "common/application/define/net/packet/id/config.h"

APPLICATION_DEFINE_NET_PACKET_ID_NAMESPACE_START

namespace gatewaylogin { //登陆服务器与验证服务器公用

typedef enum {
  kFirst = GATEWAYLOGIN_PACKETID_MIN, //起始ID
  kLast, /* the last packetid */
  kMax = GATEWAYLOGIN_PACKETID_MAX,
 } packetid_enum;

}; //namespace gatewaylogin

namespace gateway_tologin { //验证服务器发送给登陆服务器

typedef enum {
  kFirst = GATEWAY_TOLOGIN_PACKETID_MIN,
  kResultAuth, /*begin {*/
  kLast, /* the last packetid */
  kMax = GATEWAY_TOLOGIN_PACKETID_MAX, /*end }*/
} packetid_enum;

}; //namespace gateway_tologin

namespace login_togateway { //登陆服务器发送给验证服务器

typedef enum {
  /*begin {*/
  kFirst = LOGIN_TOGATEWAY_PACKETID_MIN,
  kAskAuth,
  kLast, /* the last packetid */
  kMax = LOGIN_TOGATEWAY_PACKETID_MAX,
  /*end }*/
} packetid_enum;

}; //namespace login_togateway

APPLICATION_DEFINE_NET_PACKET_ID_NAMESPACE_END

#endif //PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_GATEWAYLOGIN_H_
