#pragma once
#include "oglVertexObject.h"

class Cube : public oglVertexObject
{
public:
	Cube(const char* path);
	~Cube();

public:
	void update();
};

