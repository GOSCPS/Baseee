#ifndef _BASEEE_CODE_HPP_
#define _BASEEE_CODE_HPP_
/*baseee::code
 *code moudle
 *MIT License
 *coder:chhdao 
 */
#include "base64.cpp"
#include "code.cpp"
#include "../Baseee.hpp"

namespace baseee{
    namespace code{
        //get Base64
        int binToBase64(const char in[],const int in_length,char out[],const int out_length);
        int base64ToBin(const char in[],const int in_length,char out[],const int out_length);

        //Md5 
        //out 128Bit(16 char[])
        //!!!---已弃用---!!!
        uint32_t * md5(const char in[],const int in_length);

        
    }
}






#endif 