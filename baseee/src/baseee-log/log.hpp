/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * THIS FILE IS FROM Chhdao(sudo.free@qq.com)
 * IS LICENSED UNDER MIT
 * File:     log.hpp
 * Content:  baseee log module head file
 * Copyright (c) 2020 Chhdao All rights reserved.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <mutex>
#include <string>
#include <sstream>
#include <string_view>

namespace baseee {
	namespace log {

		enum class LogLevel : uint8_t
		{
			Level_Debug = 0,
			Level_Info = 1,
			Level_News = 2,
			Level_Note,
			Level_Warning,
			Level_Error,
			Level_Fatal
		};

		inline const std::string ToString(const LogLevel &v)
		{
			switch (v)
			{
			case LogLevel::Level_Debug:   return "Debug";
			case LogLevel::Level_Info:   return "Info";
			case LogLevel::Level_News: return "News";
			case LogLevel::Level_Note: return "Note";
			case LogLevel::Level_Warning: return "Warning";
			case LogLevel::Level_Error: return "Error";
			case LogLevel::Level_Fatal: return "Fatal";
				default: return "";
			}
		}

		class logger {
		public:
			logger& operator=(const logger&) = delete;
			logger(const logger&) = delete;
			logger() = delete;

			logger(std::string_view &&LogFormat, std::string_view &&OutFile, std::ostream &os) : OutStream(os){
				this->LogFormat = LogFormat;
				OpenFile(std::forward<std::string_view&&>(OutFile));
				return;
			}

			~logger() {
				if (this->OutFile.is_open()) this->OutFile.close();
				return;
			}

			void SetLowestLevelOutConsole(LogLevel level) noexcept {
				LowestLevelOutStream = level;
				return;
			}

			void SetLowestLevelOutFile(LogLevel level) noexcept {
				LowestLevelOutFile = level;
				return;
			}

			void SetDefaultOutLevel(LogLevel level) noexcept {
				this->DefaultOutLevel = level;
				return;
			}

			void PrintLog(std::string_view&& log) noexcept;
			void _PrintLog(LogLevel level, std::string_view&& log) noexcept;

			logger &operator<<(std::string_view &&log) noexcept{
				PrintLog(std::forward<std::string_view&&>(log));
				return *this;
			}

			template<typename T>
			logger &operator<<(T log) noexcept {
				std::ostringstream s;
				s << log;
				PrintLog(s.str());
				return *this;
			}


		private:
			//等于高于这个等级则输出到OutStream
			LogLevel LowestLevelOutStream;
			std::ostream& OutStream;

			//等于高于这个等级则输出到OutFile
			LogLevel LowestLevelOutFile;
			std::fstream OutFile;

			//默认输出等级
			LogLevel DefaultOutLevel = LogLevel::Level_Info;
			
			//日志格式
			std::string_view LogFormat;

			std::string GetFormat(
				const std::string_view& level,
				const std::string_view& format) noexcept;

			void OpenFile(std::string_view&& f);
		};

	}
}