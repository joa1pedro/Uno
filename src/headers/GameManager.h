#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Command.h"

static int INITIAL_HAND_SIZE = 7;

class GameManager {
public:
	GameManager(std::shared_ptr<Deck> deckPtr, int numberOfPlayers)
		: _deck(deckPtr), _numberOfPlayers(numberOfPlayers)
	{}

	void DistributeCards(std::vector<std::unique_ptr<Player>>& players);

	// Command Functions
	bool FetchTurnCommands(Player* player, PlayableCard* card, const std::string& aditionalCommand);
	void ExecuteBeginTurn();
	void ExecuteTurn();

	// Game Functions
	void PlayCard(Player* player, PlayableCard* card);
	void DrawForPlayer(Player* player, int numberCards);
	void ShuffleDeck();
	void DiscardFirst();
	void PrintLastDiscard();
	void InvertGameOrder();
	void SkipNextPlayerTurn();
	bool IsGameOrderInverted();
	int NextPlayer();
private:
	std::vector<std::shared_ptr<Command>> _beginTurnCommands;
	std::vector<std::shared_ptr<Command>> _turnCommands;
	std::shared_ptr<Deck> _deck;
	bool _invertedGameOrder = false;
	int _currentPlayer = 0;
	int _numberOfPlayers;
};