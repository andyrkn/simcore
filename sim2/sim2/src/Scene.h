#pragma once
#include <vector>
#include "oglObject.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"
#include "Camera.h"

#include "Cube.h"
#include "Floor.h"

class Scene
{
private:
	std::vector<Cube> cube;
	std::vector<Floor> floor;
private:
	std::vector<oglObject> objects;
	std::vector<oglVertexObject*> vertexObjects;

public:
	Scene();
	~Scene();

	void renderObjects(openGlContainer &container, Camera &camera);
	void loadObjects();
};

