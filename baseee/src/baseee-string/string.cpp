/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    string.cpp
 * Content: string Source File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <regex>
#include <vector>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <memory>
#include "string.hpp"

namespace baseee {
	namespace string {
		
		std::vector<std::string> Split(const std::string& s, const std::regex& r) {
			std::vector<std::string> out(std::sregex_token_iterator(s.begin(), s.end(), r, -1), std::sregex_token_iterator());
			return out;
		}

		std::vector<std::string> Split(const std::string& s, const std::string& r) {
			std::regex re(r);
			return baseee::string::Split(s, re);
		}

		std::string ExpandsTabs(const std::string& s, const int TabSizes = 8) noexcept {
			std::string out(s);
			while (out.find('\t') != out.npos) {
				out.replace(out.find('\t'), 1, std::string(TabSizes, ' '));
			}
			return out;
		}

		bool StartsWith(const std::string& s, const std::string& start) noexcept {
			return s.find(start) == 0 ? true : false;
		}
		bool EndWith(const std::string& s, const std::string& end) noexcept {
			return s.find(end) == (s.size() - end.size()) ? true : false;
		}

		std::string Center(const std::string& s, const bool SurplusSpaceLeft = true) noexcept {
			std::string out = Trim<std::string, char>(s);
			if (out.size() == s.size()) return out;
			auto length = (s.size() - out.size()) / 2;
			while (length != 0) {
				out = ' ' + out + ' ';
				length--;
			}
			if ((s.size() - out.size()) % 2 != 0)
				SurplusSpaceLeft ? out.insert(out.begin(), ' ') : out.insert(out.end(), ' ');
			return out;
		}


		std::string SwapCase(const std::string& s) noexcept {
			std::string out(s);
			for (char& c : out) {
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

	}
	

}