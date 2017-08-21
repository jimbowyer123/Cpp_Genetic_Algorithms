// Genetic_Algorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <array>
#include <math.h>
using namespace std;

class Allele {
public:
	int Value;
	string Name;
	vector<int> Possible_Values;
	int Allele_Number;
	void set_values(int, string, vector<int>, int);
	void mutate(float);

};

void Allele::set_values(int value, string name, vector<int> possible_values, int allele_number) {
	Value = value;
	Name = name;
	Possible_Values = possible_values;
	Allele_Number = allele_number;

}

void Allele::mutate(float mutation_coefficient) {
	float random = rand() / (float) RAND_MAX;
	if (random < mutation_coefficient) {
		Value = Possible_Values[rand() % Possible_Values.size()];
	}
}


class Person {
public:
	vector<Allele> Alleles;
	float Utility_Score;
	void set_values(vector<Allele>, float);
	void mutate(float);
};

void Person::mutate(float mutation_coefficient) {
	int number_alleles = Alleles.size();
	for (int a = 0; a < number_alleles; a += 1) {
		Alleles[a].mutate(mutation_coefficient);
	}
}

void Person::set_values(vector<Allele> alleles, float score = 0.0) {
	Alleles = alleles;
	Utility_Score = score;
};

class Population {
public:
	vector<Person> People;
	int Generation;
	void set_values(vector<Person>, int);
	void assign_scores(function< float (Person)>);
	vector<float> retrieve_scores_list();
	void transform_scores();
	void normalise_scores();
	Population create_mating_pool();
	void mutate(float);
	float average_score();
	Population crossbreed();
};

void Population::set_values(vector<Person> people, int generation = 0) {
	People = people;
	Generation = generation;
};

void Population::assign_scores(function< float (Person)> score_func) {
	int number_people = People.size();
	for (int a = 0; a < number_people; a += 1) {
		People[a].Utility_Score = score_func(People[a]);
	}
}

vector<float> Population::retrieve_scores_list() {
	int number_people = People.size();
	vector<float> scores;
	scores.reserve(number_people);
	for (int a = 0; a < number_people; a += 1) {
		scores.push_back(People[a].Utility_Score);
	}
	return(scores);
}

void Population::transform_scores() {
	vector<float> scores = retrieve_scores_list();
	vector<float>::iterator min_score = min_element(begin(scores), end(scores));
	int min_position = distance(begin(scores), min_score);
	float min_value = scores[min_position];
	int number_people = scores.size();
	for (int a = 0; a < number_people; a += 1) {
		People[a].Utility_Score = People[a].Utility_Score - min_value;
	}
}

void Population::normalise_scores() {
	float sum_scores = 0.0;
	vector<float> scores = retrieve_scores_list();
	int number_people = scores.size();
	for (int a = 0; a < number_people; a += 1) {
		sum_scores = sum_scores + scores[a];
	}
	if (sum_scores == 0.0) {
		for (int a = 0; a < number_people; a++ ) {
			People[a].Utility_Score = 1.0/(number_people);
		}
	}
	else {
		for (int b = 0; b < number_people; b += 1) {
			People[b].Utility_Score = People[b].Utility_Score / sum_scores;
		}
	}
}


vector<Person> simple_mate(Person person_1, Person person_2) {
	vector<Allele> new_alleles_one;
	vector<Allele> new_alleles_two;
	int number_alleles = person_1.Alleles.size();
	new_alleles_one.reserve(number_alleles);
	new_alleles_two.reserve(number_alleles);
	int crossover_point = rand() % (number_alleles + 1);
	for (int counter = 0; counter < number_alleles; counter += 1) {
		if (counter < crossover_point) {
			new_alleles_one.push_back(person_1.Alleles[counter]);
			new_alleles_two.push_back(person_2.Alleles[counter]);
		}
		else {
			new_alleles_two.push_back(person_1.Alleles[counter]);
			new_alleles_one.push_back(person_2.Alleles[counter]);
		}
	}
	Person new_person_one;
	Person new_person_two;
	new_person_one.set_values(new_alleles_one);
	new_person_two.set_values(new_alleles_two);
	vector<Person> new_people;
	new_people.reserve(2);
	new_people.push_back(new_person_one);
	new_people.push_back(new_person_two);
	return(new_people);
}

Population Population::create_mating_pool() {
	int b;
	int number_people = People.size();
	vector<Person> mating_pool;
	mating_pool.reserve(number_people);
	for (int a = 0; a < number_people; a += 1) {
		float random_number = rand() / (float) RAND_MAX;
		float sum_score = 0.0;
		b = 0;
		while (sum_score < random_number) {
			sum_score = sum_score + People[b].Utility_Score;
			b += 1;
		}
		mating_pool.push_back(People[b - 1]);
	}
	Population mating_population;
	mating_population.set_values(mating_pool,Generation);
	return(mating_population);
}

void Population::mutate(float mutation_coefficient = 0.01) {
	int number_people = People.size();
	for (int a = 0; a < number_people; a += 1) {
		People[a].mutate(mutation_coefficient);
	}
}

float Population::average_score() {
	int number_people = People.size();
	float sum_scores = 0.0;
	for (int a = 0; a < number_people; a += 1) {
		sum_scores = sum_scores + People[a].Utility_Score;
	}
	float average_score = sum_scores / number_people;
	return(average_score);
}

Population Population::crossbreed() {
	int number_people = People.size();
	Population new_population;
	vector<Person> new_people;
	new_people.reserve(number_people);
	new_population.set_values(new_people, Generation + 1);
	for (int a = 0; a < number_people; a += 2) {
		Person person_1 = People[a];
		Person person_2 = People[a + 1];
		vector<Person> mated_people = simple_mate(person_1,person_2);
		new_population.People.push_back(mated_people[0]);
		new_population.People.push_back(mated_people[1]);
	}
	return(new_population);
}


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
