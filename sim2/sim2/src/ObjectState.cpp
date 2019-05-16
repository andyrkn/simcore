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

	glm::vec4 dir_v4 = glm::mat4_cast(rotation) * glm::vec4(radius, 0, 0, 1);

	direction = glm::normalize(glm::vec3(dir_v4.x, dir_v4.y, dir_v4.z));
}

void assign(float (&x)[3],glm::vec3 vec)
{
	x[0] = vec.x;
	x[1] = vec.y;
	x[2] = vec.z;
}

bool ObjectState::collide(ObjectState& state2, std::vector<glm::vec3> v1, std::vector<glm::vec3> v2)
{
	glm::vec3 s1_position = this->rotatedPosition();
	glm::vec3 s2_position = state2.rotatedPosition();

	float dx = s1_position.x - s2_position.x;
	float dy = s1_position.y - s2_position.y;
	float dz = s1_position.z - s2_position.z;
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

					assign(p1, pointsInWorldSpace(v1[i], rotation, s1_position));
					assign(p2, pointsInWorldSpace(v1[i + 1], rotation, s1_position));
					assign(p3, pointsInWorldSpace(v1[i + 2], rotation, s1_position));

					assign(q1, pointsInWorldSpace(v2[j], state2.rotation, s2_position));
					assign(q2, pointsInWorldSpace(v2[j + 1], state2.rotation, s2_position));
					assign(q3, pointsInWorldSpace(v2[j + 2], state2.rotation, s2_position));

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

glm::vec3 ObjectState::rotateByQuatAroundPivot(glm::vec3& v, glm::quat& q, glm::vec3 pivot)
{
	glm::vec3 point = v - pivot;
	return rotateByQuat(point, q);
}

void ObjectState::rotateAroundPivotMatrixCalc(glm::vec3& pivot)
{
	activePivotalRotation = true;
	/*
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pivot);
	glm::mat4 resultMatrix = translationMatrix * glm::mat4_cast(q) * glm::inverse(translationMatrix);

	rotationOffSet = glm::vec3(resultMatrix[3][0], resultMatrix[3][1], resultMatrix[3][2]);
	rotationOffSet -= pivot;
	*/

	// glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -pivot);
	glm::mat4 resultMatrix = translationMatrix * glm::mat4_cast(rotation) * glm::inverse(translationMatrix);
	translationMatrix = glm::translate(resultMatrix, pivot);
	
	rotationOffSet = glm::vec3(translationMatrix[3][0], translationMatrix[3][1], translationMatrix[3][2]);
	
	// rotation = glm::quat(resultMatrix);
	// Logger::log(rotationOffSet);
}
   
glm::vec3 ObjectState::rotatedPosition()
{
	return position + rotationOffSet;
}

void ObjectState::stopOffCenterRotation()
{
	position += rotationOffSet;
	rotationOffSet = glm::vec3(0.0f);
}

void ObjectState::checkOffCenterRotation()
{
	if (!activePivotalRotation)
	{
		currentPivot = glm::vec3(0, 0, 0);
		stopOffCenterRotation();
	}
	else
	{
		activePivotalRotation = false;
	}
}

void ObjectState::applyTorque()
{
	glm::vec3 gravangle(0, -1, 0);
	float res = glm::acos(glm::dot(direction, gravangle));

	// Logger::log(glm::degrees(res));
	// Logger::log(direction);

	Logger::log(glm::degrees(glm::orientedAngle(direction, glm::vec3(0, -1, 0), glm::vec3(1, 0, 0))));
}

