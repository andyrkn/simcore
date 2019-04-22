#include "ObjectState.h"
#include "Logger.h"
#include "Colissions.h"

ObjectState::ObjectState()
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	momentum = glm::vec3(0.0f, 0.0f, 0.0f);
	linked = false;
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

void assign(float (&x)[3],glm::vec3 vec)
{
	x[0] = vec.x;
	x[1] = vec.y;
	x[2] = vec.z;
}

bool ObjectState::collide(ObjectState& state2, std::vector<glm::vec3> v1, std::vector<glm::vec3> v2)
{
	float dx = position.x - state2.position.x;
	float dy = position.y - state2.position.y;
	float dz = position.z - state2.position.z;
	float d = sqrt(dx * dx + dy * dy + dz * dz);

	if (d < std::fmax(radius, state2.radius))
	{
		bool status = false;
		for (int i = 0; i < v1.size(); i+=3)
		{
			if (!status)
			{
				for (int j = i; j < v2.size(); j += 3)
				{
					float p1[3], p2[3], p3[3], q1[3], q2[3], q3[3];

					assign(p1, pointsInWorldSpace(v1[i], rotation, position));
					assign(p2, pointsInWorldSpace(v1[i + 1], rotation, position));
					assign(p3, pointsInWorldSpace(v1[i + 2], rotation, position));

					assign(q1, pointsInWorldSpace(v2[j], state2.rotation, state2.position));
					assign(q2, pointsInWorldSpace(v2[j + 1], state2.rotation, state2.position));
					assign(q3, pointsInWorldSpace(v2[j + 2], state2.rotation, state2.position));

					if (Colissions::tri_tri_overlap_test_3d(p1, p2, p3, q1, q2, q3) == 1)
					{
						status = true; break;
					}
				}
			}
		}
		return status;
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
	glm::quat old = q * glm::quat(0, v.x, v.y, v.z) * glm::conjugate(q);
	return glm::vec3(old.x, old.y, old.z);
}
