#pragma once
#include "OpenGlProxy.h"
class openGlContainer
{

public:
	int width, height;
	GLFWwindow* window;

	GLuint ProgramID;
	GLuint MatrixID;
	GLuint VertexArrayID;
public:
	openGlContainer(int _w = 1920, int _h = 1080);
	~openGlContainer();
	void init();
private:
	void loadShaders(const char* vertex_path, const char* fragment_path);
};

 