#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;

enum card_suit{Heart,Diamond,Club,Spade};
enum card_value{Ace = 1,Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10, Jack = 11, Queen = 12, King = 13};

class Card
{
public:
	card_suit Suit;
	card_value Value;
	void set_values(card_suit, card_value);
	vector<int> blackjack_card_values();
};

