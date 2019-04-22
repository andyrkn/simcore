#pragma once
#include "oglVertexObject.h"

class Part : public oglVertexObject
{
public:
	Part(const char* path, int id);
	~Part();

public:
	void update();
};

