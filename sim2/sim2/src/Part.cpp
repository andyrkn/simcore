#include "Part.h"
#include "Logger.h"

Part::Part(const char* path, int id) : oglVertexObject(path, id)
{
	gravInvul = false;
	showDirection = true;
	
}

Part::~Part()
{

}

void Part::update()
{
	int i = 0;
	
	for (auto& rotation : v_rotationRules)
	{
		i++;
		if (deltaTime >= rotation.startTime && deltaTime <= rotation.endTime)
		{
			if (id == 1)
			{
				if (!state.activePivotalRotation)
				{
					if (i > 1)
						state.currentPivot = state.rotateByQuat(vertices[3], state.startingRotation);
					//state.currentPivot = vertices[3];
					else
						state.currentPivot = vertices[3];
					// state.currentPivot = vertices[3];
				}
			}
			if (id == 2)
			{
			}
			// p = glm::vec3(0, 0, 0);
			
			state.singularRotationQuat = glm::rotate(state.singularRotationQuat, glm::radians(rotation.degrees), rotation.axis);
			state.rotation = glm::rotate(state.rotation, glm::radians(rotation.degrees), rotation.axis);
			state.rotateAroundPivotWithQuat();
		}
	}
	
	Logger::log("cp: ",state.currentPivot);
	Logger::log(state.rotation);
	// Logger::log("center", state.position);
}
