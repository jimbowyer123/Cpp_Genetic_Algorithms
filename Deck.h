#pragma once
#include "Card.h"
#include <vector>


class Deck
{
public:
	vector<Card> Cards;
	void set_values(vector<Card>);
	void create_full_deck();
	Card draw();
	void shuffle();
};

