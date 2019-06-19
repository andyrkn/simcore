#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/vector_angle.hpp>

class ObjectState
{
public:
	//width,height,depth
	glm::quat rotation;
	glm::vec3 rotationOffSet;
	glm::quat singularRotationQuat;
	glm::quat startingRotation;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 angularVelocity;
	glm::vec3 momentum;
	glm::mat3 inertiaTensor;

	glm::vec3 direction;
	glm::vec3 currentPivot;

	float radius;
	float mass;
	float elasticity;
	bool linked;
	bool activePivotalRotation;
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
	void rotateAroundPivotWithQuat();

	glm::vec3 rotatedPosition();
	void checkOffCenterRotation();
	void applyTorque();
};