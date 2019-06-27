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
	/*
	Cromozome a(10, 11, 12, 4);
	Cromozome b(17, 23, 2, 1);
	std::cout << a.cromozomeToString() << "\n";
	std::cout << b.cromozomeToString() << "\n";
	for (int i = 0; i < 21; i++)
		for (int j = i; j < 21; j++)
		{
			Cromozome c = a.twoPointCrossOver(b, 6, 10);
			// std::cout << c.cromozomeToString() << "\n";
			std::cout << i << " " << j << "\n";
		}
	*/
	return 0;
}