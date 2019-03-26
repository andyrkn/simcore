#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class ObjectState
{
public:
	//width,height,depth
	glm::vec3 sizes;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 momentum;
	float mass;
	float elasticity;
public:
	ObjectState();
	~ObjectState();

	void init(glm::vec3 pos);
	void init(glm::vec3 pos, float mass, float elasticity = 0);
	void evaluate(glm::vec3 force,float dt);
	void recalculate(float dt);
	bool collide(ObjectState &state2);
};

