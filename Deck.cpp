
#include "stdafx.h"
#include "Deck.h"
#include "Card.h"
#include <math.h>

void Deck::set_values(vector<Card> cards) {
	Cards = cards;
}

void Deck::create_full_deck() {
	vector<Card> cards;
	vector<card_suit> list_suits;
	list_suits = { Heart,Diamond,Club,Spade };
	vector<card_value> list_card_values = { Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King };
	cards.reserve(52);
	for (int a = 0; a < 52; a++) {
		Card card;
		card.set_values(list_suits[a % 4], list_card_values[a % 13]);
		cards.push_back(card);
	}
	Cards = cards;
}

Card Deck::draw() {
	Card drawn_card;
	drawn_card = Cards.back();
	Cards.pop_back();
	return(drawn_card);
}

void Deck::shuffle() {
	vector<Card> new_cards;
	int original_size = Cards.size();
		for (int a = 0; a < original_size; a++) {
			int random_number = rand() % Cards.size();
			new_cards.push_back(Cards[random_number]);
			Cards.erase(Cards.begin() + random_number);
	}

		Cards = new_cards;
}

