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
		if (!obj->gravInvul)
		{
			obj->state.evaluate(glm::vec3(0.0f, -obj->state.mass * gravForce, 0.0f), DT);
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
			obj->update();
		}
	}
}	

void Scene::loadObjects(bool headless)
{
	// objects.push_back(oglObject("objs/92-sci_fi_gun_obj/scifi_gun.obj","."));
	parts.push_back(Part("objs/vertexObjects/cube.txt"));
	parts.push_back(Part("objs/vertexObjects/cube2.txt"));
	floor.push_back(Floor("objs/vertexObjects/floor.txt"));

	vertexObjects.push_back(&parts[0]);
	vertexObjects.push_back(&parts[1]);
	vertexObjects.push_back(&floor[0]);

	for (auto &obj : vertexObjects)
	{
		if (!headless)
		{
			obj->initOpenGLProperties(obj->path.c_str());
		}
	}
}

bool Scene::breakCondition()
{
	Logger::log(parts[0].state.position.x);
	return parts[0].state.position.x > 4 ? true : false;
}
