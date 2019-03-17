#pragma once
#include "oglVertexObject.h"

class Cube : public oglVertexObject
{
public:
	glm::mat4 TranslationMatrix;
	glm::mat4 RotationMatrix;
	glm::mat4 ScaleMatrix;
public:
	Cube(const char* path);
	~Cube();

public:
	void update();
};

