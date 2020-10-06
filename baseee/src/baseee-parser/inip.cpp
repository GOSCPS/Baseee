/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     inip.cpp
 * Content:  ini parser file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>
#include <map>
#include <optional>
#include <set>
#include <regex>
#include <iostream>
#include "inip.hpp"
#include "../baseee-string/string.hpp"


std::set<std::string> baseee::parser::IniParser::GetSection() noexcept {
	return SectionList;
}


std::optional<int64_t> baseee::parser::IniParser::GetInt(std::string_view section, std::string_view name) noexcept {
	auto it = this->IntPool.find(std::string(section));

	if (it != IntPool.cend()) {
		auto its = (*it).second.find(std::string(name));
		if (its != (*it).second.cend()) {
			return (*its).second;
		}
	}

	return std::nullopt;
}

std::optional<double> baseee::parser::IniParser::GetDouble(std::string_view section, std::string_view name) noexcept {
	auto it = this->DoublePool.find(std::string(section));

	if (it != DoublePool.cend()) {
		auto its = (*it).second.find(std::string(name));
		if (its != (*it).second.cend()) {
			return (*its).second;
		}
	}

	return std::nullopt;
}

std::optional<std::string> baseee::parser::IniParser::GetString(std::string_view section, std::string_view name) noexcept {
	auto it = this->StringPool.find(std::string(section));

	if (it != StringPool.cend()) {
		auto its = (*it).second.find(std::string(name));
		if (its != (*it).second.cend()) {
			return (*its).second;
		}
	}

	return std::nullopt;
}



int baseee::parser::IniParser::Parser(std::string_view Ini) noexcept {
	if (std::string(Ini).empty()) return 0;

	std::string Identifier("[a-zA-Z0-9_-]+");
	std::string Number("[+-]{0,1}[0-9]+");
	std::string Point("[+-]{0,1}[0-9]+\\.[0-9]+");
	std::string Str("\".+\"");
	std::string SimpleStr(".+");

	std::regex Section("\\[(" + Identifier + ")\\]");

	std::regex IniNumberName("(" + Identifier + ")=" + Number);
	std::regex IniNumberVulan(Identifier + "=(" + Number + ")");

	std::regex IniPointName("(" + Identifier + ")=" + Point);
	std::regex IniPointVulan(Identifier + "=(" + Point + ")");

	std::regex IniStrName("(" + Identifier + ")=" + Str);
	std::regex IniStrVulan(Identifier + "=(" + Str + ")");

	std::regex IniSimpleStrName("(" + Identifier + ")=" + SimpleStr);
	std::regex IniSimpleStrVulan(Identifier + "=(" + SimpleStr + ")");


	std::string NowSection = "";
	std::smatch matchResult;

	std::string BufferedName = "";
	std::string BufferedVulan = "";
	auto Tokens = baseee::string::Split(std::string(Ini), "[\\n\\r]");

	int line = 0;

	for (auto Token : Tokens) {
		line++;
		Token = baseee::string::Trim<std::string,char>(Token);
		if (Token.size() >= 1 && Token[0] == ';') {
			continue;
		}
		
		//Æ¥Åä¶Î
		if (std::regex_match(Token, matchResult, Section)) {
			NowSection = "";
			for (size_t i = 1; i < matchResult.size(); ++i)
			{
				NowSection.append(matchResult[i]);
			}
			this->SectionList.insert(NowSection);
			continue;
		}

		//Æ¥ÅäÊý×Ö
		else if(std::regex_match(Token, matchResult, IniNumberName)) {
			BufferedName = "";
			BufferedVulan = "";
			for (size_t i = 1; i < matchResult.size(); ++i)
			{
				BufferedName.append(matchResult[i]);
			}

			if (std::regex_match(Token, matchResult, IniNumberVulan)) {
				for (size_t i = 1; i < matchResult.size(); ++i)
				{
					BufferedVulan.append(matchResult[i]);
				}
			}
			else return line;

			this->IntPool[NowSection].insert(std::make_pair(BufferedName, std::atoll(BufferedVulan.c_str())));

			continue;
		}

		//Æ¥Åä¸¡µãÊý
		else if (std::regex_match(Token, matchResult, IniPointName)) {
			BufferedName = "";
			BufferedVulan = "";
			for (size_t i = 1; i < matchResult.size(); ++i)
			{
				BufferedName.append(matchResult[i]);
			}

			if (std::regex_match(Token, matchResult, IniPointVulan)) {
				for (size_t i = 1; i < matchResult.size(); ++i)
				{
					BufferedVulan.append(matchResult[i]);
				}
			}
			else return line;

			this->DoublePool[NowSection].insert(std::make_pair(BufferedName, std::stod(BufferedVulan.c_str())));

			continue;
		}

		//Æ¥Åä×Ö·û´®
		else if (std::regex_match(Token, matchResult, IniStrName)) {
			BufferedName = "";
			BufferedVulan = "";
			for (size_t i = 1; i < matchResult.size(); ++i)
			{
				BufferedName.append(matchResult[i]);
			}

			if (std::regex_match(Token, matchResult, IniStrVulan)) {
				for (size_t i = 1; i < matchResult.size(); ++i)
				{
					BufferedVulan.append(matchResult[i]);
				}
			}
			else return line;

			//É¾³ýÍ·Î²Ë«ÒýºÅ
			BufferedVulan = BufferedVulan.substr(1, BufferedVulan.size() - 2);
			this->StringPool[NowSection].insert(std::make_pair(BufferedName, 
				BufferedVulan));

			continue;
		}

		//Æ¥Åä¼òµ¥×Ö·û´®
		else if (std::regex_match(Token, matchResult, IniSimpleStrName)) {
			BufferedName = "";
			BufferedVulan = "";
			for (size_t i = 1; i < matchResult.size(); ++i)
			{
				BufferedName.append(matchResult[i]);
			}

			if (std::regex_match(Token, matchResult, IniSimpleStrVulan)) {
				for (size_t i = 1; i < matchResult.size(); ++i)
				{
					BufferedVulan.append(matchResult[i]);
				}
			}
			else return line;

			this->StringPool [NowSection] .insert(std::make_pair(BufferedName, BufferedVulan.c_str()));

			continue;
		}

		else return line;
	}

	return 0;
}