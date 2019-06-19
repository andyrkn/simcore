#pragma once
#include<vector>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class GAENV
{
public:
	bool running;
	int popsize;
	std::vector<glm::vec3> forces;
	std::vector<float> elasticities;
public:
	GAENV();
	GAENV(int popsize, std::vector<glm::vec3> forces, std::vector<float> elasticities);
	~GAENV();

	void setPopulation(std::vector<glm::vec4> population);
	void addIndividual(glm::vec4 cromozome);
	void printPop();
};

