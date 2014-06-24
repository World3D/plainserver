/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id lextend.c
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2014/06/24 16:56
 * @uses lua script extend api
 */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "luaextend.h"

//---------------------------------------------------------------------------
//    lua_settableMember
//    �ú����������ɵĺ�����ɣ���ʵ�ָı�Lua Table�е�ĳ��������ֵ
//    Lua��Table�ı�����ʽ�����֣�һ������������ʽ��ʾ�� Table[1],����һ
//    �������ַ�������ʽ��ʾ����Table.Member��  
//    ͬʱ������ֵ������Number��String��CFun��
//    indexΪ�����ڶ�ջ�е�λ�á�
//---------------------------------------------------------------------------
int lua_settable_double_fromname(lua_State* L, 
                                 int index, 
                                 const char* membername, 
                                 double number) {
  if (!lua_istable(L, index)) return 0;
  lua_pushstring(L, membername);
  lua_pushnumber(L, number);
  lua_settable(L, index);
  return 1;
}

int lua_settable_int_fromname(lua_State* L, 
                              int index, 
                              const char* membername, 
                              int number) {

  if (!lua_istable(L, index)) return 0;
  lua_pushstring(L, membername);
  lua_pushnumber(L, (double)number);
  lua_settable(L, index);
  return 1;
}

int lua_settable_sttring_fromname(lua_State* L ,
                                  int index, 
                                  const char* membername, 
                                  char* string) {
  
  if (!lua_istable(L, index)) return 0;
  lua_pushstring(L, membername);
  lua_pushstring(L, string);
  lua_settable(L, index);
  return 1;
}

int lua_settable_string_fromid(lua_State * L, 
                               int index, 
                               int id, 
                               const char* string) {
  if (!lua_istable(L, index)) return 0;
  lua_pushnumber(L, (double)id);
  lua_pushstring(L, string);
  lua_settable(L, index);
  return 1;
}

int lua_settable_double_fromid(lua_State * L, 
                               int index, 
                               int id, 
                               double number) {
  if (!lua_istable(L, index)) return 0;
  lua_pushnumber(L, (double)id);
  lua_pushnumber(L, number);
  lua_settable(L, index);
  return 1;
}

int lua_settable_int_fromid(lua_State* L, 
                            int index, 
                            int id, 
                            int number) {
  if (!lua_istable(L, index)) return 0;
  lua_pushnumber(L, (double)id);
  lua_pushnumber(L, (double)number);
  lua_settable(L, index);
  return 1;
}

int lua_settable_CFunction_fromname(lua_State* L, 
                                    int index, 
                                    const char* membername, 
                                    lua_CFunction function) {
  if (!lua_istable(L, index)) return 0;
  lua_pushstring(L, membername);
  lua_pushcfunction(L, function);
  lua_settable(L, index);
  return 1;
}

int lua_settable_CFunction_fromid(lua_State* L, 
                                  int index, 
                                  int id, 
                                  lua_CFunction function) {
  if (!lua_istable(L, index)) return 0;
  lua_pushnumber(L, id);
  lua_pushcfunction(L, function);
  lua_settable(L, index);
  return 1;
}

int lua_getvalues_fromstack(lua_State* L, char * format, ...) {

  va_list vlist;
  double* number;
  const char* string;
  const char** str_pointer;
  
  int i = 0;
  int topindex = 0;
  int index = 0;
  int valuenum = 0; //format���ַ����ȣ���ʾ��Ҫȡ�Ĳ�������
  
  
  if (!L) return 0;
  
  topindex = lua_gettop(L);  
  valuenum = strlen(format);
  
  if (0 == topindex || 0 == valuenum) //����ջ�������ݻ�ȡ�����Ƿ���FALSE
    return 0;
  
  if (topindex < valuenum)
    index = 1 ;
  else
    index = topindex - valuenum + 1;
  {
    va_start(vlist, format);     
    
    while (format[i] != '\0') {
      
      switch (format[i]) {
        case 'n': { //����ֵΪ��ֵ��,Number,��ʱLuaֻ����double�ε�ֵ
          number = va_arg(vlist, double*);
          if (NULL == number) return 0;
          
          if (lua_isnumber(L, index )) {
            *number = lua_tonumber(L, index++);
          }
          else {
            return 0;
          }
          break;
        }
        case 's': { //�ַ�����
          str_pointer = va_arg(vlist, const char**);
          if (NULL == str_pointer) return 0;
          if (lua_isstring(L, index)) {
            string = lua_tostring(L, index++);
            *str_pointer = string;
          }
          else {
            return 0;
          }
          break;
        }
        default:
          break;
      }
      i++;  
    }
    va_end(vlist); /* reset variable arguments. */
  }
  return  1;
}

LUA_API int lua_execute(lua_State *L) {
    int status;
    status = lua_pcall(L, 0, LUA_MULTRET, 0);  /* call main */
    return status;
}
