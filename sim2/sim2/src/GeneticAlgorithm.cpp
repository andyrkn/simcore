#include "GeneticAlgorithm.h"
#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include <set>
#include <fstream>

GeneticAlgorithm::GeneticAlgorithm(int popsize)
{
	this->popsize = popsize;
}


GeneticAlgorithm::~GeneticAlgorithm()
{}

GAENV GeneticAlgorithm::getEnv(std::vector<Cromozome>::iterator first, std::vector<Cromozome>::iterator last)
{
	GAENV env;
	int count = 0;
	env.running = true;

	for (auto it = first; it != last; it++)
	{
		count++;
		env.addIndividual((*it).toVec4());
	}

	env.popsize = count;
	return env;
}

void GeneticAlgorithm::visualizePopulation()
{
	GAENV env = getEnv(std::begin(population), std::end(population));
	SimulatorCore core(env, false);
	core.runAG();

}

void GeneticAlgorithm::visualizeIndividual(int index)
{
	glm::vec4 cromozome = population[fitness[index].first].toVec4();
	cromozome.w /= 10;

	SimulatorCore core2(false);
	core2.singleCromozomTest(cromozome);
}

bool GeneticAlgorithm::convergence()
{
	if (fitness[0].second > 5.0f) return false;
	if ((float)fitness[10].second - (float)fitness[0].second < 4.0) return true;
	return false;
}

void GeneticAlgorithm::initPopulation()
{
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution_forces(1, 6400);
	std::uniform_int_distribution<int> distribution_elasticity(1, 8000);

	for (int i = 0; i < popsize; i++)
	{
		long x = distribution_forces(generator) / 100;
		long y = distribution_forces(generator) / 100;
		long z = distribution_forces(generator) / 100;
		long e = distribution_elasticity(generator) / 1000;

		population.push_back(Cromozome(x, y, z, e));
	}
}

void GeneticAlgorithm::mutation(int amount, float probability)
{
	int geneAmount = 21 * amount / 100;
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> probability_distribution(1, 1000);
	std::uniform_int_distribution<int> mutation_distribution(0, 2100);

	for (auto it = std::begin(population) + 1; it != std::end(population); it++)
	{
		float chanceToMutate = (float) probability_distribution(generator) / 1000;
		if (chanceToMutate < probability)
		{
			for (int i = 0; i < geneAmount; i++) // mutate specific amount of genes
			{
				int mutatedGeneIndex = mutation_distribution(generator) / 1000;
				(*it).mutate(mutatedGeneIndex);
			}
		}
	}
}

void GeneticAlgorithm::computeFitness()
{
	//work with 4 threads

	std::vector<float> t1_res, t2_res, t3_res, t4_res;
	int size = popsize / 4;

	GAENV env_q1 = getEnv(population.begin(), population.begin() + size);
	GAENV env_q2 = getEnv(population.begin() + size, population.begin() + 2 * size);
	GAENV env_q3 = getEnv(population.begin() + 2 * size, population.begin() + 3 * size);
	GAENV env_q4 = getEnv(population.begin() + 3 * size, population.end());

	std::thread t1([&t1_res, &env_q1] {
		SimulatorCore core(env_q1, true);
		t1_res = core.runAG();
		});
	std::thread t2([&t2_res, &env_q2] {
		SimulatorCore core(env_q2, true);
		t2_res = core.runAG();
		});
	std::thread t3([&t3_res, &env_q3] {
		SimulatorCore core(env_q3, true);
		t3_res = core.runAG();
		});
	std::thread t4([&t4_res, &env_q4] {
		SimulatorCore core(env_q4, true);
		t4_res = core.runAG();
		});

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::vector<float> res;
	res.insert(res.end(), std::make_move_iterator(std::begin(t1_res)), std::make_move_iterator(t1_res.end()));
	res.insert(res.end(), std::make_move_iterator(t2_res.begin()), std::make_move_iterator(t2_res.end()));
	res.insert(res.end(), std::make_move_iterator(t3_res.begin()), std::make_move_iterator(t3_res.end()));
	res.insert(res.end(), std::make_move_iterator(t4_res.begin()), std::make_move_iterator(t4_res.end()));

	fitness.clear();
	for (int i = 0; i < res.size(); i++)
	{
		fitness.push_back(std::make_pair(i, res[i]));
		/*
		std::cout << i << " " << res[i] << " ||| "
			<< population[i].toVec4().x << " "
			<< population[i].toVec4().y << " "
			<< population[i].toVec4().z << "\n";
		*/
	}

	// order by fitness
	
	std::sort(std::begin(fitness), std::end(fitness),
		[](const std::pair<int, float> p1, const std::pair<int, float> p2) -> bool {
			return p1.second < p2.second;
		});
	
	// printPop();
}

void GeneticAlgorithm::printPop()
{
	for (auto it = std::begin(fitness); it != std::end(fitness); it++)
	{
		std::cout << (*it).second << " ||| ";
		glm::vec4 c = population[(*it).first].toVec4();

		for (int i = 0; i < 4; i++)
		{
			std::cout << c[i] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n--------------------\n";
}

void GeneticAlgorithm::tournamentSelection(bool tournamentMuation)
{
	float p = 0.7;
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

	std::uniform_int_distribution<int> selection_distribution(1, 3);
	std::uniform_int_distribution<int> probability_distribution(1, 1000);
	std::uniform_int_distribution<int> crossover_distribution(0, 21);
	std::uniform_int_distribution<int> tournament_distribution(0, popsize - 1);

	std::vector<Cromozome*> selected;
	std::vector<Cromozome> newPopulation;

	int tournamentSize = selection_distribution(generator) * 3;

	// run tournaments and select top 2 candidates from each tournament
	std::set<int> champions;
	for (int i = 0; i < tournamentSize / 2; i++)
	{
		std::set<int> mock_tourney;
		while (mock_tourney.size() < tournamentSize)
		{
			int candidate = tournament_distribution(generator);
			if (!(champions.find(candidate) != std::end(champions)))
			{
				mock_tourney.insert(candidate);
			}
		}
		auto it = std::begin(mock_tourney);
		champions.insert(*it);
		std::advance(it, 1);
		champions.insert(*it);
	}

	// move champions to new population
	for (auto it = std::begin(champions); it != std::end(champions); it++)
	{
		selected.push_back(&population[fitness[*it].first]);
		newPopulation.push_back(population[fitness[*it].first]);
	}

	// breed the champions
	for (int i = 0; i < selected.size(); i += 2)
	{
		int crossOverIndex1 = crossover_distribution(generator);
		int crossOverIndex2 = crossover_distribution(generator);
		int fmutationIndex = crossover_distribution(generator);
		int smutationIndex = crossover_distribution(generator);

		// singlePointCrossover
		Cromozome child = selected[i]->singlePointCrossOver(*selected[i + 1], crossOverIndex1);
		// if (crossOverIndex1 > crossOverIndex2) { std::swap(crossOverIndex1, crossOverIndex2); }
		// Cromozome child = selected[i]->twoPointCrossOver(*selected[i + 1], crossOverIndex1, crossOverIndex2);

		newPopulation.push_back(child);

		if (tournamentMuation)
		{
			newPopulation.push_back(selected[i]->getMutatedChild(fmutationIndex));
			newPopulation.push_back(selected[i + 1]->getMutatedChild(smutationIndex));
		}
	}

	for (std::set<int>::reverse_iterator it = std::rbegin(champions); it != std::rend(champions); it++)
	{
		fitness.erase(std::begin(fitness) + (*it));
	}

	//add top fitness candidates except the bottom
	for (auto it = std::begin(fitness); newPopulation.size() < popsize; it++)
	{
		newPopulation.push_back(population[(*it).first]);
	}
	population = newPopulation;
}

void GeneticAlgorithm::start()
{
	initPopulation();
	computeFitness();
	bool tournamentMutation = false;
	int iterations = 2000;
	int mutationPercent = 10;
	float mutationProbability = 0.1;

	std::string name =
		"pop" + std::to_string(popsize) +
		"iter" + std::to_string(iterations) +
		"mutationPercent" + std::to_string(mutationPercent) +
		"prob" + std::to_string(mutationProbability) + ".txt";

	std::ofstream fout;
	fout.open(name, std::ofstream::out);

	for (int i = 0; i < iterations; i++)
	{
		tournamentSelection(tournamentMutation); // true = champions mutate, false they dont
		if(!tournamentMutation) mutation(mutationPercent, mutationProbability);
		computeFitness();


		std::cout << "Generation " << i << " best  time: " <<
			fitness[0].second << " ||| " <<
			population[fitness[0].first].toVec4().x << " " <<
			population[fitness[0].first].toVec4().y << " " <<
			population[fitness[0].first].toVec4().z << " " <<
			population[fitness[0].first].toVec4().w << "\n";
		fout << fitness[0].second << " " <<
			population[fitness[0].first].toVec4().x << " " <<
			population[fitness[0].first].toVec4().y << " " <<
			population[fitness[0].first].toVec4().z << " " <<
			population[fitness[0].first].toVec4().w << "\n";

		if (convergence()) break;
		// if (fitness[0].second < 5.0f) break;
	}
	getchar();
	printPop();
	fout.close();
	visualizePopulation();
	visualizeIndividual(0);
}