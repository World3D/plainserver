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
#ifndef PAP_COMMON_NET_CONFIG_H_
#define PAP_COMMON_NET_CONFIG_H_

#include "common/base/type.h"

#define CONNECTION_MAX 1024
#define CONNECTION_CACHESIZE_MAX 1024
#define CONNECTION_KICKTIME 6000000 //������ʱ����Ͽ�����
#define CONNECTION_INCOME_KICKTIME 60000

typedef enum {
  kPacketFlagNone = 0,
  kPacketFlagRemove,
} packetflag_enum;

#endif //PAP_COMMON_NET_CONFIG_H_
