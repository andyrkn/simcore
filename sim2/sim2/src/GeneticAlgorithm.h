#pragma once
#include "AGENV.h"
#include <vector>
#include "Cromozome.h"
#include <glm/vec3.hpp>
#include "SimulatorCore.h"

class GeneticAlgorithm
{
	int popsize;
	std::vector<Cromozome> population;
	std::vector<std::pair<int, float>> fitness;
public:
	GeneticAlgorithm(int popsize = 100);
	~GeneticAlgorithm();
public:
	GAENV getEnv(std::vector<Cromozome>::iterator first, std::vector<Cromozome>::iterator last);
	void printPop();
	void start();
private:
	void initPopulation();
	void tournamentSelection();
	void computeFitness();
};

