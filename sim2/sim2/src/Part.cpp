#include "Part.h"
#include "Logger.h"

Part::Part(const char* path) : oglVertexObject(path)
{
	gravInvul = false;
}

Part::~Part()
{

}

void Part::update()
{
	// static float error = 0;
	double currentTime = glfwGetTime();
	deltaTime += float(currentTime - lastTime);
	// Logger::log(std::to_string(deltaTime));
	// error += abs(0.0166666 - deltaTime);
	// Logger::log(std::to_string(error));
	//---------------------------------------------------
	   //RotationQuat = glm::rotate(RotationQuat, glm::radians(1.0f), glm::vec3(1, 0, 0));
	//logMatrix(glm::mat4_cast(RotationQuat));
	
	static int frames = 0;
	if (frames++ < 120)
	{	
		state.evaluate(glm::vec3(1, 0, 0), DT);
		// logMatrix(TranslationMatrix);
	}
	state.recalculate(DT);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(RotationQuat) * ScaleMatrix;

	//std::cout << x << ' ' << y << ' ' << z << "\n";
	//std::cout << fps << "\n";


	//---------------------------------------------------
	deltaTime = 0;
	lastTime = currentTime;
}
