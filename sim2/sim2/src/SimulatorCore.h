#pragma once
#include "OpenGlProxy.h"
#include "Scene.h"
#include "Camera.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"

class SimulatorCore
{
public:
	Camera camera;
	Scene scene;
	openGlContainer container;

public:
	SimulatorCore();
	~SimulatorCore();
	void run();

private:
	void initScene();
	void render();
	void checkGlError();
};

