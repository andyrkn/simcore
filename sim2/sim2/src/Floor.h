#pragma once
#include "oglVertexObject.h"
class Floor : public oglVertexObject
{
public:
	Floor(const char* path,int id);
	~Floor();
public:
	void update();
};

