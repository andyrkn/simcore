#pragma once
#include"OpenGlProxy.h"
#include<vector>
#include"ObjectState.h"
#include <glm/gtc/quaternion.hpp>


class oglVertexObject
{
protected:
	//time ?
	double lastTime;
	float deltaTime;
public:
	//properties
	glm::mat4 TranslationMatrix;
	glm::quat RotationQuat;
	glm::mat4 ScaleMatrix;
	glm::mat4 ModelMatrix;
	bool gravInvul;
	ObjectState state;
	//space
	float width, height, depth;

	//gpu
	GLuint vertexbuffer;
	GLuint colorbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

public:
	virtual void update() = 0;
	void render();
protected:
	void load(const char* path);
	void init(const char* path);
	void updatePos();
	void logMatrix(glm::mat4 matrix);
};

