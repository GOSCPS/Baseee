#pragma once
// string.cpp字符串处理源文件
//MIT License
//Copyright(c) 2020 chhdao
//

#include <string>
#include <regex>
#include <vector>
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
			int length = (s.size() - out.size()) / 2;
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

	}
}