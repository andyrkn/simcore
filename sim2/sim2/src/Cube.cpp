#include "Cube.h"
#include "Logger.h"

Cube::Cube(const char* path)
{
	init(path);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
	ScaleMatrix = glm::mat4(1.0f);
	RotationMatrix = glm::mat4(1.0f);
	ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
}

Cube::~Cube()
{}

void Cube::update()
{
	double currentTime = glfwGetTime();
	deltaTime += float(currentTime - lastTime);
	float fps = 1 / float(currentTime - lastTime);
	static int spin = 1, type = 1;

	if (deltaTime > 0.016)
	{
		if (spin > 180) { spin = 0; type = type * -1; }

		TranslationMatrix = glm::translate(TranslationMatrix, glm::vec3(0.0f, 0.01f * type, 0.0f));

		ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;

		updatePos();
		std::cout << x << ' ' << y << ' ' << z << "\n";
		std::cout << fps << "\n";

		spin++;
		deltaTime = 0;
	}

	lastTime = currentTime;
}
