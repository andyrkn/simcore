#include "Floor.h"
#include "Logger.h"
#include "limits.h"
Floor::Floor(const char* path) : oglVertexObject(path, -1)
{
	state.inertiaTensor = 9999999.0f * glm::mat3(1.0f);
}

Floor::~Floor()
{}

void Floor::update()
{

}