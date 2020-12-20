/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    jsonp.hpp
 * Content: json parser Head File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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

			JsonData() {}


			JsonData(std::string_view Value) {
				Data = std::string(Value);
				JsonT = JsonType::JsonType_String;

				return;
			}

			JsonData(double Value) {
				Data = Value;
				JsonT = JsonType::JsonType_Number;

				return;
			}

			JsonData(bool Value) {
				if (Value)
					JsonT = JsonType::JsonType_True;
				else
					JsonT = JsonType::JsonType_False;

				return;
			}

			JsonData(std::initializer_list<JsonData> Array) {
				Data = std::vector<JsonData>();
				JsonT = JsonType::JsonType_Array;
				for (auto s : Array) {
					std::get<std::vector<JsonData>>(Data).push_back(s);
				}

				return;
			}


		};

		//解析器错误代码
		enum class JsonParserErrorCode : int {
			Parse_OK = 0,//正常
			Parse_UnknowError,//未知错误
			Parse_MissValue,//无值
			Parse_ValueError,//值错误
			Parse_MissToken//找不到对应Token: {} [] "" ,
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
			std::string BuildString(std::string String);
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
			~JsonDataBuilder() {}

			//索引节点
			//如果无则创建一个空JsonType_Object节点
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


			void operator=(JsonData J) {
				Ptr->Data = J.Data;
				Ptr->JsonT = J.JsonT;

				return;
			}

			/*获取Value的方法*/
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

			//获取构造函数参数的指针
			JsonData* GetJsonTree()noexcept { return Ptr; }

			//释放构造函数指向的内存并执行析构函数
			void Release() {
				if (Ptr != nullptr)
					delete Ptr;
				this->~JsonDataBuilder();
				return;
			}

			//删除子节点
			void Delete(std::string_view String) {
				if (Ptr->JsonT == JsonType::JsonType_Object) {

					auto map = &std::get<std::multimap<std::string, JsonData>>(Ptr->Data);
					auto it = map->find(std::string(String));

					if (it != map->cend()) {
						map->erase(it);
						return;
					}
					else return;
				}
				else throw
					std::runtime_error(
						"JsonType of JsonRootPtr is not JsonType::JsonType_Object");
				return;
			}

			//查找节点
			std::optional<JsonDataBuilder> FindChild(std::string_view Name) {
				if (Ptr->JsonT == JsonType::JsonType_Object) {

					auto map = &std::get<std::multimap<std::string, JsonData>>(Ptr->Data);
					auto it = map->find(std::string(Name));

					if (it != map->cend()) {
						return 
							std::optional<JsonDataBuilder>((&(it->second)));
					}
					else return std::nullopt;
				}
				else throw
					std::runtime_error(
						"JsonType of JsonRootPtr is not JsonType::JsonType_Object");
				return std::nullopt;
			}

			//获取节点类型
			JsonType GetJsonType() noexcept{
				return Ptr->JsonT;
			}

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
			JsonErrCode ParseValue() noexcept;

			JsonErrCode ParseValueNull() noexcept;
			JsonErrCode ParseValueBool() noexcept;
			JsonErrCode ParseValueTrue() noexcept;
			JsonErrCode ParseValueFalse() noexcept;
			JsonErrCode ParseValueNumber() noexcept;
			JsonErrCode ParseValueString() noexcept;
			std::optional<std::string> ParseValueUnicode() noexcept;
			JsonErrCode ParseValueArray() noexcept;
			JsonErrCode ParseValueObject() noexcept;

			inline bool MatchCharRange(char a, char b) noexcept;

			bool IteratorMatch(std::string_view str) noexcept;
		};

	}
}