#include "oglVertexObject.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Logger.h"


oglVertexObject::oglVertexObject(const char *path, int id)
{
	this->id = id;
	this->path = path;
	loadObjectData(path);
}

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

void oglVertexObject::loadObjectData(const char* path)
{
	float radius = 0;
	float bodyx, bodyy, bodyz, elasticity;
	std::ifstream f(path, std::ios::in);	
	std::string firstline;
	std::getline(f, firstline);
	std::istringstream in(firstline);
	in >> bodyx >> bodyy >> bodyz >> elasticity;

	for (std::string line; std::getline(f, line);) //read stream line by line
	{
		std::istringstream in(line);

		std::string type;
		in >> type;                  //and read the first whitespace-separated token
		float x, y, z;
		in >> x >> y >> z;       //now read the whitespace-separated floats


		if (type == "v")
		{
			float d = sqrt(x * x + y * y + z * z);
			radius = std::fmax(radius, d);

			vertices.push_back(glm::vec3(x, y, z));
		}
		else
		{
			colors.push_back(glm::vec3(x, y, z));
		}
	}

	deltaTime = 0;

	gravInvul = true; 

	state.radius = radius;
	state.init(glm::vec3(bodyx, bodyy, bodyz), radius * radius * radius, /*elasticity*/ elasticity);
	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ScaleMatrix = glm::mat4(1.0f);
	state.rotation = glm::quat(1, 0, 0, 0);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(state.rotation) * ScaleMatrix;
}

void oglVertexObject::initOpenGLProperties(const char * path)
{
	lastTime = glfwGetTime();

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
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
