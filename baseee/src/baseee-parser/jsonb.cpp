/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     jsonb.cpp
 * Content:  json builder file
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
#include <exception>
#include <map>
#include "jsonp.hpp"
#include "../baseee-test/test.hpp"
#include "../baseee-string/string.hpp"



std::string baseee::parser::JsonBuilder::Build(JsonData jt) noexcept {
	std::string out;

	if (jt.JsonT == JsonType::JsonType_Object)
		out += BuildObject(jt) + (this->BeautlfulFormat ? "\n" : "");

	return out;
}


std::string baseee::parser::JsonBuilder::BuildArray(baseee::parser::JsonData JsonArray) noexcept {
	BASEEE_assert(JsonArray.JsonT == JsonType::JsonType_Array);
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


std::string baseee::parser::JsonBuilder::BuildObject(baseee::parser::JsonData JsonObject) noexcept {
	BASEEE_assert(JsonObject.JsonT == JsonType::JsonType_Object);

	std::string out = (this->BeautlfulFormat ? "{\n" : "{");
	std::multimap<std::string, JsonData> obj = std::get<std::multimap<std::string, JsonData>>(JsonObject.Data);
	for (auto a : obj) {
		out += BuildKeyVulanPair(a) + (this->BeautlfulFormat ? ",\n" : ",");
	}

	out = out.substr(0, 
		(this->BeautlfulFormat ? out.size() - 2 : out.size() - 1));
	out += "}";
	return out;
}


std::string baseee::parser::JsonBuilder::BuildKeyVulanPair(
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
			std::get<std::string>(Data.second.Data)
			+ "\"";
		break;
	default:
		break;
	}

	return out;
}


std::optional<baseee::parser::JsonData> 
baseee::parser::JsonDataBuilder::AddJsonData(
	JsonData p,
	std::string_view name,
	const JsonData d) noexcept {

	if (p.JsonT == JsonType::JsonType_Object) {
		std::get<std::multimap<std::string, JsonData>>(p.Data)
			.insert(std::make_pair(name, d));
		return p;
	}
	return std::nullopt;
}