#pragma once

enum class CardAction : int
{
	Undefined,
	Default, // Default functionality for normal 0...9 cards.
	Plus2, // Draw +2 Card 
	Skip, // Blocks the next player 
	Reverse, // Reverse the order 
	Wild, // Chooses the color
};