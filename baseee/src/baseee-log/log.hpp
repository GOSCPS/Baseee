/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 这个文件来自 GOSCPS(https://github.com/GOSCPS)
 * 使用 GOSCPS 许可证
 * File:    log.hpp
 * Content: log Head File
 * Copyright (c) 2020 GOSCPS 保留所有权利.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <string_view>

namespace baseee {
	namespace log {

		class Flush {};
		
		static Flush LogFlush;

		enum class LogLevel : uint8_t
		{	
			Trace,
			Debug,
			Info,
			Error,
			Warn,
			Fatal
		};

		inline const std::string ToString(const LogLevel &v)
		{
			switch (v)
			{
			case LogLevel::Debug:   return "Debug";
			case LogLevel::Info:   return "Info";
			case LogLevel::Error: return "Error";
			case LogLevel::Fatal: return "Fatal";
			default: return "";
			}
		}

		class logger {
		public:
			logger& operator=(const logger&) = delete;
			logger(const logger&) = delete;
			logger() = delete;

			/// <summary>
			/// 初始化logger
			/// </summary>
			/// <param name="LogFormat">日志格式</param>
			/// <param name="OutFile">输出文件</param>
			/// <param name="os">输出流</param>
			logger(std::string_view &&LogFormat, std::string_view &&OutFile, std::ostream &os) : OutStream(os){
				this->LogFormat = LogFormat;
				OpenFile(std::forward<std::string_view&&>(OutFile));
				return;
			}

			~logger() {
				if (this->OutFile.is_open()) this->OutFile.close();
				return;
			}

			/// <summary>
			/// 设置最低Console输出等级
			/// </summary>
			/// <param name="level"></param>
			/// <returns></returns>
			void SetLowestLevelOutConsole(LogLevel level) noexcept {
				LowestLevelOutStream = level;
				return;
			}

			/// <summary>
			/// 设置最低文件输出等级
			/// </summary>
			/// <param name="log"></param>
			/// <returns></returns>
			void SetLowestLevelOutFile(LogLevel level) noexcept {
				LowestLevelOutFile = level;
				return;
			}

			/// <summary>
			/// 设置默认输出等级
			/// </summary>
			/// <param name="flush"></param>
			/// <returns></returns>
			void SetDefaultOutLevel(LogLevel level) noexcept {
				this->DefaultOutLevel = level;
				return;
			}

			/// <summary>
			/// 使用默认等级打印日志
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="log"></param>
			/// <returns></returns>
			void PrintLog(std::string_view&& log) noexcept;

			/// <summary>
			/// 打印日志
			/// </summary>
			void _PrintLog(LogLevel level, std::string_view&& log) noexcept;

			/// <summary>
			/// 使用默认等级输出日志
			/// </summary>
			logger &operator<<(std::string_view &&log) noexcept{
				(*BufferMutex.find(GetThreadId())).second.lock();
				(*LogBuffer.find(GetThreadId())).second.append(log);
				(*BufferMutex.find(GetThreadId())).second.unlock();
				return *this;
			}

			/// <summary>
			/// 刷新日志流
			/// </summary>
			logger& operator<<(const Flush& flush) {
				(*BufferMutex.find(GetThreadId())).second.lock();
				this->PrintLog((*LogBuffer.find(GetThreadId())).second);
				(*LogBuffer.find(GetThreadId())).second.clear();
				(*BufferMutex.find(GetThreadId())).second.unlock();
				return *this;
			}

			/// <summary>
			/// 使用默认等级输出日志
			/// </summary>
			template<typename T>
			logger &operator<<(T log) noexcept {
				std::ostringstream s;
				s << log;
				return operator<<(s.str());
			}


		private:
			//计数
			unsigned long long Counter = 1;

			//缓冲区
			std::map<unsigned long long,std::string> LogBuffer;

			//缓冲区锁
			std::map<unsigned long long, std::mutex> BufferMutex;

			//输出锁
			std::mutex Mutex;

			//等于高于这个等级则输出到OutStream
			LogLevel LowestLevelOutStream;
			std::ostream& OutStream;

			//等于高于这个等级则输出到OutFile
			LogLevel LowestLevelOutFile;
			std::fstream OutFile;

			//默认输出等级
			LogLevel DefaultOutLevel = LogLevel::Info;
			
			//日志格式
			std::string_view LogFormat;

			std::string GetFormat(
				const std::string_view& level,
				const std::string_view& format) noexcept;

			void OpenFile(std::string_view&& f);

			/// <summary>
			/// 获取线程id
			/// </summary>
			/// <returns>uint64_t</returns>
			unsigned long long GetThreadId() {
				std::stringstream s;
				s << std::this_thread::get_id();
				return std::stoull(s.str());
			}
		};

	}
}