/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id packetfactory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2014-1-3 10:11:38
 * @uses server and client net packet factory class interface
 */
#ifndef PS_COMMON_NET_PACKET_FACTORY_H_
#define PS_COMMON_NET_PACKET_FACTORY_H_

#include "common/net/config.h"

namespace ps_common_net {

namespace packet {

class Factory {

 public:
   virtual ~Factory() {};
   virtual Base* createpacket() = 0;
   virtual uint16_t get_packetid() const = 0;
   virtual uint32_t get_packet_maxsize() const = 0;

};

}; //namespace packet

}; //namespace ps_common_net

#endif //PS_COMMON_NET_PACKET_FACTORY_H_
