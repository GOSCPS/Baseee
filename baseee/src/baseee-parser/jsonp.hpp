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
		};

		//�������������
		enum class JsonParserErrorCode : int {
			Parse_OK = 0,//����
			Parse_UnknowError,//δ֪����
			Parse_MissVulan,//��ֵ
			Parse_VulanError,//ֵ����
			Parse_MissToken//�Ҳ�����ӦToken {} [] "" ,
		};

		using JsonErrCode = JsonParserErrorCode;


		//Json������
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

		//���û�ʹ�õ�Json������
		//����Tree��JsonBuilder�����ı�
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

			//��p�����һ��JsonData
			static std::optional<baseee::parser::JsonData>
				AddJsonData(
				JsonData p,
				std::string_view name,
				const JsonData d);

			//����Json Tree Root������
			JsonData GetJsonData() { return RootData; }

		private:
			JsonData RootData;
		};


		//Json������
		class JsonParser {
		public:
			JsonParser(const JsonParser&) = delete;

			JsonParser() { JsonNext.JsonT = JsonType::JsonType_Null; }
			~JsonParser() = default;

			JsonErrCode Parser(std::string_view JsonStr);

			JsonData GetJsonData() {
				return JsonData(JsonPool);
			}

			//����Object
			std::optional<baseee::parser::JsonData> 
				FindChildren(std::string_view Name);

		private:

			std::string Json;//Json�ַ���
			std::string::const_iterator Next;//Json������

			//Json�����
			JsonData JsonPool;
			//��ǰ������Json
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