#pragma once
#include <vector>
#include "PlayableCard.h"

class Player : IPrintable {
public:
	int Id;	
	bool IsCurrentPlayer = false;

	Player(int id);

	std::vector<PlayableCard> Hand;
	void Discard(PlayableCard& card);
	void Print();
	void PrintHand();
};
