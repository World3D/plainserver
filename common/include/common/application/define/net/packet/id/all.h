/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id all.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2014/06/23 11:17
 * @uses 游戏服务器网络包ID的定义，彻底改变天龙与武侠的设计模式，不过这里需要
 *       包含游戏基本定义中的宏，单独包含进来即可，不用担心ID重复
 *       （看似有局限，其实可以任意扩展）
 */
#ifndef PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_ALL_H_
#define PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_ALL_H_

#include "common/application/define/net/packet/id/config.h"

#include "common/application/define/net/packet/id/clientlogin.h"
#include "common/application/define/net/packet/id/clientserver.h"
#include "common/application/define/net/packet/id/gatewaylogin.h"
#include "common/application/define/net/packet/id/logincenter.h"
#include "common/application/define/net/packet/id/servercenter.h"
#include "common/application/define/net/packet/id/serverserver.h"

#endif //PS_COMMON_APPLICATION_DEFINE_NET_PACKET_ID_ALL_H_
