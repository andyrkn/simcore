#include "Floor.h"
#include "Logger.h"

Floor::Floor(const char* path)
{
	init(path);
}

Floor::~Floor()
{}

void Floor::update()
{
	/*
	double currentTime = glfwGetTime();
	deltaTime += float(currentTime - lastTime);

	if (deltaTime > 0.16)
	{
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -0.01f, 0.0f));
		deltaTime = 0;
	}
	*/
}
