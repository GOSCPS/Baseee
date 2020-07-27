#ifndef _BASEEE_CODE_CPP_
#define _BASEEE_CODE_CPP_
/*baseee::code
 *code moudle source
 *MIT License
 *coder:chhdao 
 */
#include "code.hpp"
#include <iostream>
#include <bitset>

namespace baseee{
    namespace code{
        int md5(const char in[],const int in_length,char out[]){
            unsigned long long A = 0x67452301;
            unsigned long long B = 0xEFCDAB89;
            unsigned long long C = 0x98BADCFE;
            unsigned long long D = 0x10325476;

            //填充
            unsigned long long length = in_length*8;
            while(length%512 != 448){
                ++length;
            }
            length-=in_length*8;
            length/=8;
            
            std::vector<std::bitset<8>> md(in_length+length);
            for(int a=0;a<in_length;a++) md.push_back(in[a]);
            md.push_back(std::bitset<8>("10000000"));
            for(int a=1;a<length;a++) md.push_back(std::bitset<8>("00000000"));

            std::bitset<64> o(in_length*8);
            for(int a=0;a < 8;a++)
            md.push_back(std::bitset<8>(o.to_string().substr(a*8,8)));

            std::cout << md.size()*8 << std::endl;









            return baseee::SUCCESS;
        }
    }
}


#endif