/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    test.hpp
 * Content: test Source File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <iostream>


namespace baseee {
	namespace test {
		static int64_t TestPassCount = 0;
		static int64_t TestCount = 0;
	}
}

#define BASEEE_TEST_EQUAL_BASE(expression,expect) { \
baseee::test::TestCount++;\
auto BASEEE_TEST_EXPRESSION_KEY = (expression);\
if(BASEEE_TEST_EXPRESSION_KEY == expect){\
baseee::test::TestPassCount++;\
}\
else {\
std::cerr << "\033[31mTest Fall Down At:" << baseee::test::TestCount \
<< " \"" << __FILE__ << ":"<< __LINE__ << "\n" <<  std::endl;\
std::cerr << "Expect is:" << expect \
<< "\nBut expression of key is:" << BASEEE_TEST_EXPRESSION_KEY \
<< "\033[0m" << std::endl;\
}\
}

#if defined(DEBUG) || !defined(NDEBUG)
#define BASEEE_assert(expression) if(!(expression)) \
std::cerr << "\033[31massert fall down at file:" << __FILE__\
<< " line:" << __LINE__ << "\033[0m" << std::endl;
#define BASEEE_assert_not(expression) BASEEE_assert((!(expression)));
#else
#define BASEEE_assert(expression) (expression);
#define BASEEE_assert(expression) (expression);
#endif