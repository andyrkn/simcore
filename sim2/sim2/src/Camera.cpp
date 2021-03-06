#include "Camera.h"



Camera::Camera()
{
	position = glm::vec3(-50, 20, 5);

	ProjectionMatrix = glm::perspective((float)glm::radians(360.0), 16.0f / 9.0f, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(position, position, glm::vec3(0, 1, 0));
}


Camera::~Camera()
{}

void Camera::setContainer(openGlContainer * container)
{
	this->container = container;
}

//camera modified from http://www.opengl-tutorial.org/download/
void Camera::update()
{
	int width = 1080;
	int height = 1920;

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(container->window, &xpos, &ypos);
	glfwSetCursorPos(container->window, height / 2, width / 2);

	horizontalAngle += mouseSpeed * float(height / 2 - xpos);
	verticalAngle += mouseSpeed * float(width / 2 - ypos);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(container->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(container->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(container->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(container->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= right * deltaTime * speed;
	}

	ProjectionMatrix = glm::perspective((float)glm::radians(FOV), 16.0f / 9.0f, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(position, position + direction, up);

	lastTime = currentTime;
}
