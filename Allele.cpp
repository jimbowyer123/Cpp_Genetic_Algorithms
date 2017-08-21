#include "stdafx.h"
#include "Allele.h"


void Allele::set_values(int value, string name, vector<int> possible_values, int allele_number) {
	Value = value;
	Name = name;
	Possible_Values = possible_values;
	Allele_Number = allele_number;

}

void Allele::mutate(float mutation_coefficient) {
	float random = rand() / (float)RAND_MAX;
	if (random < mutation_coefficient) {
		Value = Possible_Values[rand() % Possible_Values.size()];
	}
}

