// Genetic_Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Allele.h"
#include "Person.h"
#include "Population.h"
using namespace std;




Population run_simple_evo_algorithm(Population initial_population,function <float (Person)> utility_function, int number_generations = 100) {
	vector<float> average_scores;
	average_scores.reserve(number_generations);
	Population population = initial_population;
	while (population.Generation < number_generations) {
		population.assign_scores(utility_function);
		average_scores.push_back(population.average_score());
		cout << population.average_score();
		population.transform_scores();
		population.normalise_scores();
		Population mating_pool;
		mating_pool = population.create_mating_pool();
		population = mating_pool.crossbreed();
		population.mutate(0.01);
	}
	return(population);
}

float count_function(Person person) {
	float score = 0.0;
	for (int a = 0; a < person.Alleles.size(); a += 1) {
		score = score + pow(2.0, a)*person.Alleles[a].Value;
	}
	return(score);
}

Person create_binary_person() {
	Person person;
	vector<Allele> alleles;
	alleles.reserve(6);
	for (int a = 0; a < 6; a += 1) {
		Allele new_allele;
		new_allele.set_values(rand() % 2, "b", vector<int> {0, 1}, a);
		alleles.push_back(new_allele);
	}
	person.set_values(alleles);
	return(person);
}

Population create_binary_population(int number_people) {
	Population population;
	vector<Person> people;
	people.reserve(number_people);
	for (int a = 0; a < number_people; a += 1) {
		people.push_back(create_binary_person());
	}
	population.set_values(people);
	return(population);
}

int main()
{
	Population initial_population = create_binary_population(20);
	Population final_population = run_simple_evo_algorithm(initial_population, count_function);

    return 0;
}
