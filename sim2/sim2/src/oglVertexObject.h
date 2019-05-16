#pragma once
#include"OpenGlProxy.h"
#include<vector>
#include"ObjectState.h"
#include <glm/gtc/quaternion.hpp>
#include <string>
#include "RotationRule.h"
#include "envrules.h"


class oglVertexObject
{
protected:
	float deltaTime;
	int id;
	int frames;
public:
	std::string path;
	//properties
	glm::mat4 TranslationMatrix;
	glm::mat4 ScaleMatrix;
	glm::mat4 ModelMatrix;
	bool gravInvul;
	bool showDirection;
	ObjectState state;

	//gpu
	GLuint vertexbuffer;
	GLuint colorbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

	//direction gpu
	GLuint dir_vertexbuffer;
	GLuint dir_colorbuffer;
	std::vector<glm::vec3> dir_vertices;
	std::vector<glm::vec3> dir_colors;

	//behvaiour
	std::vector<RotationRule> rotationRules;

public:
	oglVertexObject(const char* path,int id);
	void coreObjectUpdate();
	virtual void update() = 0;
	void render();
	void loadObjectData(const char* path);
	void initOpenGLProperties(const char* path);
	void initOpenGLDirection();
protected:
	void logMatrix(glm::mat4 matrix);
	void recalculations();
	void drawDirection();
};

