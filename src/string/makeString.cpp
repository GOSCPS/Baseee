#ifndef _BASEEE_MAKESTRING_CPP_
#define _BASEEE_MAKESTRING_CPP_
/*baseee::string
 *string UTF make moudle
 *MIT License
 *coder:chhdao 
 */

#include <bitset>
#include "string.hpp"
#include "../Baseee.hpp"

namespace baseee
{
    namespace string
    {
        
        int stringFlip(char16_t in[],const int in_length){
            for(int a=0;a < in_length;a++){
                std::bitset<16> i(in[a]);
                std::bitset<8> o_head(i.to_string().substr(0,8));
                std::bitset<8> o_end(i.to_string().substr(8,8));
                std::bitset<16> o(o_end.to_string() + o_head.to_string());
                in[a] = static_cast<uint16_t>(o.to_ulong());
            }
        return baseee::SUCCESS;
        }






    } // namespace string
    
} // namespace baseee


#endif