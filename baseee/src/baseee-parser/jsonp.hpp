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
			JsonType JsonType = JsonType::JsonType_Null;
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

		//Json��
		class JsonTree {
		public:
			JsonTree() {}
			JsonTree(std::vector<JsonData> jt)
			{
				JsonObjectList = jt;
			}
			std::vector<JsonData> JsonObjectList;
		};


		//Json������
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
			std::string BuildKeyVulanPair(std::pair<std::string, JsonData> Data);
		};

		//��λһ��JsonTreeԪ�ص�·��
		using JsonTreePath = JsonData*;

		//���û�ʹ�õ�Json������
		//����Tree��JsonBuilder�����ı�
		class JsonTreeBuilder {
		public:
			//���Դ�0�������е�JsonTree��ʼ����
			JsonTreeBuilder() { }
			JsonTreeBuilder(JsonTree jt) { JT = jt; }

			//��ȡ��
			JsonTreePath GetRoot();

			/*���²�����Ϊ�ڸ���/�Ӹ�����*/
			//��Ӷ���
			JsonTreePath AddNumber(JsonTreePath p,std::string_view name,double number);
			JsonTreePath AddBoolean(JsonTreePath p,std::string_view name,bool boolean);
			JsonTreePath AddString(JsonTreePath p,std::string_view name,std::string_view String);
			JsonTreePath AddNull(JsonTreePath p,std::string_view name);

			//���Object
			JsonTreePath AddObject(JsonTreePath p, std::string_view name);

			//���Array
			JsonTreePath AddNumberArray(
				JsonTreePath p, 
				std::string_view name, 
				double number[],
				size_t length);

			JsonTreePath AddBooleanArray(
				JsonTreePath p,
				std::string_view name,
				bool boolean[], 
				size_t length);

			JsonTreePath AddStringArray(
				JsonTreePath p,
				std::string_view name, 
				std::string_view String[],
				size_t length);

			JsonTreePath AddNullArray(
				JsonTreePath p,
				std::string_view name,
				size_t length);

			JsonTreePath AddJsonData(
				JsonTreePath p,
				std::string_view name,
				JsonData d);

			/*һЩ��������*/
			void DeleteJson(JsonTreePath p,std::string_view name);
			std::vector<JsonTreePath> GetChildrenList(JsonTreePath p);
			JsonTreePath GoChuild(JsonTreePath p,std::string_view name);
		private:
			JsonTree JT;
			JsonTreePath AddTo(JsonTreePath p, JsonData d, std::string_view name);
		};

		//Json������
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

			//����Object
			std::optional<baseee::parser::JsonData> 
				FindChildren(std::string_view Name);

		private:
			JsonErrCode LastError = JsonErrCode::Parse_OK;

			std::string Json;//Json�ַ���
			std::string::const_iterator Next;//Json������

			//Json�����
			std::vector<JsonData> JsonPool;
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