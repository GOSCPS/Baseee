
#include <bitset>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <memory>
#include "string.hpp"


namespace baseee {
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
					*ob = (*b) & (~UTF8_HEAD[0]));
					++ob;
					++b;
					continue;
				}


				else if (((*b) & UTF8_HEAD[1]) == UTF8_HEAD_KEY[1] && (b + 1) != e) {
					uint8_t head = (*b) & (~UTF8_HEAD[1]));
					uint8_t end = (*(b + 1)) & (~UTF8_BODY));
					*ob = (static_cast<uint16_t>(head) << 6) + static_cast<uint16_t>(end);
					b += 2;
					++ob;
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


