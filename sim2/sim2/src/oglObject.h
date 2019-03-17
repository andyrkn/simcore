#pragma once
#include <vector>
#include "OpenGlProxy.h"

class oglObject
{
private:
	double lastTime;
	float deltaTime;
	unsigned int frames;
public:
	glm::mat4 ModelMatrix;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint texture;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
public:
	oglObject(const char* objPath,const char* texturePath);
	~oglObject();

	void loadOBJ(const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

	void render();
	void update();
};

