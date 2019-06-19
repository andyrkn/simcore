#include "SimulatorCore.h"
#include "Logger.h"

SimulatorCore::SimulatorCore(bool headless)
{
	initCore(headless);
	scene.loadObjects(headless);
}

SimulatorCore::SimulatorCore(GAENV env, bool headless)
{
	initCore(headless);
	scene.loadAGObjects(headless, env);
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
		if (scene.breakCondition()) { break; }
		else { update(); }
	}
}

void SimulatorCore::initCore(bool headless)
{
	this->headless = headless;
	if (!headless)
	{
		container.init();
		camera.setContainer(&this->container);
	}
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

std::vector<float> SimulatorCore::runAG()
{
	if (!headless)
	{
		while (glfwGetKey(container.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
		{
			if (scene.breakCondition()) break;
			scene.applyAG();
			render();
		}
		glfwTerminate();
	}
	else
	{
		while (true)
		{
			if (scene.breakCondition()) { break; }
			else { scene.applyAG(); update(); }
		}
	}

	return scene.getFitness();
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

void SimulatorCore::singleCromozomTest(glm::vec4 cromozom)
{
	while (glfwGetKey(container.window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		if (scene.breakCondition()) break;
		scene.TestSingleObject(glm::vec3(cromozom), cromozom.w);
		render();
	}
	glfwTerminate();
}
