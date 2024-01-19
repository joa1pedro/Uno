#pragma once

enum class CardAction : int
{
	Undefined,
	Default, // Default functionality for normal 0...9 cards.
	Plus2, // Draw +2 Card Action
	Skip, // Blocks the next player Action
	Reverse, // Reverse the order Action
};