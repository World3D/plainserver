/**
 * PLAIN SERVER Engine ( https://github.com/viticm/plainserver )
 * $Id database.h
 * @link https://github.com/viticm/plianserver for the canonical source repository
 * @copyright Copyright (c) 2014- viticm( viticm.ti@gmail.com )
 * @license
 * @user viticm<viticm.ti@gmail.com>
 * @date 2014/06/26 17:21
 * @uses as database class
 */
#ifndef PS_COMMON_FILE_DATABASE_H_
#define PS_COMMON_FILE_DATABASE_H_

#include "common/file/config.h"
#include "common/base/hashmap/config.h"

namespace ps_common_file {

class Database {

 public:
   typedef struct {
     uint32_t identify; //标示
     int32_t field_number; //列数
     int32_t record_number; //记录数
     int32_t string_block_size; //字符串区大小
   } file_head_t;
   
   typedef enum { //field type
     kTypeInt = 0,
     kTypeFloat = 1,
     kTypeString = 2,
   } field_type_enum;

   typedef std::vector<field_type_enum> field_type;
   
   //字段数据，即excel的一个单元格
   // 读取的顺序根据从左到右，自上而下的顺序读取，即以行读取
   // 注："[]" 表示excel一个单元格，下面的例子为三列数据 
   // 表格的结构体的数据类型为int32_t、const char *、float三种
   // [value1] [value2] [value3]
   // [value4] [value5] [value6]
   union field_data {
     float float_value;
     int32_t int_value;
     const char* string_value; //can't change excel value in memory
     field_data() {/** do nothing **/}
     field_data(float value) {float_value = value;}
     field_data(int32_t value) {int_value = value;}
     field_data(const char* value) {string_value = value;}
   };

   typedef std::vector<field_data> data_buffer;

 public:
   Database(uint32_t id);
   virtual ~Database();

 public:
   bool open_from_txt(const char* filename);
   bool open_from_memory(const char* memory, 
                         const char* end, 
                         const char* filename = NULL);
   virtual const field_data* search_index_equal(int32_t index) const;
   virtual const field_data* search_position(int32_t line, 
                                             int32_t column) const;
   virtual const field_data* search_first_column_equal(
       int32_t column, 
       const field_data &value) const;
   uint32_t get_id() const; //获得ID
   int32_t get_field_number() const;
   int32_t get_record_number() const;
   void create_index(int32_t column = 0, const char* filename = 0);

 public:
   static int32_t convert_string_tovector(const char* source,
                                          std::vector<std::string> &result,
                                          const char* key,
                                          bool one_key,
                                          bool ignore_empty);
   static const char* get_line_from_memory(char* str, 
                                           int32_t size, 
                                           const char* memory,
                                           const char* end);
   static bool field_equal(field_type_enum type, 
                           const field_data &a, 
                           const field_data &b);

 protected:
   typedef hash_map<int32_t, field_data*> field_hashmap;
   uint32_t id_;
   field_type type_;
   int32_t record_number_;
   int32_t field_number_;
   data_buffer data_buffer_;
   char* string_buffer_;
   int32_t string_buffer_size_;
   field_hashmap hash_index_;
   int32_t index_column_;

 protected:
   bool open_from_memory_text(const char* memory, 
                              const char* end, 
                              const char* filename = NULL);
   bool open_from_memory_binary(const char* memory, 
                                const char* end, 
                                const char* filename = NULL);

};

}; //namespace ps_common_file

#endif //PS_COMMON_FILE_DATABASE_H_
