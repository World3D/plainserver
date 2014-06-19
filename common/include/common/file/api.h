/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id api.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.it@gmail.com>
 * @date 2014/06/19 14:12
 * @uses file extend apis
 */
#ifndef PS_COMMON_FILE_API_H_
#define PS_COMMON_FILE_API_H_

#include "common/file/config.h"

#if __LINUX__ /* { */
#include <sys/types.h>  // for open()
#include <sys/stat.h>   // for open()
#include <unistd.h>     // for fcntl()
#include <fcntl.h>      // for fcntl()
#include <sys/ioctl.h>  // for ioctl()
#include <errno.h>      // for errno
#elif __WINDOWS__ /* }{ */
#include <io.h>         // for _open()
#include <fcntl.h>      // for _open()/_close()/_read()/_write()...
#endif /* } */

namespace ps_common_file {

namespace api {

int32_t openex(const char* filename, int32_t flag);
int32_t openmode_ex(const char* filename, int32_t flag, int32_t mode);
void closeex(int32_t fd);
uint32_t readex(int32_t fd, void* buffer, uint32_t length);
uint32_t writeex(int32_t fd, const void* buffer, uint32_t length);
int32_t fcntlex(int32_t fd, int32_t cmd);
int32_t fcntlarg_ex(int32_t fd, int32_t cmd, int32_t arg);
bool get_nonblocking_ex(int32_t socketid);
void set_nonblocking_ex(int32_t socketid, bool on);
void ioctlex(int32_t fd, int32_t request, void* argp);
uint32_t availableex(int32_t fd);
int32_t dupex(int32_t fd);
int64_t lseekex(int32_t fd, uint64_t offset, int32_t whence);
int64_t tellex(int32_t fd);

}; //namespace api

}; //namespace ps_common_file

#endif //PS_COMMON_FILE_API_H_
