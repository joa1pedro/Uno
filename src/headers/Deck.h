#pragma once
#include <vector>
#include <unordered_map>
#include "IPrintable.h"
#include "Card.h"
#include "PlayableCard.h"

class Deck : IPrintable {
public:
    // Constructor
    bool IsValid = false;

    // Creates a deck with gamedata validation
	Deck() 
	{ 
		Validate(); 
	};

    // Creates a deck with gamedata validation, passing in the filePath for the deck 
	Deck(const char* filePath) 
	{ 
		Validate(); 
		Create(filePath); 
	};

    // Functions
	PlayableCard DrawCard();
	PlayableCard LastDiscard();
	void ResetDeckFromDiscardPile();
	void Shuffle();
	void Discard(const PlayableCard& card);
    void Create(const char* fileName);
	void Print();
	std::vector<PlayableCard> Get();
	std::unordered_map<int, Card> GetCardMap() {
		return _cardMap;
	}
private:
	bool Validate();
    std::unordered_map<int, Card> _cardMap = {};
	std::vector<PlayableCard> _cards = {};
	std::vector<PlayableCard> _discardPile = {};
};
