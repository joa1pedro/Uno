#pragma once
#include <memory>
#include "Player.h"
#include "Card.h"

class GameState {
public:
	Player _currentPlayer;
	Card _lastCardInStack;

	GameState() = default;

	void SetCurrentPlayer(Player player);
	void SetLastCardInStack(Card card);

	Player GetCurrentPlayer();
	Card GetLastCardInStack();
};
