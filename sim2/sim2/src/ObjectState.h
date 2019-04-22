#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>

class ObjectState
{
public:
	//width,height,depth
	glm::quat rotation;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 momentum;

	float radius;
	float mass;
	float elasticity;
	bool linked;
public:
	ObjectState();
	void init(glm::vec3 pos);
	~ObjectState();

	void init(glm::vec3 pos, float mass, float elasticity = 0);
	void evaluate(glm::vec3 force, float dt);
	void recalculate(float dt);
	bool collide(ObjectState& state2, std::vector<glm::vec3> v1, std::vector<glm::vec3> v2);
	glm::vec3 pointsInWorldSpace(glm::vec3& v, glm::quat& q, glm::vec3& pos);
	glm::vec3 rotateByQuat(glm::vec3& v, glm::quat& q);
};