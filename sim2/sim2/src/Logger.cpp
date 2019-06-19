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

}void Logger::log(std::string text, glm::vec3 v)
{
	std::cout << text << ' ';
	for (int i = 0; i < 3; i++)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << "\n";
}

void Logger::log(glm::mat4 m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) std::cout << m[i][j] << ' ';
		std::cout << "\n";
	}
}

void Logger::log(glm::quat q)
{
	std::cout << q.w << ' ' << q.x << ' ' << q.y << ' ' << q.z << "\n";
}

void Logger::log(std::vector<glm::vec3> v)
{
	for (auto& i : v)
	{
		Logger::log(i);
	}
}


Logger::~Logger()
{
}
