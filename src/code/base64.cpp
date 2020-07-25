#ifndef _BASEEE_BASE64_CPP_
#define _BASEEE_BASE64_CPP_
/*baseee::code
 *code base64 moudle
 *MIT License
 *coder:chhdao 
 */
#include "code.hpp"
#include "../Baseee.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

namespace baseee{
    namespace code{
        int binToBase64(const char in[],const int in_length,char out[],const int out_length){
            const char base64_table[65]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

            int ptr=0,out_ptr=0;
            if(out_length >= (in_length % 3 == 0 ? (in_length/3)*4 : (in_length/3+1)*4)) ;else return baseee::BUFFER_ERROR;

            while(ptr < in_length){

                if(ptr+2 < in_length){
                    std::bitset<24> buff(std::bitset<8>(in[ptr]).to_string() + std::bitset<8>(in[ptr+1]).to_string() + std::bitset<8>(in[ptr+2]).to_string());
                    std::bitset<6> head(buff.to_string().substr(18,6));
                    std::bitset<6> also(buff.to_string().substr(12,6));
                    std::bitset<6> heart(buff.to_string().substr(6,6));
                    std::bitset<6> end(buff.to_string().substr(0,6));

                    out[out_ptr+3] = base64_table[static_cast<uint8_t>(head.to_ulong())];
                    out[out_ptr+2] = base64_table[static_cast<uint8_t>(also.to_ulong())];
                    out[out_ptr+1] = base64_table[static_cast<uint8_t>(heart.to_ulong())];
                    out[out_ptr] = base64_table[static_cast<uint8_t>(end.to_ulong())];

                    out_ptr+=4;
                    ptr+=3;
                    continue;
                }
                else if(ptr+1 < in_length){
                    std::bitset<24> buff(std::bitset<8>(in[ptr]).to_string() + std::bitset<8>(in[ptr+1]).to_string() + "00000000"/*std::bitset<8>(in[ptr+2]).to_string()*/);
                    std::bitset<6> head(buff.to_string().substr(18,6));
                    std::bitset<6> also(buff.to_string().substr(12,6));
                    std::bitset<6> heart(buff.to_string().substr(6,6));
                    std::bitset<6> end(buff.to_string().substr(0,6));

                    out[out_ptr+3] = base64_table[static_cast<uint8_t>(head.to_ulong())];
                    out[out_ptr+2] = base64_table[static_cast<uint8_t>(also.to_ulong())];
                    out[out_ptr+1] = base64_table[static_cast<uint8_t>(heart.to_ulong())];
                    out[out_ptr] = base64_table[static_cast<uint8_t>(end.to_ulong())];

                    out[out_ptr+3] = '=';
                    out_ptr+=4;
                    ptr+=3;

                    break;
                }
                else if(ptr < in_length){
                    std::bitset<24> buff(std::bitset<8>(in[ptr]).to_string() + "0000000000000000"/*std::bitset<8>(in[ptr+1]).to_string() + std::bitset<8>(in[ptr+2]).to_string()*/);
                    std::bitset<6> head(buff.to_string().substr(18,6));
                    std::bitset<6> also(buff.to_string().substr(12,6));
                    std::bitset<6> heart(buff.to_string().substr(6,6));
                    std::bitset<6> end(buff.to_string().substr(0,6));

                    out[out_ptr+3] = base64_table[static_cast<uint8_t>(head.to_ulong())];
                    out[out_ptr+2] = base64_table[static_cast<uint8_t>(also.to_ulong())];
                    out[out_ptr+1] = base64_table[static_cast<uint8_t>(heart.to_ulong())];
                    out[out_ptr] = base64_table[static_cast<uint8_t>(end.to_ulong())];

                    out[out_ptr+3] = '=';
                    out[out_ptr+2] = '=';
                    out_ptr+=4;
                    ptr+=3;

                    break;
                }

            else return baseee::RUNTIME_ERROR;

            }
        return baseee::SUCCESS;
        }


        int base64ToBin(const char in[],const int in_length,char out[],const int out_length){
            if(in_length%4 != 0) return baseee::BUFFER_ERROR;
            if((in_length/4) *3 > out_length) return baseee::BUFFER_ERROR;
            std::string base64_table("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

            
            for(int ptr=0,out_ptr=0;ptr < in_length;ptr+=4,out_ptr+=3){

                if(ptr+3 < in_length){

                std::bitset<6> source_head(base64_table.find(in[ptr]));
                std::bitset<6> source_also(base64_table.find(in[ptr+1]));
                std::bitset<6> source_end;
                std::bitset<6> source_heart;
                in[ptr+2] == '=' ? source_heart=std::bitset<6>("00000000") : source_heart=std::bitset<6>(base64_table.find(in[ptr+2]));
                in[ptr+3] == '=' ? source_end=std::bitset<6>("00000000") : source_end=std::bitset<6>(base64_table.find(in[ptr+3]));

                std::bitset<24> out_buf(source_head.to_string() + source_also.to_string() + source_heart.to_string() + source_end.to_string());
                std::bitset<8> out_head(out_buf.to_string().substr(16,8));
                std::bitset<8> out_middle(out_buf.to_string().substr(8,8));
                std::bitset<8> out_end(out_buf.to_string().substr(0,8));

                out[out_ptr+2] = static_cast<short>(out_head.to_ulong());
                out[out_ptr+1] = static_cast<short>(out_middle.to_ulong());
                out[out_ptr] = static_cast<short>(out_end.to_ulong());

                continue;
                }

                else return baseee::RUNTIME_ERROR;
            }
            /*for(int a=0;a < out_length;a++){
                if(out[a] == '\0'){
                    for(int b=0;b+a+1 < out_length;a++){
                        out[a+b] = out[a+b+1];
                    }
                }
                else continue;
            }*/

            return baseee::SUCCESS;
        }
    }
}








#endif