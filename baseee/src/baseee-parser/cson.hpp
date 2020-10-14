/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     inip.hpp
 * Content:  cson parser head file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <variant>
#include <memory>
#include <optional>
#include <map>


namespace baseee {
	namespace parser {

		enum class CsonParserErrorCode : int8_t {
			Ok,
			Error,
			MissToken
		};

		class CsonData {

		};

		


		class CsonParser {
		public:
			CsonParser(const CsonParser&) = delete;
			CsonParser& operator=(const CsonParser&) = delete;
			CsonParser() {}






		private:


		};

	}
}