#pragma once
#include <vector>
#include <memory>
#include "Card.h"
#include "Deck.h"

class Player {
public:
	int _id;	
	bool currentPlayer = false;

	Player(int id);

	std::vector<Card> GetHand();
	void DrawCard(Deck& deck, int numCards = 1);
	void PlayCard(int cardIndex, Card& topCard);
	int CardsInHand();

private:
	std::vector<Card> _hand;
	std::shared_ptr<Player> _leftPlayer;
	std::shared_ptr<Player> _rightPlayer;
};
