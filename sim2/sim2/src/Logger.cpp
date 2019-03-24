#include "Logger.h"

Logger::Logger()
{
}

void Logger::log(const char* str)
{
	std::cout << str << "\n";
}

void Logger::log(std::string str)
{
	std::cout << str << "\n";
}


Logger::~Logger()
{
}
