/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    jsonb.cpp
 * Content: json build Source File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <regex>
#include <array>
#include <optional>
#include <variant>
#include <exception>
#include <map>
#include "jsonp.hpp"
#include "../baseee-test/test.hpp"
#include "../baseee-string/string.hpp"



std::string baseee::parser::JsonStringBuilder::Build(JsonData jt) noexcept {
	std::string out;

	if (jt.JsonT == JsonType::JsonType_Object)
		out += BuildObject(jt) + (this->BeautlfulFormat ? "\n" : "");

	return out;
}


std::string baseee::parser::JsonStringBuilder::BuildArray(baseee::parser::JsonData JsonArray) noexcept {
	std::string out = "[";

	for (auto s : std::get<std::vector<JsonData>>(JsonArray.Data)) {
		switch (s.JsonT)
		{
		case JsonType::JsonType_False:
			out += "false";
			break;
		case JsonType::JsonType_True:
			out += "true";
			break;
		case JsonType::JsonType_Null:
			out += "null";
			break;
		case JsonType::JsonType_Number:
			out += std::to_string(std::get<double>(s.Data));
			break;
		case JsonType::JsonType_Object:
			out += BuildObject(s);
			break;
		case JsonType::JsonType_String:
			out += "\"" + std::get<std::string>(s.Data) + "\"";
			break;
		case JsonType::JsonType_Array:
			out += BuildArray(s);
			break;
		default:
			break;
		}
		out += ",";
	}
	
	out = out.substr(0, out.size() - 1);
	out += "]";
	return out;
}


std::string baseee::parser::JsonStringBuilder::BuildObject(baseee::parser::JsonData JsonObject) noexcept {

	std::string out = (this->BeautlfulFormat ? "{\n" : "{");
	std::multimap<std::string, JsonData> obj = std::get<std::multimap<std::string, JsonData>>(JsonObject.Data);
	for (auto a : obj) {
		out += BuildKeyVulanPair(a) + (this->BeautlfulFormat ? ",\n" : ",");
	}

	if(obj.size() != 0)
	out = out.substr(0, 
		(this->BeautlfulFormat ? out.size() - 2 : out.size() - 1));

	BeautlfulFormat ? out += "\n}" : out+="}";
	return out;
}


std::string baseee::parser::JsonStringBuilder::BuildKeyVulanPair(
	std::pair<std::string, JsonData> Data) noexcept {
	double Number = 0.0;
	std::string out;

	if (Data.second.JsonT == JsonType::JsonType_Array)
		return "\"" + Data.first + "\":" + BuildArray(Data.second);
	else switch (Data.second.JsonT)
	{
	case JsonType::JsonType_False:
		out = "\"" + Data.first + "\":" + "false";
		break;
	case JsonType::JsonType_True:
		out = "\"" + Data.first + "\":" + "true";
		break;
	case JsonType::JsonType_Null:
		out = "\"" + Data.first + "\":" + "null";
		break;
	case JsonType::JsonType_Number:
		out = "\"" + Data.first + "\":" +
			std::to_string(std::get<double>(Data.second.Data));
		break;
	case JsonType::JsonType_Object:
		out = "\"" + Data.first + "\":" + 
			BuildObject(Data.second);
		break;
	case JsonType::JsonType_String:
		out = "\"" + Data.first + "\":\"" + 
			BuildString(
				std::get<std::string>(Data.second.Data))
			+ "\"";
		break;
	default:
		break;
	}

	return out;
}

std::string baseee::parser::JsonStringBuilder::BuildString(std::string String) {
	std::string Out;
	for (auto s : String) {
		switch (s)
		{
		case '\n':
			Out.append("\\n");
			break;
		case '\"':
			Out.append("\\\"");
			break;
		case '\\':
			Out.append("\\\\");
			break;
		case '\b':
			Out.append("\\b");
			break;
		case '\f':
			Out.append("\\f");
			break;
		case '\r':
			Out.append("\\r");
			break;
		case '\t':
			Out.append("\\t");
			break;
		default:
			Out.append({ s });
			break;
		}
	}
	return Out;
}