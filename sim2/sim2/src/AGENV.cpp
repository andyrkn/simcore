#include "AGENV.h"
#include <iostream>


GAENV::GAENV()
{}


GAENV::GAENV(int popsize, std::vector<glm::vec3> forces, std::vector<float> elasticities)
{
	this->popsize = popsize;
	this->forces = forces;
	this->elasticities = elasticities;
}

GAENV::~GAENV()
{}

void GAENV::setPopulation(std::vector<glm::vec4> population)
{
	for(auto cromozome : population)
	{
		addIndividual(cromozome);
	}
}

void GAENV::addIndividual(glm::vec4 cromozome)
{
	forces.push_back(glm::vec3(cromozome.x, cromozome.y, cromozome.z));
	elasticities.push_back(cromozome.w / 10);
}

void GAENV::printPop()
{
	for (int i = 0; i < popsize; i++)
	{
		std::cout << forces[i].x << " " << forces[i].y << " " << forces[i].z << " " << elasticities[i] << "\n";
	}
}
