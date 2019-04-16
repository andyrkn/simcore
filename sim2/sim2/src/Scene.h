#pragma once
#include <vector>
#include "oglObject.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"
#include "Camera.h"
#include "Part.h"
#include "Floor.h"

class Scene
{
private:
	std::vector<Part> parts;
	std::vector<Floor> floor;

	std::vector<oglObject> objects; 
	std::vector<oglVertexObject*> vertexObjects;

public:
	Scene();
	~Scene();

	void renderObjects(openGlContainer &container, Camera &camera);
	void updateObjects();
	void loadObjects(bool headless);
	bool breakCondition();
};

