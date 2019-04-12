#include "Scene.h"
#include "Logger.h"

Scene::Scene()
{
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
	for (auto &obj : vertexObjects)
	{
		obj->update();
		if (!obj->gravInvul)
		{
			obj->state.evaluate(glm::vec3(0.0f, -obj->state.mass*9.8f, 0.0f), 0.0166666f);
			for (auto &obj2 : vertexObjects)
			{
				if (obj != obj2)
				{
					if (obj->state.collide(obj2->state))
					{
						obj->state.velocity.y = -obj->state.velocity.y * obj->state.elasticity;
					}
				}
			}
		}
	}
}

void Scene::loadObjects(bool headless)
{
	// objects.push_back(oglObject("objs/92-sci_fi_gun_obj/scifi_gun.obj","."));
	cube.push_back(Cube("objs/vertexObjects/cube.txt"));
	floor.push_back(Floor("objs/vertexObjects/floor.txt"));

	vertexObjects.push_back(&cube[0]);
	vertexObjects.push_back(&floor[0]);

	for (auto &obj : vertexObjects)
	{
		obj->load(obj->path.c_str());
		if (!headless)
		{
			obj->init(obj->path.c_str());
		}
	}
}

bool Scene::breakCondition()
{
	Logger::log(cube[0].state.position.x);
	return cube[0].state.position.x > 4 ? true : false;
}
