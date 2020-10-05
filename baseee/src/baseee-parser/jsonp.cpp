/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     jsonp.cpp
 * Content:  json parser file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <regex>
#include <array>
#include <optional>
#include <variant>
#include <map>
#include "jsonp.hpp"
#include "../baseee-test/test.hpp"
#include "../baseee-string/string.hpp"

//�ж��ַ��Ƿ���a-b��Χ��
//b >= a
inline bool baseee::parser::JsonParser::MatchCharRange(char a, char b) {
	if ((*Next) >= a && (*Next) <= b) return true;
	else return false;
}

baseee::parser::JsonErrCode 
baseee::parser::JsonParser::Parser(std::string_view JsonStr) {
	if (std::string(JsonStr).empty()) return JsonErrCode::Parse_OK;

	this->Json = std::string(JsonStr);
	this->Next = Json.cbegin();

	this->AfterSpace();
	auto Result = this->ParseVulan();

	if (Result == JsonErrCode::Parse_OK) {
		AfterSpace();
		if (Next != Json.cend()) return JsonErrCode::Parse_VulanError;
	}
	JsonPool.push_back(JsonNext);
	return Result;
}

//�����ո�
void baseee::parser::JsonParser::AfterSpace() {
	if (Next == Json.cend()) return;
	while (std::isspace(*Next)) Next++;
	return;
}

//����ֵ
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulan() {
	switch (*Next) {
	case 'n': return ParseVulanNull();//'n'ull
	case '\0': return JsonErrCode::Parse_MissVulan;

	case 'f': //'f'alse
	case 't'://'t'rue
		return ParseVulanBool();

	case '\"': return ParseVulanString();//'"' String"
	case '[': return ParseVulanArray();//'['xxx,xxx]
	case '{': return ParseVulanObject();//'{' "xxx":xxx}
	default: return ParseVulanNumber();//(-?)|([0-9]?)Number
	}
}

//����null
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanNull() {

	BASEEE_assert(*Next == 'n')

	if (!IteratorMatch("null")) {
		return JsonErrCode::Parse_VulanError;
	}
	Next += 4;

	JsonNext.JsonType = JsonType::JsonType_Null;
	JsonNext.Data = 0.0;
	return JsonErrCode::Parse_OK;
}

//����true
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanTrue() {

	BASEEE_assert(*Next == 't');

	if (!IteratorMatch("true")) {
		return JsonErrCode::Parse_VulanError;
	}
	Next += 4;

	JsonNext.JsonType = JsonType::JsonType_True;
	JsonNext.Data = 0.0;
	return JsonErrCode::Parse_OK;
}

//����false
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanFalse() {

	BASEEE_assert(*Next == 'f');

	if (!IteratorMatch("false")) {
		return JsonErrCode::Parse_VulanError;
	}
	Next += 5;

	JsonNext.JsonType = JsonType::JsonType_False;
	JsonNext.Data = 0.0;
	return JsonErrCode::Parse_OK;
}

//����Bool
baseee::parser::JsonErrCode
baseee::parser::JsonParser::ParseVulanBool() {

	if ((*Next) == 't') {
		return this->ParseVulanTrue();
	}
	else if ((*Next) == 'f') {
		return this->ParseVulanFalse();
	}
	else return JsonErrCode::Parse_VulanError;
}

//�ַ�ƥ��
bool baseee::parser::JsonParser::IteratorMatch(std::string_view str) {
	std::string sstr(str);

	if (sstr[sstr.size() - 1] == '\0') sstr.erase(sstr[sstr.size() - 1]);

	for (int a = 0; a < sstr.size(); a++) {
		if ((Next + a) == Json.cend()) return false;
		else if ((*(Next+a)) != sstr[a]) return false;
		else continue;
	}
	return true;
}


//��������
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanNumber() {

	std::string Int("([-]?[1-9]?[0-9]+)|([-]?[0]{1})");
	std::string Frac("\\.[0-9]+");
	std::string Exp("[eE]{1}[+-]?[0-9]+");
	std::string Number("(" + Int + "){1}(" + Frac + ")?(" + Exp + ")?");

	std::regex NumberRegex(Number);

	char c[] = { *Next,'\0' };
	std::string NumberBuf(c);

	//ѭ����ȡ����
	//����Ϊ '0'~'9' '-' 'e' 'E' '.'�е�����һ��
	while (Next != Json.cend() &&
		(MatchCharRange('0', '9') 
			|| (*Next) == '-'
			|| (*Next) == 'e' 
			|| (*Next) == 'E'
			|| (*Next) == '.')) {
		c[0] = { *Next };
		NumberBuf.append(std::string(c));
		Next++;
	}

	if (!std::regex_match(NumberBuf, NumberRegex)) {
		return JsonErrCode::Parse_VulanError;
	}

	this->JsonNext.JsonType = JsonType::JsonType_Number;
	this->JsonNext.Data = std::stod(NumberBuf);

	return JsonErrCode::Parse_OK;
}

baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanString() {
	BASEEE_assert(*Next == '\"');
	std::string String = "";
	Next++;

	std::optional<std::string> opt;

	char c[] = { *Next,'\0' };
	
	while (true) {

		if (Next == Json.cend()) return JsonErrCode::Parse_MissToken;
		else if ((*Next) == '\"') {
			Next++;
			break;
		}
		else if ((*Next) == '\\') {
			if ((Next++) == Json.cend()) return JsonErrCode::Parse_MissToken;
			else switch (*Next) {
			case 'n':
				String.append("\n");
				break;
			case '\"':
				String.append("\"");
				break;
			case '\\':
				String.append("\\");
				break;
			case 'b':
				String.append("\b");
				break;
			case 'f':
				String.append("\f");
				break;
			case 'r':
				String.append("\r");
				break;
			case 't':
				String.append("\t");
				break;
			case 'u':
				opt = ParseVulanUnicode();
				if(opt == std::nullopt || !opt.has_value()) return JsonErrCode::Parse_VulanError;
				String.append(opt.value());
				break;
			default:
				return JsonErrCode::Parse_VulanError;
			}
		}
		else {
			c[0] = *Next;
			String.append(c);
		}

		Next++;
	}

	this->JsonNext.JsonType = JsonType::JsonType_String;
	this->JsonNext.Data = String;

	return JsonErrCode::Parse_OK;
}

//����\\uXXXX
//�Լ�\\uXXXX\\uYYYY(����)
std::optional<std::string> 
baseee::parser::JsonParser::ParseVulanUnicode() {
	BASEEE_assert(*Next == 'u');
	Next++;//����\\u�е�u

	uint32_t Out;

	std::string StrBuf = "0x";//����16����������Ҫ0x
	char c[] = { '\0','\0' };

	//��ȡ����
	for (int a = 0; a < 4; a++) {
		if (Next == Json.cend()) {
			return std::nullopt;
		}
		c[0] = *Next;
		StrBuf.append(c);
		Next++;
	}

	uint32_t U8 = std::stoul(StrBuf);

	//Ϊ��λ����
	//������ȡ��λ����
	if (U8 >= 0xD800 && U8 <= 0xDBFF) {
		if (!IteratorMatch("\\u")) return std::nullopt;
		Next += 2;

		StrBuf = "0x";
		for (int a = 0; a < 4; a++) {
			if (Next == Json.cend()) {
				return std::nullopt;
			}
			c[0] = *Next;
			StrBuf.append(c);
			Next++;
		}

		char32_t U8Low = std::stoul(StrBuf);
		if (!(U8Low >= 0xDC00 && U8Low <= 0xDFFF))
			return std::nullopt;
		//�����ԭ���
		Out = 0x10000 + (U8 - 0xD800) * 0x400 + (U8Low - 0xDC00);
	}
	else {
		Out = U8;
	}

	std::array<char32_t, 1> OutArrayU32 = { Out };
	std::array<char, 4> OutArrayU8;
	baseee::coder::Utf32ToUtf8(
		OutArrayU32.cbegin(), OutArrayU32.cend(),
		OutArrayU8.begin(), OutArrayU8.end());

	return std::string(OutArrayU8.data());
}

//��������
baseee::parser::JsonErrCode 
baseee::parser::JsonParser::ParseVulanArray() {
	BASEEE_assert(*Next == '[');
	Next++;
	bool skip = true;

	JsonData JsonArray;
	JsonArray.JsonType = JsonType::JsonType_Array;
	JsonArray.Data = std::vector<JsonData>();

	auto ErrCode = JsonErrCode::Parse_OK;

	while (true) {
		if (Next == Json.cend()) return JsonErrCode::Parse_MissToken;
		else if (*Next == ']') { Next++; break; }
		else if (*Next == ',') Next++;
		// �ڣ�[xx,xx]�У���Ҫ�Ȳ���x���зָ�(, || ])�ж�
		else if (skip) skip = false;
		else return JsonErrCode::Parse_MissToken;

		AfterSpace();
		ErrCode = ParseVulan();
		if (ErrCode != JsonErrCode::Parse_OK)return ErrCode;

		std::get<std::vector<JsonData>>(JsonArray.Data)
			.push_back(JsonNext);

		AfterSpace();
	}
	
	this->JsonNext = JsonArray;
	return JsonErrCode::Parse_OK;
}

baseee::parser::JsonErrCode
baseee::parser::JsonParser::ParseVulanObject() {
	BASEEE_assert(*Next == '{');
	Next++;
	bool skip = true;

	JsonData JsonObject;
	JsonObject.JsonType = JsonType::JsonType_Object;
	JsonObject.Data = std::multimap<std::string,JsonData>();

	auto ErrCode = JsonErrCode::Parse_OK;
	std::pair<std::string, JsonData> JsonKeyVulanPair;

	while (true) {
		if (Next == Json.cend()) return JsonErrCode::Parse_MissToken;
		else if (*Next == '}') { Next++; break; }
		else if (*Next == ',') Next++;
		// �ڣ�{"xx":xx]�У���Ҫ�Ȳ���"�����ж�
		else if (skip) skip = false;
		else return JsonErrCode::Parse_MissToken;
		
		//��ȡ��
		AfterSpace();
		ErrCode = ParseVulan();

		if (ErrCode != JsonErrCode::Parse_OK) 
			return ErrCode;

		if (JsonNext.JsonType != JsonType::JsonType_String)
			return JsonErrCode::Parse_UnknowError;

		JsonKeyVulanPair.first = std::get<std::string>(JsonNext.Data);
		//��ȡֵ
		AfterSpace();
		if (*Next != ':') return JsonErrCode::Parse_MissToken;
		else Next++;
		AfterSpace();
		ErrCode = ParseVulan();

		if (ErrCode != JsonErrCode::Parse_OK)
			return ErrCode;

	
		JsonKeyVulanPair.second.Data = JsonObject.Data;

		std::get<std::multimap<std::string, JsonData>>(JsonObject.Data)
			.insert(JsonKeyVulanPair);

		AfterSpace();
	}

	this->JsonNext = JsonObject;
	return JsonErrCode::Parse_OK;
}

std::string baseee::parser::JsonBuilder::Build(JsonTree jt) {
}


std::string baseee::parser::JsonBuilder::BuildArray(baseee::parser::JsonData JsonArray) {
	BASEEE_assert(JsonArray.JsonType == JsonType::JsonType_Array);
}
std::string baseee::parser::JsonBuilder::BuildObject(baseee::parser::JsonData JsonObject) {
	BASEEE_assert(JsonObject.JsonType == JsonType::JsonType_Object);
}
std::string baseee::parser::JsonBuilder::BuildKeyVulanPair(baseee::parser::JsonData JsonVulan) {
	double Number = 0.0;
	std::string String;
}