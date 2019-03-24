#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class ObjectState
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	float mass;
	float elasticity;
public:
	ObjectState();
	~ObjectState();


	void init(glm::vec3 pos, float mass, float elasticity = 0);
	void evaluate(glm::vec3 force,float dt);
};

