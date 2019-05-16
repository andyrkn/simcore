#pragma once
#include "glm/glm.hpp"
class RotationRule
{
public:
	float startTime;
	float endTime;
	float degrees;
	glm::vec3 axis;
public:
	RotationRule();
	~RotationRule();
};

