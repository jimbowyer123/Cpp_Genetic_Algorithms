#pragma once
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <functional>
#include "Person.h"
using namespace std;

class Population {
public:
	vector<Person> People;
	int Generation;
	void set_values(vector<Person>, int generation = 0);
	void assign_scores(function< float(Person)>);
	vector<float> retrieve_scores_list();
	void transform_scores();
	void normalise_scores();
	Population create_mating_pool();
	void mutate(float);
	float average_score();
	Population crossbreed();
	vector<Person> simple_mate(Person, Person);
};