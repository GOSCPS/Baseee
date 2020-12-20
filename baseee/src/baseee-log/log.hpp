/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * ����ļ����� GOSCPS(https://github.com/GOSCPS)
 * ʹ�� GOSCPS ���֤
 * File:    log.hpp
 * Content: log Head File
 * Copyright (c) 2020 GOSCPS ��������Ȩ��.
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
			/// ��ʼ��logger
			/// </summary>
			/// <param name="LogFormat">��־��ʽ</param>
			/// <param name="OutFile">����ļ�</param>
			/// <param name="os">�����</param>
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
			/// �������Console����ȼ�
			/// </summary>
			/// <param name="level"></param>
			/// <returns></returns>
			void SetLowestLevelOutConsole(LogLevel level) noexcept {
				LowestLevelOutStream = level;
				return;
			}

			/// <summary>
			/// ��������ļ�����ȼ�
			/// </summary>
			/// <param name="log"></param>
			/// <returns></returns>
			void SetLowestLevelOutFile(LogLevel level) noexcept {
				LowestLevelOutFile = level;
				return;
			}

			/// <summary>
			/// ����Ĭ������ȼ�
			/// </summary>
			/// <param name="flush"></param>
			/// <returns></returns>
			void SetDefaultOutLevel(LogLevel level) noexcept {
				this->DefaultOutLevel = level;
				return;
			}

			/// <summary>
			/// ʹ��Ĭ�ϵȼ���ӡ��־
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="log"></param>
			/// <returns></returns>
			void PrintLog(std::string_view&& log) noexcept;

			/// <summary>
			/// ��ӡ��־
			/// </summary>
			void _PrintLog(LogLevel level, std::string_view&& log) noexcept;

			/// <summary>
			/// ʹ��Ĭ�ϵȼ������־
			/// </summary>
			logger &operator<<(std::string_view &&log) noexcept{
				(*BufferMutex.find(GetThreadId())).second.lock();
				(*LogBuffer.find(GetThreadId())).second.append(log);
				(*BufferMutex.find(GetThreadId())).second.unlock();
				return *this;
			}

			/// <summary>
			/// ˢ����־��
			/// </summary>
			logger& operator<<(const Flush& flush) {
				(*BufferMutex.find(GetThreadId())).second.lock();
				this->PrintLog((*LogBuffer.find(GetThreadId())).second);
				(*LogBuffer.find(GetThreadId())).second.clear();
				(*BufferMutex.find(GetThreadId())).second.unlock();
				return *this;
			}

			/// <summary>
			/// ʹ��Ĭ�ϵȼ������־
			/// </summary>
			template<typename T>
			logger &operator<<(T log) noexcept {
				std::ostringstream s;
				s << log;
				return operator<<(s.str());
			}


		private:
			//����
			unsigned long long Counter = 1;

			//������
			std::map<unsigned long long,std::string> LogBuffer;

			//��������
			std::map<unsigned long long, std::mutex> BufferMutex;

			//�����
			std::mutex Mutex;

			//���ڸ�������ȼ��������OutStream
			LogLevel LowestLevelOutStream;
			std::ostream& OutStream;

			//���ڸ�������ȼ��������OutFile
			LogLevel LowestLevelOutFile;
			std::fstream OutFile;

			//Ĭ������ȼ�
			LogLevel DefaultOutLevel = LogLevel::Info;
			
			//��־��ʽ
			std::string_view LogFormat;

			std::string GetFormat(
				const std::string_view& level,
				const std::string_view& format) noexcept;

			void OpenFile(std::string_view&& f);

			/// <summary>
			/// ��ȡ�߳�id
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