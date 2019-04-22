#include "Part.h"
#include "Logger.h"

Part::Part(const char* path, int id) : oglVertexObject(path, id)
{
	gravInvul = false;
}

Part::~Part()
{

}

void Part::update()
{
	static int frames = 0;
	if (frames < 1)
	{
		frames++;
	}

	if (id == 1)
	{

	}
	else if (id == 2)
	{
		// state.rotation = glm::rotate(state.rotation, glm::radians(1.0f), glm::vec3(1, 0, 0));
	}
	state.recalculate(DT);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(state.rotation) * ScaleMatrix;
}
