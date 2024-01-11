#pragma once
#include <string>
#include <vector>

enum class CardAction : int
{
	Default, // Default functionality for normal 0...9 cards.
	Plus2, // Draw +2 Card Action
	Skip, // Blocks the next player Action
	Reverse, // Reverse the order Action
	Undefined 
};

bool IsValidActions(std::vector<CardAction>& actions);