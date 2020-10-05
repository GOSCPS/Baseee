/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     jsonp.hpp
 * Content:  json parser head file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <variant>
#include <optional>
#include <map>

namespace baseee {
	namespace parser {

		//Json类型
		enum class JsonType : int {
			JsonType_Null,
			JsonType_True,
			JsonType_False,
			JsonType_Number,
			JsonType_String,
			JsonType_Array,
			JsonType_Object
		};

		//Json数据结构
		class JsonData {
		public:
			std::variant<
				double,
				std::string,
				std::vector<JsonData>,
				std::multimap<std::string, JsonData>>
				Data = 0.0;
			JsonType JsonType = JsonType::JsonType_Null;
		};

		//解析器错误代码
		enum class JsonParserErrorCode : int {
			Parse_OK = 0,//正常
			Parse_UnknowError,//未知错误
			Parse_MissVulan,//无值
			Parse_VulanError,//值错误
			Parse_MissToken//找不到对应Token {} [] "" ,
		};

		using JsonErrCode = JsonParserErrorCode;

		//Json树
		class JsonTree {
		public:
			JsonTree(std::vector<JsonData> jt)
			{
				JsonObjectList = jt;
			}
			std::vector<JsonData> JsonObjectList;
		};


		//Json生成器
		class JsonBuilder {
		public:
			JsonBuilder() = default;

			void SetBeautiful(bool b) { BeautlfulFormat = b; }

			std::string Build(JsonTree jt);

		private:
			bool BeautlfulFormat = false;
			JsonTree BuildInfo;

			std::string BuildArray(JsonData JsonArray);
			std::string BuildObject(JsonData JsonObject);
			std::string BuildKeyVulanPair(JsonData JsonVulan);
		};

		//Json解析器
		class JsonParser {
		public:
			JsonParser(const JsonParser&) = delete;

			JsonParser() { JsonNext.JsonType = JsonType::JsonType_Null; }
			~JsonParser() = default;

			JsonErrCode Parser(std::string_view JsonStr);

			JsonErrCode GetLastError() { return LastError; }

			JsonTree GetJsonTree() {
				return JsonTree(JsonPool);
			}

		private:
			JsonErrCode LastError = JsonErrCode::Parse_OK;

			std::string Json;//Json字符串
			std::string::const_iterator Next;//Json解析流

			//Json对象池
			std::vector<JsonData> JsonPool;
			//当前构建的Json
			JsonData JsonNext;

			void AfterSpace();
			JsonErrCode ParseVulan();

			JsonErrCode ParseVulanNull();
			JsonErrCode ParseVulanBool();
			JsonErrCode ParseVulanTrue();
			JsonErrCode ParseVulanFalse();
			JsonErrCode ParseVulanNumber();
			JsonErrCode ParseVulanString();
			std::optional<std::string> ParseVulanUnicode();
			JsonErrCode ParseVulanArray();
			JsonErrCode ParseVulanObject();

			inline bool MatchCharRange(char a, char b);

			bool IteratorMatch(std::string_view str);
		};

	}
}