#include "stdafx.h"
#include "Person.h"

void Person::mutate(float mutation_coefficient) {
	int number_alleles = Alleles.size();
	for (int a = 0; a < number_alleles; a += 1) {
		Alleles[a].mutate(mutation_coefficient);
	}
}

void Person::set_values(vector<Allele> alleles, float score) {
	Alleles = alleles;
	Utility_Score = score;
};
