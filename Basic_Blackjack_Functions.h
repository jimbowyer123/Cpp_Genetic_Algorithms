#pragma once
#include "Deck.h"
#include "Blacjack_Hand.h"
#include "Population.h"
#include <string>
#include <sstream>
#include <math.h>

Deck create_standard_deck() {
	Deck new_deck;
	new_deck.create_full_deck();
	return(new_deck);
}

int who_wins(Blackjack_Hand dealer_hand, Blackjack_Hand player_hand) {
	if (player_hand.values_list().size() == 0) {
		return(0);
	}
	if (dealer_hand.values_list().size() == 0) {
		return(2);
	}
	if (player_hand.values_list().back() > dealer_hand.values_list().back()) {
		return(2);
	}
	if (player_hand.values_list().back() == dealer_hand.values_list().back()) {
		return(1);
	}
	if (player_hand.values_list().back() < dealer_hand.values_list().back()) {
		return(0);
	}
}


Person create_random_strategy() {
	Person strategy;
	vector<Allele> alleles;
	for (int player_total = 2; player_total < 22; player_total++) {
		for (int dealer_total = 2; dealer_total < 12; dealer_total++) {
			string player_string;
			string dealer_string;
			ostringstream player_convert;
			ostringstream dealer_convert;
			player_convert << player_total;
			dealer_convert << dealer_total;
			string mid_string = "::";
			string name = player_convert.str() + mid_string + dealer_convert.str();
			int allele_value = rand() % 2;
			vector<int> possible_values = { 0,1 };
			Allele allele;
			allele.set_values(allele_value, name, possible_values, 0);
			alleles.push_back(allele);
		}
	}
	strategy.set_values(alleles, 0.0);
	return(strategy);
}

Population create_strategy_population(int number_people) {
	Population population;
	vector<Person> strategies;
	for (int a = 0; a < number_people; a++) {
		strategies.push_back(create_random_strategy());
	}
	population.set_values(strategies);
	return(population);
}

int play_blackjack_from_stand(Blackjack_Hand player_hand, Blackjack_Hand dealer_hand, Deck deck) {
	if (dealer_hand.values_list().size() == 0) {
		return(2);
	}
	if (dealer_hand.values_list().back() >= 17) {
		return(who_wins(dealer_hand, player_hand));
	}
	if (dealer_hand.values_list().back() < 17) {
		dealer_hand.add_card(deck.draw());
		return(play_blackjack_from_stand(player_hand, dealer_hand, deck));
	}
}

int what_to_do(Person strategy, int dealer_value, int player_value) {
	ostringstream dealer_convert;
	ostringstream player_convert;
	dealer_convert << dealer_value;
	player_convert << player_value;
	string string_dealer = dealer_convert.str();
	string string_player = player_convert.str();
	string name = string_player + "::" + string_dealer;
	for (int a = 0; a < strategy.Alleles.size(); a++){
		if (name == strategy.Alleles[a].Name) {
			return(strategy.Alleles[a].Value);
		}
	}
}

int play_blackjack_from(Person strategy, Deck deck, Blackjack_Hand dealer_hand, Blackjack_Hand player_hand) {
	if (player_hand.values_list().size() == 0) {
		return(0);
	}
	int choice = what_to_do(strategy, dealer_hand.values_list().back(), player_hand.values_list().back());
	if (choice == 0) {
		return(play_blackjack_from_stand(player_hand, dealer_hand, deck));
	}
	if (choice == 1) {
		player_hand.add_card(deck.draw());
		return(play_blackjack_from(strategy, deck, dealer_hand, player_hand));
	}
}


int play_blackjack_round(Person strategy) {
	Deck deck;
	deck.create_full_deck();
	deck.shuffle();
	Blackjack_Hand player_hand;
	Blackjack_Hand dealer_hand;
	player_hand.add_card(deck.draw());
	player_hand.add_card(deck.draw());
	dealer_hand.add_card(deck.draw());
	return(play_blackjack_from(strategy, deck, dealer_hand, player_hand));
}

float blackjack_utility_function(Person strategy) {
	float score = 0.0;
	for (int a = 0; a < 100; a++) {
		int result = play_blackjack_round(strategy);
		switch (result) {
		case 0:
			score = score - 1.0;
			break;
		case 2:
			score = score + 1.0;
			break;
		default:
			break;
		}
	}
	return(score);
}
