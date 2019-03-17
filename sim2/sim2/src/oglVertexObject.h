#pragma once
#include"OpenGlProxy.h"
#include<vector>
class oglVertexObject
{
protected:
	double lastTime;
	float deltaTime;
	unsigned int frames;
public:
	float width, height, depth;
	float x, y, z;

	glm::mat4 ModelMatrix;

	GLuint vertexbuffer;
	GLuint colorbuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

public:
	virtual void update();
	void render();
protected:
	void load(const char* path);
	void init(const char* path);
	void updatePos();
	void logModelMatrix();
};

