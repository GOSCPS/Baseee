#ifndef _BASEEE_STRING_HPP_
#define _BASEEE_STRING_HPP_
/*baseee::string
 *string moudle
 *MIT License
 *coder:chhd 
 *update time:2020-7-22
 *
 *history:add trim and regex
 *add coder encoder
 * 
 */
#include <string>
#include <vector>
#include <regex>
#include <bitset>
#include "../Baseee.hpp"
#include "string.cpp"
#include "utfEncoder.cpp"

namespace baseee{
    namespace string{
        
        std::string trim(const std::string &s);

        std::vector<std::string> split(const std::string &regex_str,const std::string &s);

        std::vector<std::string> split(const std::regex &regex,const std::string &s);


        //Get UTF8 or UTF32
        int utf8ToUtf32(const char in[],const int in_length,char32_t out[],const int out_length);
        int utf32ToUtf8(const char32_t in[],const int in_length,char out[],const int out_length);

        //Get UTF16 or UTF8
        int utf8ToUtf16(const char in[],const int in_length,char16_t out[],const int out_length);
        int utf16ToUtf8(const char16_t in[],const int in_length,char out[],const int out_length);

        //get Base64
        int binToBase64();
        int base64Tobin();


    }
}

#endif