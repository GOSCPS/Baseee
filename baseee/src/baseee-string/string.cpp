#pragma once
// string.cpp字符串处理源文件
//MIT License
//Copyright(c) 2020 chhdao
//

#include <string>
#include <regex>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "string.hpp"

namespace baseee {
	namespace string {
		std::string trim(const std::string& s) {
			std::string out(s);
			if (out.empty()) return "";
			out.erase(0, out.find_first_not_of(" "));
			out.erase(out.find_last_not_of(" ") + 1);
			return out;
		}

		std::string HeadTrim(const std::string& s) {
			std::string out(s);
			if (out.empty()) return "";
			out.erase(0, out.find_first_not_of(" "));
			return out;
		}

		std::string EndTrim(const std::string& s) {
			std::string out(s);
			if (out.empty()) return "";
			out.erase(out.find_last_not_of(" ") + 1);
			return out;
		}


		std::vector<std::string> split(const std::string& s, const std::regex& r) {
			std::vector<std::string> out(std::sregex_token_iterator(s.begin(), s.end(), r, -1), std::sregex_token_iterator());
			return out;
		}


		std::vector<std::string> split(const std::string& s, const std::string& r) {
			std::regex re(r);
			return baseee::string::split(s, re);
		}

		std::string ExpandsTabs(const std::string& s, const int TabSizes = 8) {
			std::string out(s);
			while (out.find('\t') != out.npos) {
				out.replace(out.find('\t'), 1, std::string(TabSizes,' '));
			}
			return out;
		}

		bool StartsWith(const std::string& s, const std::string& start) {
			return s.find(start) == 0 ? true : false;
		}
		bool EndWith(const std::string& s, const std::string& end) {
			return s.find(end) == (s.size()-end.size()) ? true : false;
		}

		std::string center(const std::string& s, const bool SurplusSpaceLeft = true) {
			std::string out = trim(s);
			if (out.size() == s.size()) return out;
			auto length = (s.size() - out.size()) / 2;
			while (length != 0) {
				out = ' ' + out + ' ';
				length--;
			}
			if ((s.size() - out.size()) % 2 != 0) 
				SurplusSpaceLeft ?  out.insert(out.begin(), ' ') : out.insert(out.end(), ' ');
			return out;
		}
		

		std::string SwapCase(const std::string& s) {
			std::string out(s);
			for (char &c : out) {
				if (std::islower(c)) {
					c = std::toupper(c);
					continue;
				}
				else if (std::isupper(c)) {
					c = std::tolower(c);
					continue;
				}
				else continue;
			}
			return out;
		}


		std::string format(const char* fmt, ...) {
			int len = 0;
			std::string str;
			va_list args;
			char* buffer = new char[4096]{};
			int bufferLength = 4096;

			va_start(args, fmt);

			if ((len = std::vsnprintf(buffer, bufferLength, fmt, args)) < 0) {
				while (len < 0) {
					delete[] buffer;
					bufferLength *= 2;
					buffer = new char[bufferLength];
					len = std::vsnprintf(buffer, bufferLength, fmt, args);
				}
			}
		str=std::string(buffer);
		delete[] buffer;
		va_end(args);
		return str;
		}

	}
	namespace coder {
		template<typename I, typename O>
		int Utf8ToUtf32(I b,I e,O ob, O oe) {
			const uint8_t UTF8_HEAD[4] = { 0b10000000, 0b11100000,0b11110000,0b11111000 };//utf8头的占用
			const uint8_t UTF8_HEAD_KEY[4] = { 0b00000000,0b11000000,0b11100000,0b11110000 };//utf8头
			const uint8_t UTF8_BODY = 0b11000000;
			const uint8_t UTF8_BODY_KEY = 0b10000000;

			while (b != e && ob != oe) {
				if (((*b) & UTF8_HEAD[0]) == UTF8_HEAD_KEY[0]) {
					*ob = ((*b) & (~UTF8_HEAD[0]));
					++ob;
					++b;
					continue;
				}

				else if(((*b) & UTF8_HEAD[1]) == UTF8_HEAD_KEY[1] && (b+1) != e) {
					uint8_t head = ((*b) & (~UTF8_HEAD[1]));
					uint8_t end = ((*(b+1)) & (~UTF8_BODY));
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
	}

}