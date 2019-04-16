#include "ObjectState.h"
#include "Logger.h"

ObjectState::ObjectState()
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	momentum = glm::vec3(0.0f, 0.0f, 0.0f);
}

ObjectState::~ObjectState()
{

}

void ObjectState::init(glm::vec3 pos)
{
	this->position = pos;
}

void ObjectState::init(glm::vec3 pos, float mass, float elasticity)
{
	this->elasticity = elasticity;
	this->position = pos;
	this->mass = mass;
}

void ObjectState::evaluate(glm::vec3 force, float dt)
{
	glm::vec3 acceleration = force / mass;
	velocity = velocity + acceleration * dt;
	momentum = velocity / mass;
}

void ObjectState::recalculate(float dt)
{
	position = position + velocity * dt;
}

bool ObjectState::collide(ObjectState & state2)
{
	// Logger::log(position);
	// Logger::log(state2.position);
	float xdist = state2.position.x - position.x;
	float ydist = state2.position.y - position.y;
	float zdist = state2.position.z - position.z;
	float d = sqrt(xdist + ydist + zdist);
	// if(d>-1) Logger::log(d);


	if ((state2.position[1] < (position[1] + sizes[1] ) && state2.position[1] > (position[1] - sizes[1] ))
		|| position[1] < (state2.position[1] + state2.sizes[1] ) && position[1] > (state2.position[1] - state2.sizes[1] ))
	{
		if ((state2.position[2] < (position[2] + sizes[2] ) && state2.position[2] > (position[2] - sizes[2] ))
			|| position[2] < (state2.position[2] + state2.sizes[2] ) && position[2] > (state2.position[2] - state2.sizes[2] ))
		{
			if ((state2.position[0] < (position[0] + sizes[0] ) && state2.position[0] > (position[0] - sizes[0] ))
				|| position[0] < (state2.position[0] + state2.sizes[0] ) && position[0] > (state2.position[0] - state2.sizes[0] ))
			{
				return true;
			}
		}
	}
	/*
	if (position[1] < (state2.position[1] + state2.sizes[1] ) && position[1] > (state2.position[1] - state2.sizes[1] ))
	{
		if (position[2] < (state2.position[2] + state2.sizes[2] ) && position[2] > (state2.position[2] - state2.sizes[2] ))
		{
			if (position[0] < (state2.position[0] + state2.sizes[0] ) && position[0] > (state2.position[0] - state2.sizes[0] ))
			{
				return true;
			}
		}
	}
	*/
	return false;
}
