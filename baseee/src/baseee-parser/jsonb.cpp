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



std::string baseee::parser::JsonBuilder::Build(JsonTree jt) {
	std::string out;

	for (auto& json : jt.JsonObjectList) {
		if (json.JsonType == JsonType::JsonType_Object) {
			out += BuildObject(json) + (this->BeautlfulFormat ? "\n" : "");
		}
	}

	return out;
}


std::string baseee::parser::JsonBuilder::BuildArray(baseee::parser::JsonData JsonArray) {
	BASEEE_assert(JsonArray.JsonType == JsonType::JsonType_Array);
	std::string out = "[";

	for (auto s : std::get<std::vector<JsonData>>(JsonArray.Data)) {
		switch (s.JsonType)
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


std::string baseee::parser::JsonBuilder::BuildObject(baseee::parser::JsonData JsonObject) {
	BASEEE_assert(JsonObject.JsonType == JsonType::JsonType_Object);

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
	std::pair<std::string, JsonData> Data) {
	double Number = 0.0;
	std::string out;

	if (Data.second.JsonType == JsonType::JsonType_Array)
		return "\"" + Data.first + "\":" + BuildArray(Data.second);
	else switch (Data.second.JsonType)
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


baseee::parser::JsonTreePath 
baseee::parser::JsonTreeBuilder::GetRoot() {
	int RootPath = 0;

	if (this->JT.JsonObjectList.size() == 1 &&
		this->JT.JsonObjectList[0].JsonType == JsonType::JsonType_Object) {
		return &this->JT.JsonObjectList[0];
	}

	else for (auto p : JT.JsonObjectList) {
		if (p.JsonType == JsonType::JsonType_Object)
			return &this->JT.JsonObjectList[RootPath];
		else RootPath++;
	}
	return nullptr;
}

baseee::parser::JsonTreePath  
baseee::parser::JsonTreeBuilder::AddNumber(JsonTreePath p, std::string_view name, double number) {
	JsonData TmpData;
	TmpData.JsonType = JsonType::JsonType_Number;
	TmpData.Data = number;

	return AddTo(p, TmpData, name);
}


baseee::parser::JsonTreePath  
baseee::parser::JsonTreeBuilder::AddBoolean(JsonTreePath p, std::string_view name, bool boolean) {
	JsonData TmpData;

	if (boolean)
		TmpData.JsonType = JsonType::JsonType_True;
	else
		TmpData.JsonType = JsonType::JsonType_False;

	return AddTo(p, TmpData, name);
}


baseee::parser::JsonTreePath  
baseee::parser::JsonTreeBuilder::AddString(JsonTreePath p, std::string_view name, std::string_view String) {
	JsonData TmpData;
	TmpData.JsonType = JsonType::JsonType_String;
	TmpData.Data = std::string(String);

	return AddTo(p, TmpData, name);
}


baseee::parser::JsonTreePath  
baseee::parser::JsonTreeBuilder::AddNull(JsonTreePath p, std::string_view name) {
	JsonData TmpData;
	TmpData.JsonType = JsonType::JsonType_Null;

	return AddTo(p, TmpData, name);
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddTo(JsonTreePath p, JsonData d,std::string_view name) {
	if (p->JsonType == JsonType::JsonType_Object) {
		auto it = std::get<std::multimap<std::string, JsonData>>(p->Data);
		JsonData TmpData;

		TmpData.JsonType = d.JsonType;
		TmpData.Data = d.Data;

		return &(*(it.insert(std::make_pair<>(name, TmpData)))).second;
	}
	else return nullptr;
}


baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddObject(
	JsonTreePath p, 
	std::string_view name) {

	JsonData TmpData;
	TmpData.JsonType = JsonType::JsonType_Object;
	TmpData.Data = std::multimap<std::string, JsonData>();

	return AddTo(p, TmpData, name);
}


baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddJsonData(
	JsonTreePath p,
	std::string_view name,
	JsonData d) {
	return AddTo(p,d,name);
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddNumberArray(
	JsonTreePath p,
	std::string_view name,
	double number[],
	size_t length) {

	JsonData TmpData;

	TmpData.JsonType = JsonType::JsonType_Array;
	TmpData.Data = std::vector<JsonData>();
	
	for (int a = 0; a < length; a++) {
		JsonData j;
		j.JsonType = JsonType::JsonType_Number;
		j.Data = number[a];
		std::get<std::vector<JsonData>>(TmpData.Data)
			.push_back(j);
	}
	return AddTo(p, TmpData,name);
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddBooleanArray(
	JsonTreePath p,
	std::string_view name,
	bool boolean[],
	size_t length) {

	JsonData TmpData;

	TmpData.JsonType = JsonType::JsonType_Array;
	TmpData.Data = std::vector<JsonData>();

	for (int a = 0; a < length; a++) {
		JsonData j;
		j.JsonType = (boolean[a] ? JsonType::JsonType_True : JsonType::JsonType_False);
		std::get<std::vector<JsonData>>(TmpData.Data)
			.push_back(j);
	}
	return AddTo(p, TmpData, name);
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddStringArray(
	JsonTreePath p,
	std::string_view name,
	std::string_view String[],
	size_t length) {
	JsonData TmpData;

	TmpData.JsonType = JsonType::JsonType_Array;
	TmpData.Data = std::vector<JsonData>();

	for (int a = 0; a < length; a++) {
		JsonData j;
		j.JsonType = JsonType::JsonType_String;
		j.Data = std::string(String[a]);
		std::get<std::vector<JsonData>>(TmpData.Data)
			.push_back(j);
	}
	return AddTo(p, TmpData, name);
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::AddNullArray(
	JsonTreePath p,
	std::string_view name,
	size_t length) {
	JsonData TmpData;

	TmpData.JsonType = JsonType::JsonType_Array;
	TmpData.Data = std::vector<JsonData>();

	for (int a = 0; a < length; a++) {
		JsonData j;
		j.JsonType = JsonType::JsonType_Null;
		std::get<std::vector<JsonData>>(TmpData.Data)
			.push_back(j);
	}
	return AddTo(p, TmpData, name);
}

void
baseee::parser::JsonTreeBuilder::DeleteJson(JsonTreePath p, std::string_view name) {
	if (p->JsonType != JsonType::JsonType_Object) return;
	else {
		auto it = std::get<std::multimap<std::string, JsonData>>(p->Data);
		auto fit = it.find(std::string(name));
		if (fit != it.cend()) it.erase(fit);
		else return;
	}
}

std::vector<baseee::parser::JsonTreePath>
baseee::parser::JsonTreeBuilder::GetChildrenList(JsonTreePath p) {
	if (p->JsonType != JsonType::JsonType_Object) return;
	else {
		auto it = std::get<std::multimap<std::string, JsonData>>(p->Data);
		std::vector<baseee::parser::JsonTreePath> out;

		for (auto& s : it) {
			out.push_back(&s.second);
		}
		return out;
	}
}

baseee::parser::JsonTreePath
baseee::parser::JsonTreeBuilder::GoChuild(JsonTreePath p, std::string_view name) {
	if (p->JsonType != JsonType::JsonType_Object) return;
	else {
		auto it = std::get<std::multimap<std::string, JsonData>>(p->Data);
		auto fit = it.find(std::string(name));
		if (fit != it.cend()) return &(*fit).second;
		else return;
	}
}