#include "stdafx.h"
#include "Card.h"


void Card::set_values(card_suit suit, card_value value) {
	Suit = suit;
	Value = value;
}

vector<int> Card::blackjack_card_values() {
	vector<int> card_values;
	card_values = { Value };
	if (Value == Ace) {
		card_values = { 1,11 };
	}
	if ((Value == Jack) || (Value == Queen) || (Value == King) ){
		card_values = { 10 };
	}
	return(card_values);
}