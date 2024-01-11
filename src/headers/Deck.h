#pragma once
#include <vector>
#include <unordered_map>
#include "IPrintable.h"
#include "Card.h"

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
	Card DrawCard();
	Card LastDiscard();
	void ResetDeckFromDiscardPile();
	void Shuffle();
	void Discard(Card card);
    void Create(const char* fileName);
	void Print();
	std::vector<Card> Get();

private:
	bool Validate();
    std::unordered_map<std::string, Card> _cardMap = {};
	std::vector<Card> _cards = {};
	std::vector<Card> _discardPile = {};
};
