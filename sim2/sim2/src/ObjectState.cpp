#include "ObjectState.h"


ObjectState::ObjectState()
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

ObjectState::~ObjectState()
{}

void ObjectState::init(glm::vec3 pos, float mass, float elasticity = 0)
{
	this->elasticity = elasticity;
	this->position = pos;
	this->mass = mass;
}

void ObjectState::evaluate(glm::vec3 force, float dt)
{
	glm::vec3 acceleration = force / mass;
	velocity = velocity + acceleration * dt;
	position = position + velocity * dt;
}
