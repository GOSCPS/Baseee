#ifndef _BASEEE_UTFENCODER_CPP_
#define _BASEEE_UTFENCODER_CPP_
/*baseee::string
 *string UTF encoder moudle
 *MIT License
 *coder:chhdao 
 */

#include <string>
#include <vector>
#include <regex>
#include <bitset>
#include "../Baseee.hpp"

//tools
//move bit
inline void BitChange(const std::bitset<8> a,std::bitset<32> &b,int c,int length){
    for(int d=0;d < length;++d){
        b[d+c] = a[d];
    }
    return;
}

inline void BitChange(const std::bitset<32> a,std::bitset<8> &b,int c,int length){
    for(int d=0;d < length;++d){
        b[d+c] = a[d];
    }
    return;
}



namespace baseee{
    namespace string{
        int utf8ToUtf32(const char in[],const int in_length,char32_t out[],const int out_length){
            const std::bitset<8> UTF8_1_HEAD("10000000");//UTF8 占用位
            const std::bitset<8> IS_UTF8_1_HEAD("00000000");//UTF8 固定位

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
                    BitChange((u8Bit&(~UTF8_1_HEAD)),u32Bit,0,7);
                    out[out_ptr] = u32Bit.to_ulong();
                    ++ptr;
                    ++out_ptr;
                    continue;
                }

                //Input 110xxxxx 10xxxxxx
                //Out xxxxxxxxxxx
                else if(ptr+1 < in_length && (u8Bit&UTF8_2_HEAD) == IS_UTF8_2_HEAD){
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


        int utf32ToUtf8(const char32_t in[],const int in_length,char out[],const int out_length){
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
            while(ptr > in_length && out_ptr > out_length){
                std::bitset<32> utf32Bit(in[ptr]);
                std::bitset<8> utf8Bit[4];
                for(auto &a:utf8Bit) a.reset();

                //1字节，utf8
                if(utf32Bit.to_ulong() <= static_cast<unsigned long>(0x00007f)){
                    BitChange(utf32Bit,utf8Bit[0],0,7);
                    out[out_ptr] = static_cast<short>(utf8Bit[0].to_ulong());
                    ++out_ptr;
                    ++ptr;
                    continue;
                }

                //2字节，utf8
                else if(out_ptr+1 < out_length && utf32Bit.to_ullong() <= static_cast<unsigned long>(0x0007ff)){
                    utf8Bit[1] = IS_UTF8_BODY;
                    utf8Bit[0] = IS_UTF8_2_HEAD;

                    BitChange(utf32Bit,utf8Bit[1],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[0],0,5);

                    out[out_ptr] = static_cast<short>(utf8Bit[0].to_ulong());
                    out[out_ptr+1] = static_cast<short>(utf8Bit[1].to_ulong());

                    out_ptr+=2;
                    ++ptr;
                    continue;
                }

                //三字节，utf8
                else if(out_ptr+2 < out_length && utf32Bit.to_ullong() <= static_cast<unsigned long>(0x00ffff)){

                    utf8Bit[2] = IS_UTF8_BODY;
                    utf8Bit[1] = IS_UTF8_BODY;
                    utf8Bit[0] = IS_UTF8_3_HEAD;

                    BitChange(utf32Bit,utf8Bit[2],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[1],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[0],0,4);

                    out[out_ptr] = static_cast<short>(utf8Bit[0].to_ulong());
                    out[out_ptr+1] = static_cast<short>(utf8Bit[1].to_ulong());
                    out[out_ptr+2] = static_cast<short>(utf8Bit[2].to_ulong());

                    out_ptr+=3;
                    ++ptr;
                    continue;
                }

                //四字节，utf8
                else if(out_ptr+3 < out_length && utf32Bit.to_ullong() <= static_cast<unsigned long>(0x10ffff)){

                    utf8Bit[3] = IS_UTF8_BODY;
                    utf8Bit[2] = IS_UTF8_BODY;
                    utf8Bit[1] = IS_UTF8_BODY;
                    utf8Bit[0] = IS_UTF8_4_HEAD;

                    BitChange(utf32Bit,utf8Bit[3],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[2],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[1],0,6);
                    utf32Bit>>6;
                    BitChange(utf32Bit,utf8Bit[0],0,3);

                    out[out_ptr] = static_cast<short>(utf8Bit[0].to_ulong());
                    out[out_ptr+1] = static_cast<short>(utf8Bit[1].to_ulong());
                    out[out_ptr+2] = static_cast<short>(utf8Bit[2].to_ulong());
                    out[out_ptr+3] = static_cast<short>(utf8Bit[3].to_ulong());

                    out_ptr+=4;
                    ++ptr;
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

            const std::bitset<6> UTF16_HIGH("110110");
            const std::bitset<6> UTF16_LOW("110111");

            int ptr=0,out_ptr=0;

            while(ptr < in_length && out_ptr < out_length){

                if(((std::bitset<8>(in[ptr]))&(UTF8_1_HEAD)) == IS_UTF8_1_HEAD){
                    out[out_ptr] = static_cast<uint16_t>((std::bitset<8>(in[ptr])&(~UTF8_1_HEAD)).to_ulong());
                    ++ptr;
                    ++out_ptr;
                    continue;
                }

                else if(ptr+1 < in_length && (std::bitset<8>(in[ptr])&(UTF8_2_HEAD)) == IS_UTF8_2_HEAD){
                    std::bitset<8> one(in[ptr]),two(in[ptr+1]);
                    //one &= (~UTF8_2_HEAD);//5
                    //two &= (~UTF8_BODY);//6

                    std::bitset<16> buf("00000" + one.to_string().substr(3,5) + two.to_string().substr(2,6));

                    out[out_ptr] = static_cast<uint16_t>(buf.to_ulong());
                    ++out_ptr;
                    ptr+=2;
                    continue;
                }

                else if(ptr+2 < in_length && ((std::bitset<8>(in[ptr]))&(UTF8_3_HEAD)) == IS_UTF8_3_HEAD){
                    std::bitset<8> one(in[ptr]),two(in[ptr+1]),three(in[ptr+2]);
                    //one &= (~UTF8_3_HEAD);//4
                    //two &= (~UTF8_BODY);//6
                    //three &= (~UTF8_BODY);//6

                    
                    out[out_ptr] = static_cast<uint16_t>(std::bitset<16>(one.to_string().substr(4,4) + two.to_string().substr(2,6) + three.to_string().substr(2,6)).to_ulong());

                    ++out_ptr;
                    ptr+=3;
                    continue;
                }


                else if(ptr+3 < in_length && out_ptr+1 < out_length && ((std::bitset<8>(in[ptr]))&(UTF8_4_HEAD)) == IS_UTF8_4_HEAD){
                    char32_t buf[1];
                    const char *const p = &in[ptr];
                    utf8ToUtf32(p,4,buf,1);
                    buf[0] = buf[0] - 0x10000;
                    std::bitset<32> Bit(buf[0]);
                    std::bitset<10> high(Bit.to_string().substr(12,10));
                    std::bitset<10> low(Bit.to_string().substr(22,10));

                    char16_t out_buf[2];
                    out_buf[0] = static_cast<uint16_t>(high.to_ulong()+0xD800);
                    out_buf[1] = static_cast<uint16_t>(low.to_ulong()+0xDC00);

                    out[out_ptr] = out_buf[0];
                    out[out_ptr+1] = out_buf[1];

                    out_ptr+=2;
                    ptr+=4;
                    continue;
                }


                else return baseee::RUNTIME_ERROR;
            }
            return baseee::SUCCESS;
        }

        int utf16ToUtf8(const char16_t in[],const int in_length,char out[],const int out_length){
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

            const std::bitset<6> UTF16_HIGH("110110");
            const std::bitset<6> UTF16_LOW("110111");

            int ptr=0,out_ptr=0;

            while(ptr < in_length && out_ptr < out_length){
                std::bitset<16> buf(in[ptr]);

                if(out_ptr+3 < out_length && ptr+1 < in_length && (buf&std::bitset<16>("1111110000000000")) == std::bitset<16>(UTF16_HIGH.to_string()+"0000000000")){
                    std::bitset<16> low(in[ptr+1]);
                    std::bitset<8> o[4];

                    uint16_t H=buf.to_ulong(),L=low.to_ulong();
                    H = H - 0xD800;
                    L = L - 0xDC00;
                    std::bitset<20> F(std::bitset<10>(H).to_string()+std::bitset<10>(L).to_string());
                    uint32_t G = F.to_ulong() + 0x10000;

                    std::bitset<21> O(G);
                    o[0] = std::bitset<8>("11110"+O.to_string().substr(0,3)).to_ulong();
                    o[1] = std::bitset<8>("10"+O.to_string().substr(3,6)).to_ulong();
                    o[2] = std::bitset<8>("10"+O.to_string().substr(9,6)).to_ulong();
                    o[3] = std::bitset<8>("10"+O.to_string().substr(15,6)).to_ulong();
                    
                    out[out_ptr] = static_cast<uint8_t>(o[0].to_ulong());
                    out[out_ptr+1] = static_cast<uint8_t>(o[1].to_ulong());
                    out[out_ptr+2] = static_cast<uint8_t>(o[2].to_ulong());
                    out[out_ptr+3] = static_cast<uint8_t>(o[3].to_ulong());

                    ptr+=2;
                    out_ptr+=4;
                    continue;
                }

                else if(out_ptr+2 < out_length && buf.to_ulong() >= 0x000800 && buf.to_ulong() <= 0x00ffff){
                    std::bitset<8> o[3];
                    o[2] = std::bitset<8>("10"+buf.to_string().substr(10,6));
                    o[1] = std::bitset<8>("10"+buf.to_string().substr(4,6));
                    o[0] = std::bitset<8>("1110" + buf.to_string().substr(0,4));

                    out[out_ptr] = static_cast<uint8_t>(o[0].to_ulong());
                    out[out_ptr+1] = static_cast<uint8_t>(o[1].to_ulong());
                    out[out_ptr+2] = static_cast<uint8_t>(o[2].to_ulong());

                    ++ptr;
                    out_ptr+=3;
                    continue;
                }

                else if(out_ptr+1 < out_length && buf.to_ulong() >= 0x000080 && buf.to_ulong() <= 0x0007ff){
                    std::bitset<8> o[2];
                    o[1] = std::bitset<8>("10"+buf.to_string().substr(10,6));
                    o[0] = std::bitset<8>("110" + buf.to_string().substr(5,5));

                    out[out_ptr] = static_cast<uint8_t>(o[0].to_ulong());
                    out[out_ptr+1] = static_cast<uint8_t>(o[1].to_ulong());

                    ++ptr;
                    out_ptr+=2;
                    continue;
                }

                else if(buf.to_ulong() >= 0x000000 && buf.to_ulong() <= 0x00007f){
                    out[out_ptr] = static_cast<uint8_t>(std::bitset<8>("0"+buf.to_string().substr(9,7)).to_ulong());
                    ++ptr;
                    ++out_ptr;
                    continue;
                }

                else return baseee::RUNTIME_ERROR;
            }

        return baseee::SUCCESS;
        }

    }
}



#endif