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
	GameManager(std::shared_ptr<Deck> deckPtr, std::vector<std::shared_ptr<Player>> players)
		: _deck(deckPtr), _players((players)), _numberOfPlayers(_players.size())
	{}

	// Distribute all cards from the current deck for all players
	void DistributeCards();

	// Fetch all commands for that turn
	bool FetchTurnCommands(std::shared_ptr<Player> player, PlayableCard card, const std::string& aditionalCommand);
	
	// Executed in the beginning of the turn, if theres any actions pending
	void ExecuteBeginTurn();

	// Execute the turn with all the actions pending for that turn
	void ExecuteTurn();

	// Game Functions
	void PlayCard(std::shared_ptr<Player> player, PlayableCard card);

	// Draws a card for the player
	void DrawForPlayer(std::shared_ptr<Player> player, int numberCards);

	// Tells the deck to be Shuffled
	void ShuffleDeck();

	// Discard the first card from the Deck
	void DiscardFirst();

	// Prints the top card of the Discard Pile
	void PrintLastDiscard();

	// Inverts the game order for the next turn
	void InvertGameOrder();
	
	// Pass the turn for the next player. Returns the index of the next player 
	int PassTurn();

	// Returns if the game order is currently inverted
	bool IsGameOrderInverted();

	// Checks if the Discard Pile matches in Type, TypeOverride or Value with the target card
	bool CheckDiscardPile(Card& card);
private:
	std::vector<std::shared_ptr<Command>> _beginTurnCommands;
	std::vector<std::shared_ptr<Command>> _turnCommands;
	std::vector<std::shared_ptr<Player>> _players;
	std::shared_ptr<Deck> _deck;
	bool _invertedGameOrder = false;
	int _currentPlayer = 0;
	int _numberOfPlayers;
};