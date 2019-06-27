#include "Floor.h"
#include "Logger.h"
#include "limits.h"
Floor::Floor(const char* path,int id) : oglVertexObject(path, id)
{
	state.inertiaTensor = 9999999.0f * glm::mat3(1.0f);
}

Floor::~Floor()
{}

void Floor::update()
{
	int i = 0;
	bool rotated = false;
	for (auto& rotation : v_rotationRules)
	{
		i++;
		if (deltaTime >= rotation.startTime && deltaTime <= rotation.endTime)
		{
			/*
			if (!state.activePivotalRotation)
			{
				if (i == 1)
					state.currentPivot = state.rotateByQuat(vertices[0], state.rotation);
				else
					state.currentPivot = state.rotateByQuat(vertices[3], state.rotation);
			}
			*/
			rotated = true;
			state.rotation = glm::rotate(state.rotation, glm::radians(rotation.degrees), rotation.axis);
			state.rotateAroundPivotWithQuat();
		}
	}
	if (!rotated)
		state.checkOffCenterRotation();

	if (id == -1)
	{
		state.position.y += 0.2;
	}
}