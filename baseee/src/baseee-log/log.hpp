#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <mutex>
// log.hpp日志声明
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

			//打印日志
			void PrintLog(const int level,const std::string log);
			void LogStream(const std::pair<int,std::string> log);

			//日志流
			const int Log_Info = 0;
			const int Log_Important = 0;
			const int Log_Warning = 0;
			const int Log_fatal = 0;

			//日志等级
			const int Level_Info = 0;
			const int Level_Important = 1;
			const int Level_Warning = 2;
			const int Level_Error = 3;
			const int Level_Fatal = 4;
			
		private:
			const std::string name;
			const std::string format;
			const int lowest;	//如果要打印的日志高于这个等级，则输出到os
			std::ostream& os;
			std::ofstream ofs;

			std::mutex mtx;


			std::string BuildOutFormat(const int& level);//构建输出格式
			std::string BuildOutFileName(const std::string& format);//构建文件名称
			std::string GetLevelString(const int& level);//根据等级构建对应字符串
		};

	}
}