/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     unit-test.cpp
 * Content:  baseee unit test
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include "string.hpp"
#include "log.hpp"
#include <utility>
#include <thread>
#include <array>
#include <bitset>
#include <ctime>
#include <cstdio>

using namespace std;
using namespace baseee;

array<char, 57> TESTLISTU8 = { u8"你好-Hello-$-€-𐐷-𤭢-🏳️‍🌈-Greater Test" };
array<char16_t, 39> TESTLISTU16 = { u"你好-Hello-$-€-𐐷-𤭢-🏳️‍🌈-Greater Test" };
array<char32_t, 35> TESTLISTU32 = { U"你好-Hello-$-€-𐐷-𤭢-🏳️‍🌈-Greater Test" };
const auto U8Size = TESTLISTU8.size();
const auto U16Size = TESTLISTU16.size();
const auto U32Size = TESTLISTU32.size();

void StringCoderTest1();
void StringCoderTest2();
void LogTest();

int main(int argc,char *argv[])
{
	StringCoderTest1();
	StringCoderTest2();
	LogTest();
	return 0;
}

void StringCoderTest1() {
	{
		cout << "Test:Utf8 To Utf32" << endl;

		array<char32_t, U32Size> buf = {};
		cout << coder::Utf8ToUtf32(TESTLISTU8.cbegin(), TESTLISTU8.cend(), buf.begin(), buf.end()) << endl;

		for (int a = 0; a < buf.size(); a++) {
			if (buf[a] != TESTLISTU32[a]) {
				cout << "Error At " << a << endl;
			}
		}

		cout << "Right!" << endl;
	}

	{
		cout << "Test:Utf32 To Utf8" << endl;

		array<char, U8Size> buf = {};
		cout << coder::Utf32ToUtf8(TESTLISTU32.cbegin(), TESTLISTU32.cend(), buf.begin(), buf.end()) << endl;

		for (int a = 0; a < buf.size(); a++) {
			if (buf[a] != TESTLISTU8[a]) {
				cout << "Error At " << a << endl;
			}
		}

		cout << "Right!" << endl;
	}
}

void StringCoderTest2() {
	{
		cout << "Test:Utf8 To Utf16" << endl;

		array<char16_t, U16Size> buf = {};
		cout << coder::Utf8ToUtf16(TESTLISTU8.cbegin(), TESTLISTU8.cend(), buf.begin(), buf.end()) << endl;

		for (int a = 0; a < buf.size(); a++) {
			if (buf[a] != TESTLISTU16[a]) {
				cout << "Error At " << a << endl;
			}
		}

		cout << "Right!" << endl;
	}

	{
		cout << "Test:Utf16 To Utf8" << endl;

		array<char, U8Size> buf = {};
		cout << coder::Utf16ToUtf8(TESTLISTU16.cbegin(), TESTLISTU16.cend(), buf.begin(), buf.end()) << endl;

		for (int a = 0; a < buf.size(); a++) {
			if (buf[a] != TESTLISTU8[a]) {
				cout << "Error At " << a << endl;
			}
		}

		cout << "Right!" << endl;
	}
}


void LogTest() {
	baseee::log::logger logger("{year}-{month}-{day} at {hour}:{min}:{sec} {level}:","",std::cout);
	logger.SetLowestLevelOutConsole(baseee::log::LogLevel::Level_Debug);

	logger.SetDefaultOutLevel(baseee::log::LogLevel::Level_Debug);
	logger.PrintLog("Test:Log Print!");
	logger << "Hello World";

	logger.PrintLog(baseee::log::LogLevel::Level_Fatal, "Right!");
}