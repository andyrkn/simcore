#include "ObjectState.h"
#include "Logger.h"
#include "Colissions.h"

ObjectState::ObjectState()
{
	velocity = glm::vec3(0.0f);
	momentum = glm::vec3(0.0f);
	rotationOffSet = glm::vec3(0.0f);

	activePivotalRotation = false;
	currentPivot = glm::vec3(0.0f);
	singularRotationQuat = glm::quat(1, 0, 0, 0);

	linked = false;
}

ObjectState::~ObjectState()
{
	angularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
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
	this->inertiaTensor = (mass * radius * radius / 6) * glm::mat3(1.0f);
}

void ObjectState::evaluate(glm::vec3 force, float dt)
{
	glm::vec3 acceleration = force / mass;
	velocity = velocity + acceleration * dt;
	momentum = velocity * mass;
}

void ObjectState::recalculate(float dt)
{
	position = position + velocity * dt;

	glm::vec4 dir_v4 = glm::mat4_cast(rotation) * glm::vec4(radius, 0, 0, 1);
	direction = glm::normalize(glm::vec3(dir_v4.x, dir_v4.y, dir_v4.z));
}

void assign(float (&x)[3], glm::vec3 vec)
{
	x[0] = vec.x;
	x[1] = vec.y;
	x[2] = vec.z;
}
glm::vec3 f_vec3(float(&x)[3])
{
	return glm::vec3(x[0], x[1], x[2]);
}

bool ObjectState::collide(ObjectState& state2, std::vector<glm::vec3> v1, std::vector<glm::vec3> v2)
{
	std::vector<glm::vec3> responsable1, responsable2;

	glm::vec3 s1_position = this->rotatedPosition();
	glm::vec3 s2_position = state2.rotatedPosition();

	float dx = s1_position.x - s2_position.x;
	float dy = s1_position.y - s2_position.y;
	float dz = s1_position.z - s2_position.z;
	float d = sqrt(dx * dx + dy * dy + dz * dz);

	if (d < std::fmax(radius, state2.radius))
	{
		bool status = false;
		for (int i = 0; i < v1.size(); i += 3)
		{
			for (int j = 0; j < v2.size(); j += 3)
			{
				float p1[3], p2[3], p3[3], q1[3], q2[3], q3[3];

				assign(p1, pointsInWorldSpace(v1[i], rotation, s1_position));
				assign(p2, pointsInWorldSpace(v1[i + 1], rotation, s1_position));
				assign(p3, pointsInWorldSpace(v1[i + 2], rotation, s1_position));

				assign(q1, pointsInWorldSpace(v2[j], state2.rotation, s2_position));
				assign(q2, pointsInWorldSpace(v2[j + 1], state2.rotation, s2_position));
				assign(q3, pointsInWorldSpace(v2[j + 2], state2.rotation, s2_position));

				if (Colissions::tri_tri_overlap_test_3d(p1, p2, p3, q1, q2, q3) == 1)
				{
					glm::vec3 n = glm::triangleNormal(v2[j], v2[j + 1], v2[j + 2]);

					velocity *= elasticity;
					for (int k = 0; k < 3; k++) if (n[k] != 0) velocity[k] = -velocity[k];

					status = true;
					/*
					responsable1.push_back(f_vec3(p1));
					responsable1.push_back(f_vec3(p2));
					responsable1.push_back(f_vec3(p3));
					responsable2.push_back(f_vec3(q1));
					responsable2.push_back(f_vec3(q2));
					responsable2.push_back(f_vec3(q3));
					*/
					// Logger::log(glm::triangleNormal(v1[i], v1[i + 1], v1[i + 2]));
					// Logger::log(responsable1);
					// Logger::log(glm::triangleNormal(v2[j], v2[j+1], v2[j+2]));
					return status;
				}
			}
		}
		if (status)
		{
			// Logger::log(responsable1);
			// Logger::log(responsable2);
			return status;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

glm::vec3 ObjectState::pointsInWorldSpace(glm::vec3& v, glm::quat& q,glm::vec3& pos)
{
	glm::vec3 qu = rotateByQuat(v, q);
	return glm::vec3(qu.x + pos.x, qu.y + pos.y, qu.z + pos.z);
}

glm::vec3 ObjectState::rotateByQuat(glm::vec3& v, glm::quat& q)
{
	return q * v;
}

void ObjectState::rotateAroundPivotWithQuat()
{
	activePivotalRotation = true;
	
	glm::vec3 negp = -currentPivot;
	glm::vec3 res = rotation * negp;
	rotationOffSet = res + currentPivot;
}

glm::vec3 ObjectState::rotatedPosition()
{
	return position + rotationOffSet;
}

void ObjectState::checkOffCenterRotation()
{
	currentPivot = glm::vec3(0, 0, 0);
	position += rotationOffSet;
	rotationOffSet = glm::vec3(0.0f);
	activePivotalRotation = false;
}

void ObjectState::applyTorque()
{
	glm::vec3 gravangle(0, -1, 0);
	float res = glm::acos(glm::dot(direction, gravangle));

	// Logger::log(glm::degrees(res));
	// Logger::log(direction);
	// Logger::log(glm::degrees(glm::orientedAngle(direction, glm::vec3(0, -1, 0), glm::vec3(1, 0, 0))));
}
