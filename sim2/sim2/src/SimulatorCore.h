#pragma once
#include "OpenGlProxy.h"
#include "Scene.h"
#include "Camera.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"

class SimulatorCore
{
private:
	bool headless;

public:
	Camera camera;
	Scene scene;
	openGlContainer container;

public:
	SimulatorCore(bool headless = false);
	~SimulatorCore();
	void start();

private:
	void runHead();
	void runHeadless();
	void initScene();
	void render();
	void update();
	void checkGlError();
};

