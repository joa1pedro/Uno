#pragma once
#include <vector>
#include <unordered_map>
#include "IPrintable.h"
#include "Card.h"
#include "PlayableCard.h"

class Deck : IPrintable {
public:
    // Creates a deck with gamedata validation. No cards are going to be added
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

    // Returns a card from the top of the deck and removes it from the top
	PlayableCard DrawCard();

	// Returns the top card of the discard pile
	PlayableCard LastDiscard() const;

	// Resets the deck with the current cards in the discard pile and then Shuffles it.
	void ResetDeckFromDiscardPile();

	// Shuffles the Deck
	void Shuffle();

	// Adds a card to the discard pile
	void Discard(const PlayableCard card);
    
	// Creates a deck using a file inside GameData folder.
	void Create(const char* fileName);

	// Prints every current card in the deck
	void Print() const;

	// Returns all cards currently in the deck
	std::vector<PlayableCard> Get() const;

	// Returns a Map of a Card structures that can exist in this deck
	std::unordered_map<int, Card> GetCardMap() const;

	// Returns if this deck is valid for playing. No cards can have no CardActions, invalid CardType or CardValue 
	bool IsValid();

private:
	// Validates if the GameData folder has a valid GameData.txt file
	bool Validate();

	bool _isValid = false;
    std::unordered_map<int, Card> _cardMap = {};
	std::vector<PlayableCard> _cards = {};
	std::vector<PlayableCard> _discardPile = {};
};
