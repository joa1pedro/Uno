#pragma once
#include <string>
#include <array>

enum class CardAction : int
{
	Default, // Default functionality for normal 0...9 cards.
	Plus2, // Draw +2 Card Action
	Skip, // Blocks the next player Action
	Reverse, // Reverse the order Action
	Undefined 
};