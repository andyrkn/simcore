#include "Scene.h"
#include "Logger.h"

Scene::Scene()
{
	breakStatus = false;
}


Scene::~Scene()
{}

void Scene::renderObjects(openGlContainer &container, Camera &camera)
{
	for (auto &obj : vertexObjects)
	{
		glm::mat4 MVP = camera.ProjectionMatrix * camera.ViewMatrix * obj->ModelMatrix;
		glUniformMatrix4fv(container.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		obj->render();
	}
}

void Scene::updateObjects()
{
	for (int i = 0; i < vertexObjects.size(); i++)
	{
		auto& obj = vertexObjects[i];

		if (!obj->gravInvul)
		{
			if (!obj->state.linked)
			{
				obj->state.evaluate(glm::vec3(0.0f, -obj->state.mass * gravForce, 0.0f), DT);
			}

			for (int j = i + 1; j < vertexObjects.size(); j++)
			{
				auto& obj2 = vertexObjects[j];

				if (obj != obj2 && obj2->gravInvul) // obj2 gravinvul means we only colide with immovable objects
				{
					if (obj->state.collide(obj2->state, obj->vertices, obj2->vertices))
					{
						obj->state.position += obj->state.velocity * (DT*4);

						if (env.running) //  check if there's an active genetic environment
						{
							if (j != vertexObjects.size() - 1)
							{
								// breakC = true; 
								// Logger::log(obj->id);
								if (AGResults[i] == -1)
								{
									AGResults[i] = computeFitness(i, true);
								}
							}
						}
					}
					else
					{ 
						// obj->state.linked = false;
					}
				}
			}

			obj->coreObjectUpdate();
		}
	}
}

void Scene::loadObjects(bool headless)
{
	parts.push_back(Part("objs/vertexObjects/cube.txt", 1));
	floor.push_back(Floor("objs/vertexObjects/target.txt"));
	floor.push_back(Floor("objs/vertexObjects/floor.txt"));

	for (auto& part : parts)
	{
		vertexObjects.push_back(&part);
	}

	vertexObjects.push_back(&floor[0]);
	vertexObjects.push_back(&floor[1]);

	if (!headless)
	{
		initObjectsOpenGL();
	}
}

void Scene::loadAGObjects(bool headless, GAENV env)
{
	this->env = env;

	for (int i = 0; i < env.popsize; i++)
	{
		parts.push_back(Part("objs/vertexObjects/cube.txt", i));
		parts[i].state.elasticity = env.elasticities[i];
		AGResults.push_back(-1);
	}
	for (auto& part : parts)
	{
		vertexObjects.push_back(&part);
	}

	floor.push_back(Floor("objs/vertexObjects/target.txt"));
	floor.push_back(Floor("objs/vertexObjects/floor.txt"));
	vertexObjects.push_back(&floor[0]);
	vertexObjects.push_back(&floor[1]);

	if (!headless)
	{
		initObjectsOpenGL();
	}
}

bool Scene::breakCondition()
{
	if (vertexObjects[0]->deltaTime > 5.0f) breakStatus = true;
	return breakStatus;
}

std::vector<float> Scene::getFitness()
{
	for (int i = 0; i < env.popsize; i++)
	{
		if (AGResults[i] == -1)
		{
			AGResults[i] = computeFitness(i, false);
		}
	}
	return AGResults;
}

float Scene::computeFitness(int i, bool hit)
{
	glm::vec3 s2_position = vertexObjects[vertexObjects.size() - 2]->state.position;
	glm::vec3 s1_position = vertexObjects[i]->state.position;

	float dx = s1_position.x - s2_position.x;
	float dy = s1_position.y - s2_position.y;
	float dz = s1_position.z - s2_position.z;

	float d;
	if (!hit) d = sqrt(dx * dx + dy * dy + dz * dz) * vertexObjects[0]->deltaTime * vertexObjects[0]->deltaTime; // fitness = distance * time
	if (hit) d = vertexObjects[0]->deltaTime; // if he hit the target, distance is considered 0 (for now)

	// Logger::log(vertexObjects[i]->state.position);
	// Logger::log(d);
	return d;
}

void Scene::applyAG()
{
	if (vertexObjects[0]->deltaTime < 0.50f)
	{
		for (int i = 0; i < env.popsize; i++)
		{
			vertexObjects[i]->state.evaluate(env.forces[i], DT);
		}
	}
}

void Scene::TestSingleObject(glm::vec3 F, float elasticity)
{
	if (vertexObjects[0]->deltaTime < 0.50f)
	{
		vertexObjects[0]->state.evaluate(F, DT);
		vertexObjects[0]->state.elasticity = elasticity;
	}
}

void Scene::initObjectsOpenGL()
{
	for (auto& obj : vertexObjects)
	{
		obj->initOpenGLProperties(obj->path.c_str());
	}
}
