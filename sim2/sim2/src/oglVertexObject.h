#pragma once
#include"OpenGlProxy.h"
#include<vector>
#include"ObjectState.h"
#include <glm/gtc/quaternion.hpp>
#include <string>
#include "envrules.h"


class oglVertexObject
{
protected:
	//time ?
	double lastTime;
	float deltaTime;
public:
	std::string path;
	//properties
	glm::mat4 TranslationMatrix;
	glm::quat RotationQuat;
	glm::mat4 ScaleMatrix;
	glm::mat4 ModelMatrix;
	bool gravInvul;
	ObjectState state;

	//gpu
	GLuint vertexbuffer;
	GLuint colorbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

public:
	oglVertexObject(const char* path);
	virtual void update() = 0;
	void render();
	void loadObjectData(const char* path);
	void initOpenGLProperties(const char* path);
protected:
	void logMatrix(glm::mat4 matrix);
};

