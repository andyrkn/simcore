#pragma once
#include<iostream>
#include<string>
class Logger
{
public:
	Logger();
	~Logger();
	void static log(const char* str);
	void static log(std::string str);
};

