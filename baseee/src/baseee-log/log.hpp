#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <mutex>
// log.hpp��־����
//MIT License
//Copyright(c) 2020 chhdao
//


namespace baseee {
	namespace log {

		class logger {
		public:
			logger& operator=(const logger&) = delete;
			logger() = delete;
			logger(std::string ProgramName,std::string LogFormat, int LowestOutLevel, std::ostream& OutStream, std::string OutFileFormat) :
				format(LogFormat), lowest(LowestOutLevel), os(OutStream),name(ProgramName){
				if(!OutFileFormat.empty())ofs = std::ofstream();
				ofs.open(BuildOutFileName(OutFileFormat), std::ios::out | std::ios::ate);
				return;
			}

			logger &operator<<(std::pair<int, std::string> log) {
				(this->LogStream)(log);
				return *this;
			}


			~logger() = default;

			//��ӡ��־
			void PrintLog(const int level,const std::string log);
			void LogStream(const std::pair<int,std::string> log);

			//��־��
			const int Log_Info = 0;
			const int Log_Important = 0;
			const int Log_Warning = 0;
			const int Log_fatal = 0;

			//��־�ȼ�
			const int Level_Info = 0;
			const int Level_Important = 1;
			const int Level_Warning = 2;
			const int Level_Error = 3;
			const int Level_Fatal = 4;
			
		private:
			const std::string name;
			const std::string format;
			const int lowest;	//���Ҫ��ӡ����־��������ȼ����������os
			std::ostream& os;
			std::ofstream ofs;

			std::mutex mtx;


			std::string BuildOutFormat(const int& level);//���������ʽ
			std::string BuildOutFileName(const std::string& format);//�����ļ�����
			std::string GetLevelString(const int& level);//���ݵȼ�������Ӧ�ַ���
		};

	}
}