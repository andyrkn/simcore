#pragma once
#include "oglVertexObject.h"
class Floor : public oglVertexObject
{
public:
	Floor(const char* path);
	~Floor();
public:
	void update();
	void selfInit();
};

