#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
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