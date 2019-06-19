#pragma once
#include <vector>
#include "oglObject.h"
#include "oglVertexObject.h"
#include "openGlContainer.h"
#include "Camera.h"
#include "Part.h"
#include "Floor.h"
#include "AGENV.h"

class Scene
{
private:

	GAENV env;

	std::vector<float> AGResults;

	std::vector<Part> parts;
	std::vector<Floor> floor;

	std::vector<oglObject> objects; 
	std::vector<oglVertexObject*> vertexObjects;

	bool breakStatus;
public:
	Scene();
	~Scene();

	void renderObjects(openGlContainer &container, Camera &camera);
	void updateObjects();
	void loadObjects(bool headless);
	void loadAGObjects(bool headless, GAENV env);
	bool breakCondition();
	std::vector<float> getFitness();
	float computeFitness(int i,bool hit);
public:
	void applyAG();
	void TestSingleObject(glm::vec3 F,float elasticity);

private:
	void initObjectsOpenGL();
};

