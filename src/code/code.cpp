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
#include <memory>
#include <utility>

namespace baseee{
    namespace code{


        inline uint32_t LoopLeftShift(uint32_t i,uint32_t left){
            std::bitset<32> in(i);
            std::bitset<32> l(in.to_string().substr(0,left));
            std::bitset<32> r(in.to_string().substr(left));
            std::bitset<32> out(r.to_ulong() + l.to_ulong());
            i = out.to_ulong();
            return i;
        }

        inline uint32_t F(uint32_t X,uint32_t Y,uint32_t Z) {
            return (X&Y)|((~X)&Z);
        }
        inline uint32_t G(uint32_t X,uint32_t Y,uint32_t Z) {
            return (X&Z)|(Y&(~Z));
        }
        inline uint32_t H(uint32_t X,uint32_t Y,uint32_t Z) {
            return X^Y^Z;
        }
        inline uint32_t I(uint32_t X,uint32_t Y,uint32_t Z) {
            return Y^(X|(~Z));
        }

        inline uint32_t FF(uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t Mj,uint32_t s,uint32_t ti){
            a = b + ( LoopLeftShift((a + F(b,c,d) + Mj + ti),s));
            return a;
        }
        inline uint32_t GG(uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t Mj,uint32_t s,uint32_t ti){
            a = b + ( LoopLeftShift((a + G(b,c,d) + Mj + ti),s));
            return a;
        }
        inline uint32_t HH(uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t Mj,uint32_t s,uint32_t ti){
            a = b + ( LoopLeftShift((a + H(b,c,d) + Mj + ti),s));
            return a;
        }
        inline uint32_t II(uint32_t a,uint32_t b,uint32_t c,uint32_t d,uint32_t Mj,uint32_t s,uint32_t ti){
            a = b + ( LoopLeftShift((a + I(b,c,d) + Mj + ti),s));
            return a;
        }




        std::pair<uint8_t *,uint64_t> md5Fill(const char in[],const int in_length){
            uint64_t length = in_length*8;
            while(length%512 != 448) ++length;
            length += 64;

            //分配内存
            uint64_t word = length/8;//按字节计算
            uint8_t *ptr = new uint8_t[word];

            //填充元数据
            for(int a=0;a < in_length;a++) ptr[a] = in[a];

            //填充1及N0
            ptr[in_length] = static_cast<uint8_t>(std::bitset<8>("10000000").to_ulong());
            for(int a=in_length+1;a < (word-8);a++) ptr[a] = 0;

            //填充元数据长度
            uint64_t in_long = in_length*8;
            ptr[word-1] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-2] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-3] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-4] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-5] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-6] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-7] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;
            ptr[word-8] = static_cast<uint8_t>(in_long);
            in_long = in_long >> 8;

            return {ptr,word};
        }


        uint32_t * md5Calculation(uint32_t *ptr,uint32_t A,uint32_t B,uint32_t C,uint32_t D){
            /*uint32_t A = 0x67452301;
            uint32_t B = 0xEFCDAB89;
            uint32_t C = 0x98BADCFE;
            uint32_t D = 0x10325476;*/
            uint32_t a = A;
            uint32_t b = B;
            uint32_t c = C;
            uint32_t d = D;

            uint32_t &M0 = ptr[0];
            uint32_t &M1 = ptr[1];
            uint32_t &M2 = ptr[2];
            uint32_t &M3 = ptr[2];
            uint32_t &M4 = ptr[4];
            uint32_t &M5 = ptr[5];
            uint32_t &M6 = ptr[6];
            uint32_t &M7 = ptr[7];
            uint32_t &M8 = ptr[8];
            uint32_t &M9 = ptr[9];
            uint32_t &M10 = ptr[10];
            uint32_t &M11 = ptr[11];
            uint32_t &M12 = ptr[12];
            uint32_t &M13 = ptr[13];
            uint32_t &M14 = ptr[14];
            uint32_t &M15 = ptr[15];

             //第一轮
            a=FF(a,b,c,d,M0,7,0xd76aa478);
            b=FF(d,a,b,c,M1,12,0xe8c7b756);
            c=FF(c,d,a,b,M2,17,0x242070db);
            d=FF(b,c,d,a,M3,22,0xc1bdceee);
            a=FF(a,b,c,d,M4,7,0xf57c0faf);
            b=FF(d,a,b,c,M5,12,0x4787c62a);
            c=FF(c,d,a,b,M6,17,0xa8304613);
            d=FF(b,c,d,a,M7,22,0xfd469501);
            a=FF(a,b,c,d,M8,7,0x698098d8);
            b=FF(d,a,b,c,M9,12,0x8b44f7af);
            c=FF(c,d,a,b,M10,17,0xffff5bb1);
            d=FF(b,c,d,a,M11,22,0x895cd7be);
            a=FF(a,b,c,d,M12,7,0x6b901122);
            b=FF(d,a,b,c,M13,12,0xfd987193);
            c=FF(c,d,a,b,M14,17,0xa679438e);
            d=FF(b,c,d,a,M15,22,0x49b40821);

            //第二轮
            a=GG(a,b,c,d,M1,5,0xf61e2562);
            b=GG(d,a,b,c,M6,9,0xc040b340);
            c=GG(c,d,a,b,M11,14,0x265e5a51);
            d=GG(b,c,d,a,M0,20,0xe9b6c7aa);
            a=GG(a,b,c,d,M5,5,0xd62f105d);
            b=GG(d,a,b,c,M10,9,0x02441453);
            c=GG(c,d,a,b,M15,14,0xd8a1e681);
            d=GG(b,c,d,a,M4,20,0xe7d3fbc8);
            a=GG(a,b,c,d,M9,5,0x21e1cde6);
            b=GG(d,a,b,c,M14,9,0xc33707d6);
            c=GG(c,d,a,b,M3,14,0xf4d50d87);
            d=GG(b,c,d,a,M8,20,0x455a14ed);
            a=GG(a,b,c,d,M13,5,0xa9e3e905);
            b=GG(d,a,b,c,M2,9,0xfcefa3f8);
            c=GG(c,d,a,b,M7,14,0x676f02d9);
            d=GG(b,c,d,a,M12,20,0x8d2a4c8a);

            //第三轮
            a=HH(a,b,c,d,M5,4,0xfffa3942);
            b=HH(d,a,b,c,M8,11,0x8771f681);
            c=HH(c,d,a,b,M11,16,0x6d9d6122);
            d=HH(b,c,d,a,M14,23,0xfde5380c);
            a=HH(a,b,c,d,M1,4,0xa4beea44);
            b=HH(d,a,b,c,M4,11,0x4bdecfa9);
            c=HH(c,d,a,b,M7,16,0xf6bb4b60);
            d=HH(b,c,d,a,M10,23,0xbebfbc70);
            a=HH(a,b,c,d,M13,4,0x289b7ec6);
            b=HH(d,a,b,c,M0,11,0xeaa127fa);
            c=HH(c,d,a,b,M3,16,0xd4ef3085);
            d=HH(b,c,d,a,M6,23,0x04881d05);
            a=HH(a,b,c,d,M9,4,0xd9d4d039);
            b=HH(d,a,b,c,M12,11,0xe6db99e5);
            c=HH(c,d,a,b,M15,16,0x1fa27cf8);
            d=HH(b,c,d,a,M2,23,0xc4ac5665);

            //第四轮
            a=II(a,b,c,d,M0,6,0xf4292244);
            b=II(d,a,b,c,M7,10,0x432aff97);
            c=II(c,d,a,b,M14,15,0xab9423a7);
            d=II(b,c,d,a,M5,21,0xfc93a039);
            a=II(a,b,c,d,M12,6,0x655b59c3);
            b=II(d,a,b,c,M3,10,0x8f0ccc92);
            c=II(c,d,a,b,M10,15,0xffeff47d);
            d=II(b,c,d,a,M1,21,0x85845dd1);
            a=II(a,b,c,d,M8,6,0x6fa87e4f);
            b=II(d,a,b,c,M15,10,0xfe2ce6e0);
            c=II(c,d,a,b,M6,15,0xa3014314);
            d=II(b,c,d,a,M13,21,0x4e0811a1);
            a=II(a,b,c,d,M4,6,0xf7537e82);
            b=II(d,a,b,c,M11,10,0xbd3af235);
            c=II(c,d,a,b,M2,15,0x2ad7d2bb);
            d=II(b,c,d,a,M9,21,0xeb86d391);

            a = a + A;b = b + B;
            c = c + C;d = d + D;

            uint32_t * out = new uint32_t[4];
            out[0] = a;
            out[1] = b;
            out[2] = c;
            out[3] = d;
            return out;
        }

        uint32_t * buildMd5Group(uint8_t * in){
            uint32_t * ptr = new uint32_t[16];
            for(int a=0,s=0;a<16;++a,s+=4){
                    std::bitset<8> buf[4];
                    buf[0] = in[s];
                    buf[1] = in[s+1];
                    buf[2] = in[s+2];
                    buf[3] = in[s+3];
                    ptr[a] = std::bitset<32>(buf[0].to_string() + buf[1].to_string() + buf[2].to_string() + buf[3].to_string()).to_ulong();
            }
        return ptr;
        }


        uint32_t *md5(const char in[],const int in_length){
            auto re = md5Fill(in,in_length);
            uint8_t * ptr = re.first;
            uint64_t length = re.second;

            //---填充完毕---
            //512bit 分为 16组 
            //每组 32bit 4Byte
            std::vector<uint32_t*> group;
            
            int p=0;
            while(p < length){
            group.push_back(buildMd5Group(&ptr[p]));
            p += 64;
            }

            //处理
            uint32_t *key = new uint32_t[4]{0x67452301,0xEFCDAB89,0x98BADCFE,0x10325476};

            for(auto &s:group){
                key = md5Calculation(s,key[0],key[1],key[2],key[3]);
            }

            //free ram
            for(auto &s:group){
                delete []s;
            }
            delete []ptr;
            return key;
        }
    }
}


#endif