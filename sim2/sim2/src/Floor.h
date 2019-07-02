#pragma once
#include "oglVertexObject.h"
class Floor : public oglVertexObject
{
public:
	bool mode;
	Floor(const char* path,int id);
	~Floor();
public:
	void update();
};

