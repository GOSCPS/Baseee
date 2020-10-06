/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     inip.hpp
 * Content:  ini parser head file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <string>
#include <map>
#include <optional>
#include <set>

namespace baseee {
	namespace parser {

		class IniParser {
		public:
			IniParser(const IniParser&) = delete;
			IniParser& operator=(const IniParser&) = delete;
			IniParser() noexcept {}

			int Parser(std::string_view Ini) noexcept;

			std::optional<int64_t> GetInt(std::string_view section, std::string_view name) noexcept;
			std::optional<double> GetDouble(std::string_view section, std::string_view name) noexcept;
			std::optional<std::string> GetString(std::string_view section, std::string_view name) noexcept;

			std::set<std::string> GetSection() noexcept;

		private:
			bool IsGood = true;
			std::set<std::string> SectionList;
			std::map<std::string, std::map<std::string, int64_t>> IntPool;
			std::map<std::string, std::map<std::string, double>> DoublePool;
			std::map<std::string, std::map<std::string, std::string>> StringPool;
		};

	}

}












