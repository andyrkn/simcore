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

void Logger::log(float d)
{
	std::cout << d << "\n";
}

void Logger::log(glm::vec3 v)
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << "\n";
}


Logger::~Logger()
{
}
