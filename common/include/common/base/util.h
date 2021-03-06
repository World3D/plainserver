/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id util.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.it@gmail.com>
 * @date 2014/06/18 13:46
 * @uses base util module
 */
#ifndef PS_COMMON_BASE_UTIL_H_
#define PS_COMMON_BASE_UTIL_H_

#include "common/base/config.h"
#include "common/base/md5.h"

namespace ps_common_base {

namespace util {

char value_toascii(char in);
char ascii_tovalue(char in);
bool binary_tostring(const char* in, uint32_t in_length, char* out);
bool string_tobinary(const char* in, 
                     uint32_t in_length, 
                     char* out, 
                     uint32_t out_limit, 
                     uint32_t &out_length);
void sleep(uint32_t million_seconds);
/**
 * 由byte类型获得单位大小字符串如：32bytes,32kb,32mb,32gb,32t
 * type: -1 获得大于1最大单位字符串，如1023byte则返回1023bytes而非kb
 * type: 0 - 4 分别对应单位bytes、kb、mb、gb、t，
 *       不过规则是返回最至少大于0.01单位的字符串
 */ 
void get_sizestr(uint64_t size, 
                 char* buffer, 
                 uint32_t length, 
                 int8_t type = -1);

void path_tounix(char* buffer, uint16_t length);

//获取当前执行文件名
void get_module_filename(char *buffer, size_t size);

void disable_windowclose();

bool makedir(const char *path, uint16_t mode = 755);

uint64_t touint64(uint32_t high, uint32_t low);

uint32_t get_highsection(uint64_t value);

uint32_t get_lowsection(uint64_t value);

} //namespace util

} //namespace ps_common_base

#endif //PS_COMMON_BASE_UTIL_H_
