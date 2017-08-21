#pragma once
#include <stdlib.h>
#include "stdafx.h"
#include <vector>
#include "Allele.h"
using namespace std;

class Person {
public:
	vector<Allele> Alleles;
	float Utility_Score;
	void set_values(vector<Allele>, float score = 0.0);
	void mutate(float);
};
