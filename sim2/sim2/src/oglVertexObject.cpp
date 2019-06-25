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
	showDirection = false;
	loadObjectData(path);
}

void oglVertexObject::coreObjectUpdate()
{
	update();

	recalculations();
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

	if (showDirection)
	{
		// drawDirection();
	}
}

void oglVertexObject::loadObjectData(const char* path)
{
	glm::vec3 centroid(0, 0, 0), body(0, 0, 0);
	float rotationRules = 0;
	float radius = 0;
	float elasticity;
	std::ifstream f(path, std::ios::in);	
	std::string rotationRulesLine;
	std::getline(f, rotationRulesLine);
	std::istringstream in(rotationRulesLine);

	in >> rotationRules;

	for (int i = 0; i < rotationRules; i++)
	{
		RotationRule rule;
		std::string line;
		std::getline(f, line);
		std::istringstream in(line);
		in >> rule.startTime >> rule.endTime >> rule.degrees >> rule.axis.x >> rule.axis.y >> rule.axis.z;
		this->v_rotationRules.push_back(rule);
	}

	std::string bodyline;
	std::getline(f, bodyline);
	std::istringstream rin(bodyline);
	rin >> body.x >> body.y >> body.z >> elasticity;

	for (std::string line; std::getline(f, line);) //read stream line by line
	{
		std::istringstream in(line);

		std::string type;
		in >> type;                  //and read the first whitespace-separated token
		float x, y, z;
		in >> x >> y >> z;       //now read the whitespace-separated floats


		if (type == "v")
		{
			centroid.x += x;
			centroid.y += y;
			centroid.z += z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		else
		{
			colors.push_back(glm::vec3(x, y, z));
		}
	}

	f.close();

	centroid /= vertices.size();

	for (auto& vertice : vertices)
	{
		vertice = vertice - centroid;
		float d = sqrt(vertice.x * vertice.x + vertice.y * vertice.y + vertice.z * vertice.z);
		radius = std::fmax(radius, d);
	}

	frames = 0;
	deltaTime = 0;
	gravInvul = true; 
	state.radius = radius;
	state.init(body, radius * radius * radius, /*elasticity*/ elasticity);
	
	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.position);
	ScaleMatrix = glm::mat4(1.0f);
	state.rotation = glm::quat(1, 0, 0, 0);
	ModelMatrix = TranslationMatrix * glm::mat4_cast(state.rotation) * ScaleMatrix;
}

void oglVertexObject::initOpenGLProperties(const char * path)
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

	initOpenGLDirection();
}

void oglVertexObject::initOpenGLDirection()
{
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(0.1, state.radius, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, state.radius, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, state.radius, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, state.radius, 0.1));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(0.1, 0.0, state.radius));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, state.radius));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, 0.1, state.radius));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, state.radius));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(state.radius, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(state.radius, 0.1, 0.0));
	dir_vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(state.radius, 0.0, 0.0));
	dir_vertices.push_back(glm::vec3(state.radius, 0.0, 0.1));

	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(1, 0, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 1, 0));
	dir_colors.push_back(glm::vec3(0, 0, 1));
	dir_colors.push_back(glm::vec3(0, 0, 1));
	dir_colors.push_back(glm::vec3(0, 0, 1));
	dir_colors.push_back(glm::vec3(0, 0, 1));
	dir_colors.push_back(glm::vec3(0, 0, 1));
	dir_colors.push_back(glm::vec3(0, 0, 1));

	glGenBuffers(1, &dir_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dir_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, dir_vertices.size() * sizeof(glm::vec3), &dir_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &dir_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, dir_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, dir_colors.size() * sizeof(glm::vec3), &dir_colors[0], GL_STATIC_DRAW);
}

void oglVertexObject::recalculations()
{
	deltaTime += DT;
	state.recalculate(DT);

	TranslationMatrix = glm::translate(glm::mat4(1.0f), state.rotatedPosition());

	ModelMatrix =
		TranslationMatrix *
		glm::mat4_cast(state.rotation) *
		ScaleMatrix;
}

void oglVertexObject::drawDirection()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, dir_vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, dir_colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, dir_vertices.size()); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
