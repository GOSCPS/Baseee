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
#include "inip.hpp"
#include "jsonp.hpp"
#include "test.hpp"
#include <utility>
#include <thread>
#include <array>
#include <optional>
#include <bitset>
#include <ctime>
#include <cstdio>
#include <regex>

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
void IniParserTest();
void StringMakeTest();
void JsonParserTest();

int main(int argc,char *argv[])
{
	//StringCoderTest1();
	//StringCoderTest2();
	//LogTest();
	//IniParserTest();
	//StringMakeTest();
	JsonParserTest();
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

	logger._PrintLog(baseee::log::LogLevel::Level_Fatal, "Right!");
}


void IniParserTest() {
	std::string IniText("[display]\n\nWide=8\n\nHigh=12");


	baseee::parser::IniParser Parser;
	cout << Parser.Parser(IniText) << endl;

	if (Parser.GetInt("display", "Wide").has_value()) {
		cout << "Int:" << Parser.GetInt("display", "Wide").value() << endl;
	}
	if (Parser.GetInt("display", "High").has_value()) {
		cout << "Int:" << Parser.GetInt("display", "High").value() << endl;
	}

	return;
}

void StringMakeTest() {

	std::string t("  \tHello World  \n ");
	cout << ">" << baseee::string::Trim<std::string,char>(t) << "<" << endl;
	cout << ">" << baseee::string::EndTrim<char>(t) << "<" << endl;
	cout << ">" << baseee::string::HeadTrim<char>(t) << "<" << endl;

	return;
}

void JsonParserTest() {
	baseee::parser::JsonDataBuilder JsonParser
		(baseee::parser::CreateNewJsonTree());

	JsonParser["Test Int"] = 0;
	JsonParser["Test String"] = "Hello Json";
	JsonParser["Test Json Objects"]["Second"] = "Hello Baseee";
	JsonParser["Boolean True"].SetBoolean(true);
	JsonParser["Boolean False"].SetBoolean(false);

	baseee::parser::JsonStringBuilder JsonBuilder;
	JsonBuilder.SetBeautiful(true);
	

	cout << JsonBuilder.Build(*JsonParser.GetJsonTree()) << endl;
	cout << JsonParser["Boolean False"].GetBoolean().value() << endl;
	cout << JsonParser["Boolean True"].GetBoolean().value() << endl;
	cout << JsonParser["Test Int"].GetNumber().value() << endl;
	cout << JsonParser["Test String"].GetString().value() << endl;
	cout << JsonParser["Test Json Objects"]["Second"].GetString().value() << endl;

	return;
}