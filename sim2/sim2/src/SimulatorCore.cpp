#include "SimulatorCore.h"
#include "Logger.h"

SimulatorCore::SimulatorCore(bool headless)
{
	this->headless = headless;
	if (!headless)
	{
		container.init();
		camera.setContainer(&this->container);
	}
	initScene();
}

SimulatorCore::~SimulatorCore() {}

void SimulatorCore::runHead()
{
	while (glfwGetKey(container.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		if (scene.breakCondition()) break;
		render();
	}
	glfwTerminate();
}

void SimulatorCore::runHeadless()
{
	while (true)
	{
		if (scene.breakCondition()) break;
		update();
	}
}

void SimulatorCore::initScene()
{
	scene.loadObjects(headless);
}

void SimulatorCore::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(container.ProgramID);

	camera.update();
	update();
	scene.renderObjects(container, camera);

	glfwSwapBuffers(container.window);
	glfwPollEvents();
}

void SimulatorCore::update()
{
	scene.updateObjects();
}

void SimulatorCore::checkGlError()
{
	GLenum glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << gluErrorString(glError) << "\n";
	}
}

void SimulatorCore::start()
{
	if (headless)
	{
		runHeadless();
	}
	else
	{
		runHead();
	}
}
