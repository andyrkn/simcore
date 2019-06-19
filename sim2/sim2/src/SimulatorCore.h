#pragma once
#include "OpenGlProxy.h"
#include "Scene.h"
#include "Camera.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"
#include "AGENV.h"

class SimulatorCore
{
private:
	bool headless;

public:
	Camera camera;
	Scene scene;
	openGlContainer container;

public:
	SimulatorCore(GAENV env, bool headless = false);
	SimulatorCore(bool headless = false);
	~SimulatorCore();
	void start();
	void singleCromozomTest(glm::vec4 cromozom);
	std::vector<float> runAG();

private:
	void runHead();
	void runHeadless();
	void initCore(bool headless);
	void render();
	void update();
	void checkGlError();
};

