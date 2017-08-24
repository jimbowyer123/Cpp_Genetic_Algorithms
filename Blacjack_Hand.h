#pragma once
#include "Card.h"
#include "Deck.h"

class Blackjack_Hand
{
public:
	vector<Card> Cards;
	void set_values(vector<Card>);
	vector<int> values_list();
	void add_card(Card);
};

