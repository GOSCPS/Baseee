#ifndef _BASEEE_STRING_HPP_
#define _BASEEE_STRING_HPP_
/*baseee::string
 *string moudle
 *MIT License
 *coder:chhdao 
 */
#include <string>
#include <vector>
#include <regex>
#include <bitset>
#include "../Baseee.hpp"
#include "string.cpp"
#include "makeString.cpp"
#include "utfEncoder.cpp"

namespace baseee{
    namespace string{
        //tools，可用
        std::string trim(const std::string &s);

        std::vector<std::string> split(const std::string &regex_str,const std::string &s);

        std::vector<std::string> split(const std::regex &regex,const std::string &s);


        //UTF32及UTF8函数，可用
        int utf8ToUtf32(const char in[],const int in_length,char32_t out[],const int out_length);
        int utf32ToUtf8(const char32_t in[],const int in_length,char out[],const int out_length);

        //UTF16及UTF8的函数，暂未实现
        int utf8ToUtf16(const char in[],const int in_length,char16_t out[],const int out_length);
        int utf16ToUtf8(const char16_t in[],const int in_length,char out[],const int out_length);

        //反转字符,UTF16-BE-LE
        int stringFlip(char16_t in[],const int in_length);

    }
}

#endif