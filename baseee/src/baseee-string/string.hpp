/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     string.hpp
 * Content:  baseee string module head file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once


#include <string>
#include <regex>
#include <bitset>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <memory>
#include <vector>

/*wstring爬*/

namespace baseee {
	namespace string {
		
		//trim:去除头尾空格,不包括\n\t等空白控制字符
		//返回string
		std::string trim(const std::string& s);
		std::string HeadTrim(const std::string& s);
		std::string EndTrim(const std::string& s);

		//split，根据正则表达式分割字符串，返回结果集
		//s字符串，r正则表达式
		std::vector<std::string> split(const std::string& s, const std::string& r);
		std::vector<std::string> split(const std::string& s, const std::regex& r);

		//ExpandsTabs 将tab转化为空格
		//默认一个tab为8空格
		std::string ExpandsTabs(const std::string& s, const int TabSizes);

		// *With判断字符串是否以end/start结尾/开头
		bool StartsWith(const std::string& s, const std::string &start);
		bool EndWith(const std::string& s, const std::string& end);

		//center 将字符串居中
		//SurplusSpaceLeft控制是否将多余的空格分配在左侧(begin)，否则分配在右侧(end)(默认true)
		std::string center(const std::string& s,const bool SurplusSpaceLeft);

		//大写转小写，小写转大写
		std::string SwapCase(const std::string& s);

		//格式化字符串
		//返回string的vsnprintf
		std::string format(const char * fmt, ...);
	}

	namespace coder {
		template<typename I, typename O>
		int Utf8ToUtf32(I b, I e, O ob, O oe) {
			const uint8_t UTF8_HEAD[4] = { 0b10000000, 0b11100000,0b11110000,0b11111000 };//utf8头的占用
			const uint8_t UTF8_HEAD_KEY[4] = { 0b00000000,0b11000000,0b11100000,0b11110000 };//utf8头
			const uint8_t UTF8_BODY = 0b11000000;
			//const uint8_t UTF8_BODY_KEY = 0b10000000;

			while (b != e && ob != oe) {
				if (((*b) & UTF8_HEAD[0]) == UTF8_HEAD_KEY[0]) {
					*ob = ((*b) & (~UTF8_HEAD[0]));
					++ob;
					++b;
					continue;
				}

				else if (((*b) & UTF8_HEAD[1]) == UTF8_HEAD_KEY[1] && (b + 1) != e) {
					uint8_t head = ((*b) & (~UTF8_HEAD[1]));
					uint8_t end = ((*(b + 1)) & (~UTF8_BODY));
					uint32_t out = (head << 6) + end;
					*ob = out;
					++ob;
					b += 2;
					continue;
				}

				else if (((*b) & UTF8_HEAD[2]) == UTF8_HEAD_KEY[2] && (b + 2) != e) {
					uint8_t head = ((*b) & (~UTF8_HEAD[2]));
					uint8_t heart = ((*(b + 1)) & (~UTF8_BODY));
					uint8_t end = ((*(b + 2)) & (~UTF8_BODY));
					uint32_t out = (head << 12) + (heart << 6) + end;
					*ob = out;
					++ob;
					b += 3;
					continue;
				}

				else if (((*b) & UTF8_HEAD[3]) == UTF8_HEAD_KEY[3] && (b + 3) != e) {
					uint8_t head = ((*b) & (~UTF8_HEAD[3]));
					uint8_t heart = ((*(b + 1)) & (~UTF8_BODY));
					uint8_t lung = ((*(b + 2)) & (~UTF8_BODY));
					uint8_t end = ((*(b + 3)) & (~UTF8_BODY));
					uint32_t out = (head << 18) + (heart << 12) + (lung << 6) + end;
					*ob = out;
					++ob;
					b += 4;
					continue;
				}

				else return -1;
			}

			return 0;
		}

		template<typename I, typename O>
		int Utf32ToUtf8(I b, I e, O ob, O oe) {
			const uint8_t UTF8_HEAD[4] = { 0b10000000, 0b11100000,0b11110000,0b11111000 };//utf8头的占用
			const uint8_t UTF8_HEAD_KEY[4] = { 0b00000000,0b11000000,0b11100000,0b11110000 };//utf8头
			const uint8_t UTF8_BODY = 0b11000000;
			const uint8_t UTF8_BODY_KEY = 0b10000000;

			while (b != e && ob != oe) {

				if (*b <= 0x7f) {
					*ob = UTF8_HEAD_KEY[0] + static_cast<uint8_t>(*b);
					++ob;
					++b;
					continue;
				}

				else if (*b <= 0x7ff && (ob + 1) != oe) {
					*(ob + 1) = UTF8_BODY_KEY + (static_cast<uint8_t>(*b) & (~UTF8_BODY));
					*ob = UTF8_HEAD_KEY[1] + (static_cast<uint8_t>((*b) >> 6) & (~UTF8_HEAD[1]));
					ob += 2;
					++b;
					continue;
				}

				else if (*b <= 0xffff && (ob + 2) != oe) {
					*(ob + 2) = UTF8_BODY_KEY + (static_cast<uint8_t>(*b) & (~UTF8_BODY));
					*(ob + 1) = UTF8_BODY_KEY + (static_cast<uint8_t>((*b) >> 6) & (~UTF8_BODY));
					*ob = UTF8_HEAD_KEY[2] + (static_cast<uint8_t>((*b) >> 12) & (~UTF8_HEAD[2]));
					ob += 3;
					++b;
					continue;
				}

				else if (*b <= 0x10ffff && (ob + 3) != oe) {
					*(ob + 3) = UTF8_BODY_KEY + (static_cast<uint8_t>(*b) & (~UTF8_BODY));
					*(ob + 2) = UTF8_BODY_KEY + (static_cast<uint8_t>((*b) >> 6) & (~UTF8_BODY));
					*(ob + 1) = UTF8_BODY_KEY + (static_cast<uint8_t>((*b) >> 12) & (~UTF8_BODY));
					*ob = UTF8_HEAD_KEY[3] + (static_cast<uint8_t>((*b) >> 18) & (~UTF8_HEAD[3]));
					ob += 4;
					++b;
					continue;
				}

				else return -1;
			}

			return 0;
		}

		
		template<typename I, typename O>
		int Utf8ToUtf16(I b, I e, O ob, O oe) {
			const uint8_t UTF8_HEAD[4] = { 0b10000000, 0b11100000,0b11110000,0b11111000 };//utf8头的占用
			const uint8_t UTF8_HEAD_KEY[4] = { 0b00000000,0b11000000,0b11100000,0b11110000 };//utf8头
			const uint8_t UTF8_BODY = 0b11000000;
			//const uint8_t UTF8_BODY_KEY = 0b10000000;

			while (b != e && ob != oe) {

				if (((*b) & UTF8_HEAD[0]) == UTF8_HEAD_KEY[0]) {
					*ob = (*b) & (~UTF8_HEAD[0]);
					++ob;
					++b;
					continue;
				}


				else if (((*b) & UTF8_HEAD[1]) == UTF8_HEAD_KEY[1] && (b + 1) != e) {
					uint8_t head = (*b) & (~UTF8_HEAD[1]);
					uint8_t end = (*(b + 1)) & (~UTF8_BODY);
					*ob = (static_cast<uint16_t>(head) << 6) + static_cast<uint16_t>(end);
					b += 2;
					++ob;
					continue;
				}

				else if (((*b) & UTF8_HEAD[2]) == UTF8_HEAD_KEY[2] && (b + 2) != e) {
					uint8_t head = (*b) & (~UTF8_HEAD[2]);
					uint8_t heart = (*(b + 1)) & (~UTF8_BODY);
					uint8_t end = (*(b + 2)) & (~UTF8_BODY);
					*ob = (static_cast<uint16_t>(head << 12))
						+ (static_cast<uint16_t>(heart << 6))
						+ static_cast<uint16_t>(end);
					b += 3;
					++ob;
					continue;
				}

				else if (((*b) & UTF8_HEAD[3]) == UTF8_HEAD_KEY[3] && (b + 3) != e) {
					uint8_t head = (*b) & (~UTF8_HEAD[3]);
					uint8_t heart = (*(b + 1)) & (~UTF8_BODY);
					uint8_t lung = (*(b + 2)) & (~UTF8_BODY);
					uint8_t end = (*(b + 3)) & (~UTF8_BODY);

					uint32_t all = (head << 18)
						+ (heart << 12)
						+ (lung << 6)
						+ (end);

					all = all - 0x10000;

					uint16_t first = static_cast<uint16_t>(
						std::bitset<10>(std::bitset<20>(all).to_string().substr(0, 10)).to_ulong());
					uint16_t second = static_cast<uint16_t>(
						std::bitset<10>(std::bitset<20>(all).to_string().substr(10, 10)).to_ulong());

					first = first + 0xD800;
					second = second + 0xDC00;

					*ob = first;
					*(ob + 1) = second;
					ob += 2;
					b += 4;
					continue;
				}

				else return -1;
			}

			return 0;
		}
		
		template<typename I, typename O>
		int Utf16ToUtf8(I b, I e, O ob, O oe) {
	    	const uint8_t UTF8_HEAD[4] = { 0b10000000, 0b11100000,0b11110000,0b11111000 };//utf8头的占用
			const uint8_t UTF8_HEAD_KEY[4] = { 0b00000000,0b11000000,0b11100000,0b11110000 };//utf8头
			const uint8_t UTF8_BODY = 0b11000000;
			const uint8_t UTF8_BODY_KEY = 0b10000000;

			const uint16_t UTF16_HEAD = 0b1101100000000000;
			//const uint16_t UTF16_END = 0b1101110000000000;
			const uint16_t UTF16_NEED = 0b1111110000000000;

			while (b != e && ob != oe) {
				if ((b + 1) != e
					&& ((*b) & UTF16_NEED) == UTF16_HEAD
					&& (ob + 3) != oe) {

					uint16_t first = (*b);
					uint16_t end = (*(b + 1));

					first = first - 0xD800;
					end = end - 0xDC00;

					std::bitset<10> First(std::bitset<16>(first).to_string().substr(6, 10));
					std::bitset<10> Second(std::bitset<16>(end).to_string().substr(6, 10));
					uint32_t all = (First.to_ulong() << 10) + (Second.to_ulong());

					all = all + 0x10000;

					array<char32_t, 1> Aims = { all };
					array<char, 4> Out = { 0,0,0,0 };
					//Utf32ToUtf8(&all, (&all) + 1, ob, (ob + 4));
					Utf32ToUtf8(Aims.cbegin(), Aims.cend(), Out.begin(), Out.end());
					*ob = Out[0];
					*(ob + 1) = Out[1];
					*(ob + 2) = Out[2];
					*(ob + 3) = Out[3];

					ob += 4;
					b += 2;
					continue;
				}

				else if ((*b) <= 0x007F) {
					/*uint32_t all = *b;

					std::array<uint32_t, 1> Aims = { all };
					std::array<uint8_t, 1> Out;
					Utf32ToUtf8(Aims.begin(), Aims.end(), Out.begin(), Out.end());*/

					*ob = static_cast<uint8_t>(*b);
					ob++;
					b++;
					continue;
				}

				else if ((*b) <= 0x07FF && (ob + 1) != oe) {
					uint32_t all = *b;

					std::array<uint32_t, 1> Aims = { all };
					std::array<uint8_t, 2> Out;
					Utf32ToUtf8(Aims.begin(), Aims.end(), Out.begin(), Out.end());

					*ob = Out[0];
					*(ob + 1) = Out[1];

					ob += 2;
					b++;
					continue;
				}

				else if ((*b) <= 0xFFFF && (ob + 2) != oe) {
					uint32_t all = *b;

					std::array<uint32_t, 1> Aims = { all };
					std::array<uint8_t, 3> Out;
					Utf32ToUtf8(Aims.begin(), Aims.end(), Out.begin(), Out.end());

					*ob = Out[0];
					*(ob + 1) = Out[1];
					*(ob + 2) = Out[2];

					ob += 3;
					b++;
					continue;
				}
				
				else return -1;
			}


			return 0;
		}


		template<typename O>
		O GetBom(const std::string& code, const std::string& mark) {
			switch (code)
			{
			case "utf-16":
			case "UTF-16":
			case "UTF16":
			case "utf16":
			case "utf_16":
			case "UTF_16":
				switch (mark)
				{
				case "LE":
				case "le":
					std::shared_ptr<char16_t> out(new char16_t[2]);
					out.operator[0] = 0xFF;
					out.operator[1] = 0xFE;
					return out;
					break;

				case "BE":
				case 'be':
					std::shared_ptr<char16_t> out(new char16_t[2]);
					out.operator[0] = 0xFE;
					out.operator[1] = 0xFF;
					return out;
					break;
				default:
					break;
				}
				break;

			case "utf-32":
			case "UTF-32":
			case "utf32":
			case "UTF32":
			case "utf_32":
			case "UTF_32":
				switch (mark)
				{
				case "LE":
				case "le":
					std::shared_ptr<char16_t> out(new char32_t[2]);
					out.operator[0] = 0xFFFE;
					out.operator[1] = 0x0000;
					return out;
					break;

				case "BE":
				case 'be':
					std::shared_ptr<char16_t> out(new char32_t[2]);
					out.operator[0] = 0x0000;
					out.operator[1] = 0xFEFF;
					return out;
					break;

				default:
					break;
				}
				break;


			default:
				break;
			}
			return nullptr;
		}

		template<typename O>
		O GetBom(const std::string& code) {
			switch (code)
			{
			case "utf-8":
			case "UTF-8":
			case "utf8":
			case "UTF8":
			case "utf_8":
			case "UTF_8":
				std::shared_ptr<char> out(new char[3]);
				out.operator[0] = 0xEF;
				out.operator[1] = 0xBB;
				out.operator[2] = 0xBF;
				return out;
			default:
				break;
			}
			return nullptr;
		}
	}

}