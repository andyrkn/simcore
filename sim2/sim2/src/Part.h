#pragma once
#include "oglVertexObject.h"

class Part : public oglVertexObject
{
public:
	Part(const char* path);
	~Part();

public:
	void update();
};

