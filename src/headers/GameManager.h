#pragma once
#include <iostream>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Command.h"
#include "IExecutor.h"

static const int INITIAL_HAND_SIZE = 7;

class GameManager : public IExecutor, public std::enable_shared_from_this<GameManager> {
public:
	GameManager(std::shared_ptr<Deck> deckPtr, std::vector<std::shared_ptr<Player>> players)
		: _deck(deckPtr), _players((players)), _numberOfPlayers(static_cast<int>(_players.size()))
	{}

	// Distribute all cards from the current deck for all players
	void DistributeCards();

	// Fetch all commands for that turn. Returns a boolean if the turn fetched is valid or not.
	bool FetchTurnCommands(std::shared_ptr<Player> player, const int cardPositionInHand, const std::string& aditionalCommand, const std::string& unoWordCheck);

	// Execute the turn with all the actions pending for that turn
	void ExecuteTurn();

	// Tells the deck to be Shuffled
	void ShuffleDeck();

	// Discard the first card from the Deck
	void DiscardFirst();

	// Shuffles the deck, distribute cards and discards the first valid card
	void StartGame();

	// First action to be taken by the deck after distributing cards.
	// Discard first and check if its not a WILD card. If it is, return it, shuffle and discard a new one.
	void DiscardFirstValid();

	// Prints the top card of the Discard Pile
	void PrintLastDiscard();

	// Returns if the game order is currently inverted
	bool IsGameOrderInverted();

	// Checks if the Discard Pile matches in Type, TypeOverride or Value with the target card
	bool ValidDiscardPile(const Card& card);

	// Sets the player that has missed uno spell check
	void SetMissedUno(int playerId);

	// Returns a pointer to this Game Manager
	std::shared_ptr<GameManager> GetPointer();

	// Makes a draw request for the manager. Player is going to draw the number of cards currently set for that turn to draw
	void DrawRequest(std::shared_ptr<Player> playerPtr);

	// ################################# Overrides for IExecutor #################################

	// Plays the card, puts it in the discard pile and removes it from the player hand
	void PlayCard(std::shared_ptr<Player> player, PlayableCard card) override;

	// Inverts the game order for the next turn
	void InvertGameOrder() override;

	// Pass the turn for the next player. Returns the index of the next player 
	int PassTurn() override;

	// Forces the draw for the next player.
	void ForceDrawNextPhase	(int sumForNextDraw) override;

	// Draws a card for the player
	void DrawForPlayer(std::shared_ptr<Player> player) override;

private:
	std::vector<std::shared_ptr<Command>> _turnCommands;
	std::vector<std::shared_ptr<Player>> _players;
	std::shared_ptr<Deck> _deck;

	bool _invertedGameOrder = false;
	bool _forcedDraw = false;
	int _numberOfPlayers = -1;
	int _currentPlayer = 0;

	// Represents the index of the player that has missed the UNO! yelling.
	int _missedUno = -1;

	// This represents how many cards the next player that is going to draw will receive.
	// If this is at 0. The player is going to receive 1 by default
	int _cardsToDrawNext = 0;

	static std::shared_ptr<Command> ParseCardActionToCommand(CardAction action) {
		auto it = _cardCommandMap.find(action);
		if (it != _cardCommandMap.end()) {
			return it->second;
		}
		return nullptr;
	}
	static const std::unordered_map<CardAction, std::shared_ptr<Command>> _cardCommandMap;
};