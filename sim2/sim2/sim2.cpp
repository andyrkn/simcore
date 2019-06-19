#include "src/SimulatorCore.h"
#include "src/GeneticAlgorithm.h"

#include<iostream>
#include<thread>

void noAG()
{
	SimulatorCore simcore(false);
	simcore.singleCromozomTest(glm::vec4(63, 34, 13, 0.2));
}

void AGHead()
{

}

void AGHeadless()
{
	GeneticAlgorithm GA(40);
	GA.start();
}

int main()
{
	// noAG();
	AGHeadless();
	return 0;
}