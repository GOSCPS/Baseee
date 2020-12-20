/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    inip.hpp
 * Content: ini parser Head File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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