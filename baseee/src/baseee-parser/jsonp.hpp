/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ����ļ����� GOSCPS(https://github.com/GOSCPS)
 * ʹ�� GOSCPS ���֤
 * File:    jsonp.hpp
 * Content: json parser Head File
 * Copyright (c) 2020 GOSCPS ��������Ȩ��.
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

		//Json����
		enum class JsonType : int {
			JsonType_Null,
			JsonType_True,
			JsonType_False,
			JsonType_Number,
			JsonType_String,
			JsonType_Array,
			JsonType_Object
		};

		//Json���ݽṹ
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

		//�������������
		enum class JsonParserErrorCode : int {
			Parse_OK = 0,//����
			Parse_UnknowError,//δ֪����
			Parse_MissValue,//��ֵ
			Parse_ValueError,//ֵ����
			Parse_MissToken//�Ҳ�����ӦToken: {} [] "" ,
		};

		using JsonErrCode = JsonParserErrorCode;

		static JsonData* CreateNewJsonTree() {
			JsonData* JsonPtr;
			JsonPtr = new JsonData;
			JsonPtr->Data = std::multimap<std::string, JsonData>();
			JsonPtr->JsonT = JsonType::JsonType_Object;
			return JsonPtr;
		}

		//Json�ַ���������
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


		//JsonData������
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

			//�����ڵ�
			//������򴴽�һ����JsonType_Object�ڵ�
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

			/*��ȡValue�ķ���*/
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

			//��ȡ���캯��������ָ��
			JsonData* GetJsonTree()noexcept { return Ptr; }

			//�ͷŹ��캯��ָ����ڴ沢ִ����������
			void Release() {
				if (Ptr != nullptr)
					delete Ptr;
				this->~JsonDataBuilder();
				return;
			}

			//ɾ���ӽڵ�
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

			//���ҽڵ�
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

			//��ȡ�ڵ�����
			JsonType GetJsonType() noexcept{
				return Ptr->JsonT;
			}

		private:
			JsonData* Ptr;
		};


		//Json������
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

			std::string Json;//Json�ַ���
			std::string::const_iterator Next;//Json������

			//Json�����
			JsonData JsonPool;
			//��ǰ������Json
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