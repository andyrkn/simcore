#include "src/SimulatorCore.h"
#include "src/GeneticAlgorithm.h"

#include<iostream>
#include<thread>

void noAG()
{
	SimulatorCore simcore(false);
	simcore.start();
	// simcore.singleCromozomTest(glm::vec4(20, 35, -30 , 0.7));
}

void AGHeadless()
{
	GeneticAlgorithm GA(150);
	GA.start();
}

int main()
{
	// noAG();
	AGHeadless();
	return 0;
}