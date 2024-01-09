#pragma once
#include <vector>
#include <map>
#include "IPrintable.h"
#include "Card.h"

class Deck : IPrintable {
public:
    // Constructor
    bool _isValid = false;

    // Creates a deck with gamedata validation
	Deck() { Validate(); };

    // Creates a deck with gamedata validation, passing in the filePath for the deck 
	Deck(const char* filePath) { Validate(); Create(filePath); };


    // Functions
    void Shuffle();
    Card DrawCard();
    void Create(const char* fileName);
    void Print();
    std::vector<Card> Get();

private:
	bool Validate();
    std::map<std::string, Card> _cardMap = {};
    std::vector<Card> _cards = {};
};
