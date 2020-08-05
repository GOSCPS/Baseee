#pragma once
// string.hpp�ַ�����������
//MIT License
//Copyright(c) 2020 chhdao
//
#include "string.cpp"
#include <string>
#include <regex>
#include <vector>

namespace baseee {
	namespace string {
		//wstring��
		//trim:ȥ��ͷβ�ո�
		//����string
		std::string trim(const std::string& s);
		std::string HeadTrim(const std::string& s);
		std::string EndTrim(const std::string& s);

		//split������������ʽ�ָ��ַ��������ؽ����
		//s�ַ�����r������ʽ
		std::vector<std::string> split(const std::string& s, const std::string& r);
		std::vector<std::string> split(const std::string& s, const std::regex& r);

		//ExpandsTabs ��tabת��Ϊ�ո�
		//Ĭ��һ��tabΪ8�ո�
		std::string ExpandsTabs(const std::string& s, const int TabSizes);

		// *With�ж��ַ����Ƿ���end/start��β/��ͷ
		bool StartsWith(const std::string& s, const std::string &start);
		bool EndWith(const std::string& s, const std::string& end);

		//center ���ַ�������
		//SurplusSpaceLeft�����Ƿ񽫶���Ŀո���������(begin)������������Ҳ�(end)(Ĭ��true)
		std::string center(const std::string& s,const bool SurplusSpaceLeft);

		//��дתСд��Сдת��д
		std::string SwapCase(const std::string& s);

		//��ʽ���ַ���
		//����string��vsnprintf
		std::string format(const char * fmt, ...);
	}

	namespace coder {
		//Unicode����ת��
		//���������
		//�ɹ�����0
		template<typename I,typename O>
		int Utf8ToUtf32(I, I, O, O);
		template<typename I, typename O>
		int Utf32ToUtf8(I, I, O, O);
	}

}
