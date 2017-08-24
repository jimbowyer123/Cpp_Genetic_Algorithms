#include "stdafx.h"
#include "Blacjack_Hand.h"


void Blackjack_Hand::set_values(vector<Card> cards) {
	Cards = cards;
}

vector<int> Blackjack_Hand::values_list() {
	int hand_size = Cards.size();
	if (hand_size == 1) {
		return(Cards[0].blackjack_card_values());
	}
	Blackjack_Hand smaller_hand;
	vector<Card> smaller_hand_cards;
	for (int a = 0; a < hand_size - 1; a++) {
		smaller_hand_cards.push_back(Cards[a]);
	}
	smaller_hand.set_values(smaller_hand_cards);
	vector<int> smaller_hand_values = smaller_hand.values_list();
	vector<int> last_card_values = Cards.back().blackjack_card_values();
	vector<int> new_hand_values;
	for (int a = 0; a < smaller_hand_values.size(); a++) {
		for (int b = 0; b < last_card_values.size(); b++) {
			if (smaller_hand_values[a] + last_card_values[b] < 22) {
				new_hand_values.push_back(smaller_hand_values[a] + last_card_values[b]);
			}
		}
	}
	return(new_hand_values);
}


void Blackjack_Hand::add_card(Card card) {
	Cards.push_back(card);
}