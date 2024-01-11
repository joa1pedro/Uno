#include "headers/GameState.h"
#include "headers/Player.h"
#include "headers/Card.h"

void GameState::SetCurrentPlayer(Player player)
{
	GameState::_currentPlayer = player;
}

void GameState::SetLastCardInStack(Card card)
{
	GameState::_lastCardInStack = card;
}

Player GameState::GetCurrentPlayer()
{
	return GameState::_currentPlayer;
}

Card GameState::GetLastCardInStack()
{
	return GameState::_lastCardInStack;
}
