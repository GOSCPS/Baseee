#pragma once

// log.cpp日志源文件
//MIT License
//Copyright(c) 2020 chhdao
//

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>
#include <thread>
#include <sstream>
#include "log.hpp"

std::string baseee::log::logger::BuildOutFileName(const std::string &format) {
	time_t rwtime;
	time(&rwtime);
	struct tm *time = localtime(&rwtime);
	std::string out = format;
	while (true) {
		if (out.find("{year}") != out.npos) {
			out.replace(out.find("{year}"), 6, std::to_string(time->tm_year + 1900));
			continue;
		}

		else if (out.find("{month}") != out.npos) {
			out.replace(out.find("{month}"), 7, std::to_string(time->tm_mon + 1));
			continue;
		}

		else if (out.find("{day}") != out.npos) {
			out.replace(out.find("{day}"), 5, std::to_string(time->tm_mday));
			continue;
		}

		else if (out.find("{hour}") != out.npos) {
			out.replace(out.find("{hour}"), 6, std::to_string(time->tm_hour));
			continue;
		}

		else if (out.find("{min}") != out.npos) {
			out.replace(out.find("{min}"), 5, std::to_string(time->tm_min));
			continue;
		}

		else if (out.find("{sec}") != out.npos) {
			out.replace(out.find("{sec}"), 5, std::to_string(time->tm_sec));
			continue;
		}

		else if (out.find("{name}") != out.npos) {
			out.replace(out.find("{name}"), 6, name);
			continue;
		}

		else break;
	}
	return out;
}

std::string baseee::log::logger::BuildOutFormat(const int &level) {
	time_t rwtime;
	time(&rwtime);
	struct tm* time = localtime(&rwtime);
	std::string out = format;
	while (true) {
		if (out.find("{year}") != out.npos) {
			out.replace(out.find("{year}"), 6, std::to_string(time->tm_year + 1900));
			continue;
		}

		else if (out.find("{month}") != out.npos) {
			out.replace(out.find("{month}"), 7, std::to_string(time->tm_mon + 1));
			continue;
		}

		else if (out.find("{day}") != out.npos) {
			out.replace(out.find("{day}"), 5, std::to_string(time->tm_mday));
			continue;
		}

		else if (out.find("{hour}") != out.npos) {
			out.replace(out.find("{hour}"), 6, std::to_string(time->tm_hour));
			continue;
		}

		else if (out.find("{min}") != out.npos) {
			out.replace(out.find("{min}"), 5, std::to_string(time->tm_min));
			continue;
		}

		else if (out.find("{sec}") != out.npos) {
			out.replace(out.find("{sec}"), 5, std::to_string(time->tm_sec));
			continue;
		}

		else if (out.find("{name}") != out.npos) {
			out.replace(out.find("{name}"), 6, name);
			continue;
		}

		else if (out.find("{level}") != out.npos) {
			out.replace(out.find("{level}"), 7, GetLevelString(level));
			continue;
		}

		else if (out.find("{threadId}") != out.npos) {
			std::ostringstream oss;
			oss << std::this_thread::get_id();
			out.replace(out.find("{threadId}"), 10, oss.str());
			continue;
		}

		else break;
	}
	return out;
}

std::string baseee::log::logger::GetLevelString(const int& level) {
	switch (level)
	{
	case 0:
		return "Info";
		break;
	case 1:
		return "Important";
		break;
	case 2:
		return "Warning";
		break;
	case 3:
		return "Eroor";
		break;
	case 4:
		return "Fatal";
		break;
	default:
		return "OtherLevel:" + std::to_string(level);
		break;
	}
}

void baseee::log::logger::PrintLog(const int level,const std::string log) {
	mtx.lock();
	if (ofs.good()) ofs << BuildOutFormat(level) << log << std::endl;
	if (level >= lowest && os.good()) os << BuildOutFormat(level) << log << std::endl;
	mtx.unlock();
	return;
}

void baseee::log::logger::LogStream(const std::pair<int, std::string> log) {
	PrintLog(log.first,log.second);
	return;
}

