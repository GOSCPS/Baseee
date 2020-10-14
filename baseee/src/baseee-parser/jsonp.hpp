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

		static JsonData* CreateNewJsonTree() {
			JsonData* JsonPtr;
			JsonPtr = new JsonData;
			JsonPtr->Data = std::multimap<std::string, JsonData>();
			JsonPtr->JsonT = JsonType::JsonType_Object;
			return JsonPtr;
		}

		//Json字符串生成器
		class JsonStringBuilder {
		public:
			JsonStringBuilder() = default;

			void SetBeautiful(bool b) { BeautlfulFormat = b; }

			std::string Build(JsonData jt) noexcept;

		private:
			bool BeautlfulFormat = false;

			std::string BuildArray(JsonData JsonArray) noexcept;
			std::string BuildObject(JsonData JsonObject) noexcept;
			std::string BuildKeyVulanPair(std::pair<std::string, JsonData> Data) noexcept;
		};


		//JsonData操作器
		class JsonDataBuilder {
		public:
			JsonDataBuilder& operator=(const JsonDataBuilder&) = delete;
			JsonDataBuilder(const JsonDataBuilder&) = delete;
			JsonDataBuilder(JsonData* J) {
				if (J != nullptr)
					Ptr = J;
				else throw std::runtime_error("Json Data is Null");
			}

			JsonDataBuilder operator[](std::string_view index) {
				if (Ptr->JsonT == JsonType::JsonType_Object) {

					auto map = &std::get<std::multimap<std::string, JsonData>>(Ptr->Data);
					auto it = map->find(std::string(index));

					if (it != map->cend()) {
						return JsonDataBuilder(&(it->second));
					}
					else {
						JsonData data;
						data.Data = std::multimap<std::string, JsonData>();
						data.JsonT = JsonType::JsonType_Object;
						return 
							JsonDataBuilder(
								&map->
								insert(std::make_pair(index, data))
								->second);
					}

				}
				else throw 
					std::runtime_error(
						"JsonType of JsonRootPtr is not JsonType::JsonType_Object");
				return JsonDataBuilder(nullptr);
			}

			void operator=(std::string_view vulan) {
				std::string String(vulan);
				Ptr->JsonT = JsonType::JsonType_String;
				Ptr->Data = String;

				return;
			}

			void operator=(double vulan) {
				Ptr->JsonT = JsonType::JsonType_Number;
				Ptr->Data = vulan;

				return;
			}

			void SetBoolean(bool vulan) {
				if (vulan)
					Ptr->JsonT = JsonType::JsonType_True;
				else Ptr->JsonT = JsonType::JsonType_False;

				return;
			}

			std::optional<std::string> GetString() {
				if (Ptr->JsonT == JsonType::JsonType_String)
					return std::get<std::string>(Ptr->Data);
				else return std::nullopt;
			}

			std::optional<double> GetNumber() {
				if (Ptr->JsonT == JsonType::JsonType_Number)
					return std::get<double>(Ptr->Data);
				else return std::nullopt;
			}

			std::optional<bool> GetBoolean() {
				if (Ptr->JsonT == JsonType::JsonType_False)
					return false;
				else if (Ptr->JsonT == JsonType::JsonType_True)
					return true;
				else return std::nullopt;
			}


			JsonData* GetJsonTree() { return Ptr; }

		private:
			JsonData* Ptr;
		};


		//Json解析器
		class JsonParser {
		public:
			JsonParser(const JsonParser&) = delete;
			JsonParser& operator=(const JsonParser&) = delete;

			JsonParser() { JsonNext.JsonT = JsonType::JsonType_Null; }
			~JsonParser() = default;

			JsonErrCode Parser(std::string_view JsonStr) noexcept;

			JsonData GetJsonData() noexcept {
				return JsonData(JsonPool);
			}

		private:

			std::string Json;//Json字符串
			std::string::const_iterator Next;//Json解析流

			//Json对象池
			JsonData JsonPool;
			//当前构建的Json
			JsonData JsonNext;

			void AfterSpace() noexcept;
			JsonErrCode ParseVulan() noexcept;

			JsonErrCode ParseVulanNull() noexcept;
			JsonErrCode ParseVulanBool() noexcept;
			JsonErrCode ParseVulanTrue() noexcept;
			JsonErrCode ParseVulanFalse() noexcept;
			JsonErrCode ParseVulanNumber() noexcept;
			JsonErrCode ParseVulanString() noexcept;
			std::optional<std::string> ParseVulanUnicode() noexcept;
			JsonErrCode ParseVulanArray() noexcept;
			JsonErrCode ParseVulanObject() noexcept;

			inline bool MatchCharRange(char a, char b) noexcept;

			bool IteratorMatch(std::string_view str) noexcept;
		};

	}
}