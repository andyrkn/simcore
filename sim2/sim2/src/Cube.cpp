#include "Cube.h"
#include "Logger.h"

Cube::Cube(const char* path)
{
	init(path);
	gravInvul = false;
	state.init(glm::vec3(0.0f, 3.0f, 0.0f), this->state.sizes[0]*this->state.sizes[1] *this->state.sizes[2], 0.7f);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ScaleMatrix = glm::mat4(1.0f);
	RotationQuat = glm::quat(1, 0, 0, 0);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(RotationQuat) * ScaleMatrix;
}

Cube::~Cube()
{}

void Cube::update()
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
		state.evaluate(glm::vec3(1, 10, 0), 0.0166666f);
		//logMatrix(TranslationMatrix);
	}
	state.recalculate(0.0166666f);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(RotationQuat) * ScaleMatrix;
	updatePos();

	//std::cout << x << ' ' << y << ' ' << z << "\n";
	//std::cout << fps << "\n";


	//---------------------------------------------------
	deltaTime = 0;
	lastTime = currentTime;
}
