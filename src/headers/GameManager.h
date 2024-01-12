#pragma once
#include <iostream>
#include "Card.h"
#include "Player.h"

class GameManager {
public:
	void ProcessCard(Card* card) {
		std::cout << "Receiver: Working on (Card:)";
		card->Print();
	}

	void ProcessPlayer(Player* player) {
		std::cout << "Receiver: Also working on (Player:" << player->Id << ")\n";		
	}
};