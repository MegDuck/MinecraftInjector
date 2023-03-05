#pragma once
#include <cstdio>
#include <fstream>
#include <filesystem>

class Logger
{
public:
	Logger();
	void log(std::string str);
	void close();

private:
	std::ofstream file;
};

