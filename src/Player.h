#pragma once
#include <vector>
#include <memory>
#include "Card.h"
#include "Deck.h"

class Player {
public:
	int _id;	
	bool _currentPlayer = false;

	Player(int id);

	std::vector<Card> GetHand();
	void Draw(Deck& deck, int numCards = 1);
	void Play(int cardIndex, Card& topCard);

private:
	std::vector<Card> _hand;
};
