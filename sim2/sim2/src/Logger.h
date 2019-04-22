#pragma once
#include<iostream>
#include<string>
#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Logger
{
public:
	Logger();
	~Logger();
	void static log(const char* str);
	void static log(std::string str);
	void static log(float d);
	void static log(glm::vec3 v);
	void static log(glm::mat4 m);
	void static log(glm::quat q);
};

