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

	// Distribute all cards from the current deck for all players
	void DistributeCards(std::vector<std::shared_ptr<Player>>& players);

	// Fetch all commands for that turn
	bool FetchTurnCommands(Player* player, PlayableCard* card, const std::string& aditionalCommand);
	
	// Executed in the beginning of the turn, if theres any actions pending
	void ExecuteBeginTurn();

	// Execute the turn with all the actions pending for that turn
	void ExecuteTurn();

	// Game Functions
	void PlayCard(Player* player, PlayableCard* card);

	// Draws a card for the player
	void DrawForPlayer(Player* player, int numberCards);

	// Tells the deck to be Shuffled
	void ShuffleDeck();

	// Discard the first card from the Deck
	void DiscardFirst();

	// Prints the top card of the Discard Pile
	void PrintLastDiscard();

	// Inverts the game order for the next turn
	void InvertGameOrder();
	
	// Pass the turn for the next player.
	int PassTurn();

	// Returns if the game order is currently inverted
	bool IsGameOrderInverted();
	
	// Card Comparison
	bool IsValidCard(const Card& selectedCard, const PlayableCard& lastDiscard) const;

	// Compares the selected card Type or TypeOverride with the last discard.
	bool HasMatchingType(const Card& selectedCard, const PlayableCard& lastDiscard) const;

	// Compares the selected card Value with the last discard
	bool HasMatchingValue(const Card& selectedCard, const PlayableCard& lastDiscard) const;

	// Checks if the Discard Pile matches in Type, TypeOverride or Value with the targed card
	bool CheckDiscardPile(Card& card);
private:
	std::vector<std::shared_ptr<Command>> _beginTurnCommands;
	std::vector<std::shared_ptr<Command>> _turnCommands;
	std::shared_ptr<Deck> _deck;
	bool _invertedGameOrder = false;
	int _currentPlayer = 0;
	int _numberOfPlayers;
};