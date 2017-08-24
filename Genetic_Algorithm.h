#pragma once
#include "Population.h"




Population run_simple_evo_algorithm(Population initial_population, function <float(Person)> utility_function, int number_generations = 100) {
	vector<float> average_scores;
	average_scores.reserve(number_generations);
	Population population = initial_population;
	while (population.Generation < number_generations) {
		population.assign_scores(utility_function);
		average_scores.push_back(population.average_score());
		cout << population.average_score();
		cout << "\n";
		population.transform_scores();
		population.normalise_scores();
		Population mating_pool;
		mating_pool = population.create_mating_pool();
		population = mating_pool.crossbreed();
		population.mutate(0.01);
	}
	return(population);
}
