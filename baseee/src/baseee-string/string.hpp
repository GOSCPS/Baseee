#pragma once
// string.hpp字符串处理声明
//MIT License
//Copyright(c) 2020 chhdao
//
#include "string.cpp"
#include <string>
#include <regex>
#include <vector>

namespace baseee {
	namespace string {
		//wstring爬
		//trim:去除头尾空格
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
		//Unicode编码转换
		//输入迭代器
		//成功返回0
		template<typename I,typename O>
		int Utf8ToUtf32(I, I, O, O);
		template<typename I, typename O>
		int Utf32ToUtf8(I, I, O, O);
	}

}
