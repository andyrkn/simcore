#include "src/SimulatorCore.h"
#include "src/GeneticAlgorithm.h"

#include<iostream>
#include<thread>

void noAG()
{
	SimulatorCore simcore(false);
	simcore.singleCromozomTest(glm::vec4(63, 46, 3 , 0.7));
}

void AGHead()
{

}

void AGHeadless()
{
	GeneticAlgorithm GA(100);
	GA.start();
}

int main()
{
	// noAG();
	AGHeadless();
	return 0;
}