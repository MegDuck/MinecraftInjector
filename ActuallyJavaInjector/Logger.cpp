#include "Logger.h"

Logger::Logger() {
	if (!std::filesystem::exists("C:\\logs")) {
		std::filesystem::create_directory("C:\\logs");
	}
	file.open("C:\\logs\\log.txt", std::ios::app | std::ios::out);
}

void Logger::log(std::string str) {
	file << str << "\n";
}

void Logger::close() {
	file.close();
}