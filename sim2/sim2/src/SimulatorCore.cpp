#include "SimulatorCore.h"
#include "Logger.h"

SimulatorCore::SimulatorCore() : camera(&container)
{
	initScene();
}

SimulatorCore::~SimulatorCore() {}

void SimulatorCore::initScene()
{
	scene.loadObjects();
}

void SimulatorCore::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(container.programID);

	camera.update();
	scene.renderObjects(container,camera);

	glfwSwapBuffers(container.window);
	glfwPollEvents();
}

void SimulatorCore::checkGlError()
{
	GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << gluErrorString(glError) << "\n";
	}
}

void SimulatorCore::run()
{
	while (glfwGetKey(container.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		render();
	}
	glfwTerminate();
}
