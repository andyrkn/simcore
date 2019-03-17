#pragma once
#include "OpenGlProxy.h"
class openGlContainer
{

public:
	int width, height;
	GLFWwindow* window;

	GLuint programID;
	GLuint MatrixID;
	GLuint VertexArrayID;
public:
	openGlContainer(int _w = 1024, int _h = 768);
	~openGlContainer();
private:
	void init();
	void loadShaders(const char* vertex_path, const char* fragment_path);
};

