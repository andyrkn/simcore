#include "GeneticAlgorithm.h"
#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include <set>
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

void GeneticAlgorithm::tournamentSelection()
{
	float p = 0.7;
	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

	std::uniform_int_distribution<int> selection_distribution(1, 4);
	std::uniform_int_distribution<int> probability_distribution(1, 1000);
	std::uniform_int_distribution<int> crossover_distribution(1, 21);
	std::uniform_int_distribution<int> tournament_distribution(1, popsize - 1);

	std::vector<Cromozome*> selected;
	std::vector<Cromozome> newPopulation;

	int tournamentSize = selection_distribution(generator) * 2;

	// select k candidates at tourney nrTourney
	std::set<int> selected_indexes;
	while (selected_indexes.size() < tournamentSize)	selected_indexes.insert(tournament_distribution(generator));

	for (auto it = std::begin(selected_indexes); it != std::end(selected_indexes); it++)
	{
		selected.push_back(&population[fitness[*it].first]);
		newPopulation.push_back(population[fitness[*it].first]);
	}

	for (int i = 0; i < selected.size(); i += 2)
	{
		int crossOverIndex = crossover_distribution(generator);
		int mutationIndex = crossover_distribution(generator);
		
		Cromozome child = selected[i]->crossOver(*selected[i + 1], crossOverIndex);
		// both parents mutate and have an offspring
		newPopulation.push_back(child);
		newPopulation.push_back(selected[i]->getMutatedChild(mutationIndex));
		newPopulation.push_back(selected[i + 1]->getMutatedChild(mutationIndex));
	}

	for (std::set<int>::reverse_iterator it = std::rbegin(selected_indexes); it != std::rend(selected_indexes); it++)
	{
		fitness.erase(std::begin(fitness) + (*it));
	}

	// select best two candidates and remove them from candidate list
	for (auto it = std::begin(fitness); it != std::end(fitness) - selected.size() * 2; it++)
	{
		newPopulation.push_back(population[(*it).first]);
	}

}

void GeneticAlgorithm::start()
{
	initPopulation();
	computeFitness();
	tournamentSelection();
	computeFitness();
}