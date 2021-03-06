#pragma once
#include "OpenGlProxy.h"
#include "openGlContainer.h"
class Camera
{
public:

	int width;
	int height;

	glm::vec3 position;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float FOV = 45.0f;

	float speed = 3.0f;
	float mouseSpeed = 0.005f;

	openGlContainer *container;
public:
	Camera();
	~Camera();

	void setContainer(openGlContainer *container);
	void update();
	
};

