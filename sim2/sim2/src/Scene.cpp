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
			//obj->state.applyTorque();
			//if(!obj->state.linked)
				//obj->state.evaluate(glm::vec3(0.0f, -obj->state.mass * gravForce, 0.0f), DT);
			for (auto &obj2 : vertexObjects)
			{
				if (obj != obj2)
				{
					if (obj->state.collide(obj2->state, obj->vertices, obj2->vertices))
					{
						obj->state.velocity.y = 0;
						obj->state.position.y += obj->state.radius / 40;
						obj->state.linked = true;
					}
					else
					{
						obj->state.linked = false;
					}
				}
			}
			obj->coreObjectUpdate();
		}
	}
}	

void Scene::loadObjects(bool headless)
{
	parts.push_back(Part("objs/vertexObjects/cube.txt",1));
	parts.push_back(Part("objs/vertexObjects/simple triangle.txt", 2));
	// parts.push_back(Part("objs/vertexObjects/something.txt",2));
	// parts.push_back(Part("objs/vertexObjects/arrow.txt",3));
	// parts.push_back(Part("objs/vertexObjects/cube2.txt"));
	floor.push_back(Floor("objs/vertexObjects/floor.txt"));

	for (auto &part : parts) 
	{
		vertexObjects.push_back(&part);
	}

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
	// return parts[0].state.position.x > 4 ? true : false;
	return false;
}
