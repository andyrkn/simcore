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
	for (auto& rotation : rotationRules)
	{
		i++;
		if (deltaTime >= rotation.startTime && deltaTime <= rotation.endTime)
		{
			glm::vec3 p;
			if (id == 1)
				state.currentPivot = vertices[i*3];
				// p = glm::vec3(0, 0, 0);	
			if (id == 2)
				p = vertices[3];

			p = glm::vec3(0, 0, 0);

			state.rotation = glm::rotate(state.rotation, glm::radians(rotation.degrees), rotation.axis);
			//state.rotateAroundPivotMatrixCalc(p);
		}
	}
}
