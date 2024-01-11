#pragma once
#include <vector>
#include <memory>
#include "Card.h"
#include "Deck.h"

class Player {
public:
	int Id;	
	bool IsCurrentPlayer = false;

	Player(int id);

	std::vector<Card> Hand;
	void Draw(Deck& deck, int numCards = 1);
	void Play(int cardIndex, Card& topCard);
};
