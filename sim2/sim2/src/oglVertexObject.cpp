#include "oglVertexObject.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Logger.h"


void oglVertexObject::render()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void oglVertexObject::load(const char* path)
{
	float max = 0, mix = 0, may = 0, miy = 0, maz = 0, miz = 0;
	std::ifstream f(path, std::ios::in);
	for (std::string line; std::getline(f, line);) //read stream line by line
	{
		std::istringstream in(line);

		std::string type;
		in >> type;                  //and read the first whitespace-separated token
		float x, y, z;
		in >> x >> y >> z;       //now read the whitespace-separated floats

		if (type == "v")
		{
			vertices.push_back(glm::vec3(x, y, z));
			max = std::fmaxf(x, max);
			mix = std::fminf(x, mix);
			may = std::fmaxf(y, may);
			miy = std::fminf(y, miy);
			maz = std::fmaxf(z, maz);
			miz = std::fminf(z, miz);
		}
		else
		{
			colors.push_back(glm::vec3(x, y, z));
		}
	}
	state.sizes[0] = -mix + max;
	state.sizes[1] = -miy + may;
	state.sizes[2] = -miz + maz;
}

void oglVertexObject::init(const char * path)
{
	lastTime = glfwGetTime();
	deltaTime = 0;
	gravInvul = true;

	load(path);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
}

void oglVertexObject::updatePos()
{
	// x = ModelMatrix[3][0];
	// y = ModelMatrix[3][1];
	// z = ModelMatrix[3][2];
}

void oglVertexObject::logMatrix(glm::mat4 matrix)
{

	for (int i = 0; i < 4; i++)
		std::cout << matrix[i][0] << ' '\
		<< matrix[i][1] << ' '\
		<< matrix[i][2] << ' '\
		<< matrix[i][3] << ' ' << "\n";

	std::cout << "\n-------------------------------------\n";
}
