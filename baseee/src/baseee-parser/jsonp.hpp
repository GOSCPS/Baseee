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
#include <memory>
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
			JsonType JsonT = JsonType::JsonType_Null;
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


		//Json生成器
		class JsonBuilder {
		public:
			JsonBuilder() = default;

			void SetBeautiful(bool b) { BeautlfulFormat = b; }

			std::string Build(JsonData jt);

		private:
			bool BeautlfulFormat = false;

			std::string BuildArray(JsonData JsonArray);
			std::string BuildObject(JsonData JsonObject);
			std::string BuildKeyVulanPair(std::pair<std::string, JsonData> Data);
		};

		//using JsonDataPath = JsonData*;

		//给用户使用的Json生成器
		//生成Tree供JsonBuilder生成文本
		class JsonDataBuilder {
		public:
			JsonDataBuilder() {
				RootData.JsonT = JsonType::JsonType_Object;
				RootData.Data = std::multimap<std::string, JsonData>();
			}
			JsonDataBuilder(JsonData &data) {
				RootData.Data = data.Data;
				RootData.JsonT = data.JsonT;
			}

			//在p处添加一个JsonData
			static std::optional<baseee::parser::JsonData>
				AddJsonData(
				JsonData p,
				std::string_view name,
				const JsonData d);

			//返回Json Tree Root的引用
			JsonData GetJsonData() { return RootData; }

		private:
			JsonData RootData;
		};


		//Json解析器
		class JsonParser {
		public:
			JsonParser(const JsonParser&) = delete;

			JsonParser() { JsonNext.JsonT = JsonType::JsonType_Null; }
			~JsonParser() = default;

			JsonErrCode Parser(std::string_view JsonStr);

			JsonData GetJsonData() {
				return JsonData(JsonPool);
			}

			//查找Object
			std::optional<baseee::parser::JsonData> 
				FindChildren(std::string_view Name);

		private:

			std::string Json;//Json字符串
			std::string::const_iterator Next;//Json解析流

			//Json对象池
			JsonData JsonPool;
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