#pragma once

enum class CardAction : int
{
	Undefined,
	Default, // Default functionality for normal 0...9 cards.
	Plus2, // Draw +2 Cards 
	Plus4, // Draw +4 Cards
	Skip, // Blocks the next player 
	Reverse, // Reverse the order 
	Wild, // Chooses the color
};