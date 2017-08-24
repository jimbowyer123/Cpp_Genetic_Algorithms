// Genetic_Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Allele.h"
#include "Person.h"
#include "Population.h"
#include "Basic_Blackjack_Functions.h"
#include "Genetic_Algorithm.h"
using namespace std;






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
	Population initial_population = create_strategy_population(50);
	Population final_population = run_simple_evo_algorithm(initial_population, blackjack_utility_function,1000);

    return 0;
}
