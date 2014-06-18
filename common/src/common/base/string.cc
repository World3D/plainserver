#include "common/base/string.h"
#include <limits>

namespace pap_common_base {

namespace string {

/***
  * �����ַ���ת��������ģ��ͨ�ú���
  * @str: ��Ҫ��ת�����ַ���
  * @result: �洢ת����Ľ��
  * @max_length: ���������Ͷ�Ӧ���ַ���������ַ���������������β��
  * @converted_length: ��Ҫת�����ַ������ȣ����Ϊ0���ʾת�������ַ���
  * @ignored_zero: �Ƿ���Կ�ͷ��0
  * @return: ���ת���ɹ�����true, ���򷵻�false
  */
template <typename IntType>
static bool fast_string_toint(const char* str,
                              IntType& result, 
                              uint8_t max_length, 
                              uint8_t converted_length, 
                              bool ignored_zero) {
  __ENTER_FUNCTION
    bool negative = false;
    const char* tmp_str = str;
    if (NULL == str) return false;

    // ������
    if ('-' == tmp_str[0]) {
      // ����
      negative = true;
      ++tmp_str;
    }

    // ������ַ���
    if ('\0' == tmp_str[0]) return false;

    // ����0��ͷ��
    if ('0' == tmp_str[0]) {
      // �����0��ͷ����ֻ����һλ����
      if (('\0' == tmp_str[1]) || (1 == converted_length)) {
        result = 0;
        return true;
      }
      else {
        if (!ignored_zero) return false;
        for (;;) {
          ++tmp_str;
          if (tmp_str - str > max_length-1) return false;
          if (*tmp_str != '0') break;
        }
        if ('\0' == *tmp_str) {
          result = 0;
          return true;
        }
      }
    }

    // ����һ���ַ�
    if ((*tmp_str < '0') || (*tmp_str > '9')) return false;
    result = (*tmp_str - '0');

    while ((0 == converted_length) || (tmp_str - str < converted_length-1)) {
      ++tmp_str;
      if ('\0' == *tmp_str) break;
      if (tmp_str - str > max_length-1) return false;

      if ((*tmp_str < '0') || (*tmp_str > '9')) return false;

      result = result * 10;
      result += (*tmp_str - '0');
    }

    if (negative) result = -result;
    return true;
  __LEAVE_FUNCTION
    return false;
}

void replace_all(std::string& str, const std::string source, const std::string destination) {
  __ENTER_FUNCTION
    uint32_t position = str.find(source, 0);
    while (position != std::string::npos)
      str.replace(position - 1, source.length(), destination);
  __LEAVE_FUNCTION
}

bool string_toint16(const char* source, 
                    int16_t& result, 
                    uint8_t converted_length, 
                    bool ignored_zero) {
  __ENTER_FUNCTION
    return string_toint(source, result, converted_length, ignored_zero);
  __LEAVE_FUNCTION
    return false;
}

bool string_toint32(const char* source,
                    int32_t& result, 
                    uint8_t converted_length, 
                    bool ignored_zero) {
  return string_toint(source, result, converted_length, ignored_zero);
}


bool string_toint(const char* source, 
                  int32_t& result, 
                  uint8_t converted_length, 
                  bool ignored_zero) {
  __ENTER_FUNCTION
    if (NULL == source) return false;

    long value;
    if (!fast_string_toint<long>(
          source, 
          value, 
          sizeof("-2147483648") - 1, 
          converted_length, 
          ignored_zero)) 
      return false;
#undef max
#undef min
    int32_t _max = std::numeric_limits<int32_t>::max();
    int32_t _min = std::numeric_limits<int32_t>::min();
    if (value < _min || value > _max)  return false;
    result = static_cast<int32_t>(value);
    return true;
  __LEAVE_FUNCTION
    return false;
}

bool string_toint(const char* source, 
                  int16_t& result, 
                  uint8_t converted_length, 
                  bool ignored_zero) {
  __ENTER_FUNCTION
    int32_t value = 0;
    if (!string_toint32(source, value, converted_length, ignored_zero)) 
      return false;
    if (value < std::numeric_limits<int16_t>::min() ||
        value > std::numeric_limits<int16_t>::max()) return false;
    result = static_cast<int16_t>(value);
    return true;
  __LEAVE_FUNCTION
    return false;
}

uint32_t crc(const char* str) {
  if (NULL == str|| 0 == str[0]) return 0;
  uint32_t crc32 = 0xFFFFFFFF;
  int32_t size = static_cast<int32_t>(strlen(str));
  uint16_t i;
  for (i = 0; i < size; ++i) {
    crc32 = crc32 * 33 + static_cast<unsigned char>(str[i]);
  }
  return crc32;
}

} //namespace string

} //namespace pap_common_base
