#pragma once
#include <vector>
#include <string>
#include "PlayableCard.h"

class Player : IPrintable {
public:
	int Id;	
	std::string Name;

	Player(int id);

	std::vector<PlayableCard> Hand;

	// Removes the selected card from this player hand
	void Discard(PlayableCard card);

	// Prints the Id of this player. Format: Player [id]
	void Print() const;

	// Prints the current card in hand for this player
	void PrintHand() const;

	bool CurrentlyPlaying = false;
};
