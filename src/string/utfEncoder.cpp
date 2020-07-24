#ifndef _BASEEE_UTFENCODER_CPP_
#define _BASEEE_UTFENCODER_CPP_


#include <string>
#include <vector>
#include <regex>
#include <bitset>
#include "../Baseee.hpp"


inline void BitChange(const std::bitset<8> a,std::bitset<32> &b,int c,int length){
    for(int d=0;d < length;++d){
        b[d+c] = a[d];
    }
    return;
}

inline void BitChange(const std::bitset<8> a,std::bitset<16> &b,int c,int length){
    for(int d=0;d < length;++d){
        b[d+c] = a[d];
    }
    return;
}
inline void BitChange(const std::bitset<16> a,std::bitset<32> &b,int c,int length){
    for(int d=0;d < length;++d){
        b[d+c] = a[d];
    }
    return;
}



namespace baseee{
    namespace string{
        int utf8ToUtf32(const char in[],const int in_length,char32_t out[],const int out_length){
            const std::bitset<8> UTF8_1_HEAD("10000000");//UTF8 use bit
            const std::bitset<8> IS_UTF8_1_HEAD("00000000");//UTF8 use bit of key

            const std::bitset<8> UTF8_2_HEAD("11100000");
            const std::bitset<8> IS_UTF8_2_HEAD("11000000");

            const std::bitset<8> UTF8_3_HEAD("11110000");
            const std::bitset<8> IS_UTF8_3_HEAD("11100000");

            const std::bitset<8> UTF8_4_HEAD("11111000");
            const std::bitset<8> IS_UTF8_4_HEAD("11110000");

            const std::bitset<8> UTF8_BODY("11000000");
            const std::bitset<8> IS_UTF8_BODY("10000000");

            

            int ptr=0,out_ptr=0;
            while(ptr < in_length && out_ptr < out_length){
                std::bitset<8> u8Bit(in[ptr]);
                std::bitset<32> u32Bit;
                u32Bit.reset();

                //Input 0xxxxxxx
                //Out xxxxxx
                if((u8Bit&UTF8_1_HEAD) == IS_UTF8_1_HEAD){
                    std::cout << "UTF8-1" << std::endl;
                    BitChange((u8Bit&(~UTF8_1_HEAD)),u32Bit,0,7);
                    out[out_ptr] = u32Bit.to_ulong();
                    ++ptr;
                    ++out_ptr;
                    continue;
                }

                //Input 110xxxxx 10xxxxxx
                //Out xxxxxxxxxxx
                else if(ptr+1 < in_length && (u8Bit&UTF8_2_HEAD) == IS_UTF8_2_HEAD){
                    std::cout << "UTF8-2" << std::endl;
                    BitChange((u8Bit&(~UTF8_2_HEAD)),u32Bit,6,5);
                    u8Bit = in[ptr+1];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,0,6);
                    out[out_ptr] = u32Bit.to_ulong();
                    ptr+=2;
                    ++out_ptr;
                    continue;
                }

                //Input 1110xxxx 10xxxxxx 10xxxxxx
                //Out xxxxxxxxxxxxxxxx
                else if(ptr+2 < in_length && (u8Bit&UTF8_3_HEAD) == IS_UTF8_3_HEAD){
                    std::cout << "UTF8-3" << std::endl;
                    BitChange((u8Bit&(~UTF8_3_HEAD)),u32Bit,12,4);
                    u8Bit = in[ptr+1];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,6,6);
                    u8Bit = in[ptr+2];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,0,6);
                    out[out_ptr] = u32Bit.to_ulong();
                    ptr+=3;
                    ++out_ptr;
                    continue;
                }

                //Input 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                //xxxxxxxxxxxxxxxxxxxxx
                else if(ptr+3 < in_length && (u8Bit&UTF8_4_HEAD) == IS_UTF8_4_HEAD){
                    std::cout << "UTF8-4" << std::endl;
                    BitChange((u8Bit&(~UTF8_4_HEAD)),u32Bit,18,3);
                    u8Bit = in[ptr+1];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,12,6);
                    u8Bit = in[ptr+2];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,6,6);
                    u8Bit = in[ptr+3];
                    BitChange((u8Bit&(~UTF8_BODY)),u32Bit,0,6);
                    out[out_ptr] = u32Bit.to_ulong();
                    ptr+=4;
                    ++out_ptr;
                    continue;
                }

                else return baseee::RUNTIME_ERROR;
            }

        return baseee::SUCCESS;
        }



        int utf8ToUtf16(const char in[],const int in_length,char16_t out[],const int out_length){
            const std::bitset<8> UTF8_1_HEAD("10000000");//UTF8 use bit
            const std::bitset<8> IS_UTF8_1_HEAD("00000000");//UTF8 use bit of key

            const std::bitset<8> UTF8_2_HEAD("11100000");
            const std::bitset<8> IS_UTF8_2_HEAD("11000000");

            const std::bitset<8> UTF8_3_HEAD("11110000");
            const std::bitset<8> IS_UTF8_3_HEAD("11100000");

            const std::bitset<8> UTF8_4_HEAD("11111000");
            const std::bitset<8> IS_UTF8_4_HEAD("11110000");

            const std::bitset<8> UTF8_BODY("11000000");
            const std::bitset<8> IS_UTF8_BODY("10000000");

            const std::bitset<16> IS_UTF16_LOW(std::string("1101110000000000"));
            const std::bitset<16> IS_UTF16_HIGH(std::string("1101100000000000"));
            const std::bitset<16> UTF16_LOW(std::string("1111110000000000"));
            const std::bitset<16> UTF16_HIGH(std::string("1111110000000000"));



            int ptr=0,out_ptr=0;

            while(ptr < in_length && out_ptr < out_length){
                std::bitset<8> utf8Bit(in[ptr]);
                std::bitset<16> utf16Bit;
                utf16Bit.reset();

                if((utf8Bit&UTF8_1_HEAD) == IS_UTF8_1_HEAD){
                    BitChange((utf8Bit&(~UTF8_1_HEAD)),utf16Bit,0,7);
                    out[out_ptr] = static_cast<short>(utf16Bit.to_ulong());
                    ++out_ptr;
                    ++ptr;
                    continue;
                }

                else if(ptr+1 < in_length && (utf8Bit&UTF8_2_HEAD) == IS_UTF8_2_HEAD){
                    BitChange((utf8Bit&(~UTF8_2_HEAD)),utf16Bit,6,5);
                    utf8Bit = in[ptr+1];
                    BitChange((utf8Bit&(~UTF8_BODY)),utf16Bit,0,6);
                    out[out_ptr] = static_cast<short>(utf16Bit.to_ulong());
                    ++out_ptr;
                    ptr=+2;
                    continue;
                }

                else if(ptr+2 < in_length && out_ptr+1 < out_length &&
                (utf8Bit&UTF8_3_HEAD) == IS_UTF8_3_HEAD){
                std::bitset<16> High(IS_UTF16_HIGH);
                std::bitset<16> Low(IS_UTF16_LOW);

                utf8Bit = in[ptr+2];
                BitChange((utf8Bit&(~UTF8_BODY)),Low,0,6);
                utf8Bit = in[ptr+1];
                BitChange((utf8Bit&(~UTF8_BODY)),Low,6,4);
                BitChange((utf8Bit&(~UTF8_BODY))>>4,High,0,2);
                utf8Bit = in[ptr];
                BitChange((utf8Bit&(~UTF8_3_HEAD)),High,2,4);

                out[out_ptr] = static_cast<short>(High.to_ulong());
                out[out_ptr+1] = static_cast<short>(Low.to_ulong());

                out_ptr+=2;
                ptr+=3;
                continue;
                }

                





                else return baseee::RUNTIME_ERROR;
            }

            return baseee::SUCCESS;
        }



    }
}



#endif