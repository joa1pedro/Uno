#include "headers/GameManager.h"

#include "Commands/Draw2Command.h"
#include "Commands/Draw4Command.h"
#include "Commands/DrawCommand.h"
#include "Commands/SkipCommand.h"
#include "Commands/ReverseCommand.h"
#include "Commands/PlayCardCommand.h"
#include "headers/CardUtils.h"
#include "headers/IOHelper.h"

#define NormalGameOrder +1
#define InvertedGameOrder -1

// 0 indexed turn players, first player is index 0 and last one is numberOfPlayers-1
int GameManager::PassTurn()
{
	int lastPlayer = _numberOfPlayers - 1;
	if (_invertedGameOrder) {
		_currentPlayer = (_currentPlayer InvertedGameOrder == -1) ? lastPlayer : _currentPlayer InvertedGameOrder;
	}
	else { // Normal Game order
		_currentPlayer = (_currentPlayer == lastPlayer) ? 0 : _currentPlayer NormalGameOrder;
	}

	return _currentPlayer;
}

void GameManager::DistributeCards() 
{
	for (const std::shared_ptr<Player>& player : _players)
	{
		for (int i = 0; i < INITIAL_HAND_SIZE; i++) {
			player->Hand.push_back(_deck->DrawCard());
			player->Hand.back().SetPositionInHand(i);
		}
	}
}

bool GameManager::CheckDiscardPile(Card& card)
{
	const PlayableCard& lastDiscard = _deck->LastDiscard();

	if (!CardUtils::IsValidCard(card, lastDiscard))
	{
		IOHelper::AddWarning("Invalid Card Selected.");
		return false;
	}

	return true;
}

void GameManager::ForceDrawNextPhase(int sumForNextDraw = 0)
{
	_forcedDraw = true;
	_nextDraw += sumForNextDraw;
}

bool GameManager::FetchTurnCommands(
	std::shared_ptr<Player> player, PlayableCard playedCard, 
	const std::string& aditionalCommand,
	const std::string& unoWordCheck)
{

	if (_missedUno == player->Id) {
		std::cout << "You missed UNO! You are forced to draw" << std::endl;
		return false;
	}
	if (_forcedDraw) {
		IOHelper::AddWarning("You are forced to draw!");
		return false;
	}

	Card card = _deck->GetCardMap()[playedCard.Id()];
	
	// Early type override parse
	CardType typeOverride = CardUtils::ParseStrToCardType(aditionalCommand);

	for (int i = 0; i < card.GetCardActions().size(); i++) {
		if (card.GetCardActions()[i] == CardAction::Wild) {
			if (typeOverride == CardType::Undefined)
			{
				IOHelper::AddWarning("You are missing to call a new Color!");
				// Wild Cards must have a TypeOverride
				_turnCommands.clear();
				return false;
			}
		}

		if (card.GetCardActions()[i] == CardAction::Default) {
			if (!CheckDiscardPile(card)) {
				IOHelper::AddWarning("That card doesn't match");
				_turnCommands.clear();
				return false;
			}
		}

		if (card.GetCardActions()[i] == CardAction::Reverse) {
			_turnCommands.emplace_back(std::make_shared<ReverseCommand>(this));
		}
		if (card.GetCardActions()[i] == CardAction::Plus2) {
			_turnCommands.emplace_back(std::make_shared<Draw2Command>(this, player));
		}
		if (card.GetCardActions()[i] == CardAction::Plus4) {
			_turnCommands.emplace_back(std::make_shared<Draw4Command>(this, player));
		}
		if (card.GetCardActions()[i] == CardAction::Skip) {
			_turnCommands.emplace_back(std::make_shared<SkipCommand>(this));
		}
	}

	// Set Type override if theres additional commands for it
	if (playedCard.GetType() == CardType::Wild 
		&& CardUtils::ParseStrToCardType(aditionalCommand) != CardType::Undefined) {
		playedCard.SetTypeOverride(typeOverride);
	}

	_turnCommands.emplace_back(std::make_shared<PlayCardCommand>(this, player, playedCard));

	if (player->Hand.size() == 2){
		if ((unoWordCheck != "uno") && (aditionalCommand != "uno"))
		{
			SetMissedUno(player->Id);
		}
	}

	return true;
}

void GameManager::SetMissedUno(int playerId)
{
	_missedUno = playerId;
}

void GameManager::ExecuteTurn() 
{
	// Inverted for Loop for executing command in reverse order
	for (auto itr = _turnCommands.size(); itr-- > 0;)
	{
		_turnCommands[itr]->Execute();
	}
	_turnCommands.clear();
}

void GameManager::PlayCard(std::shared_ptr<Player> playerPtr, PlayableCard card)
{
	//Reseting the type override for the last card before the new one gets discarded
	_deck->LastDiscard().SetTypeOverride(CardType::Undefined);

	_deck->Discard(card);
	playerPtr->Discard(card);
}

void GameManager::DrawForPlayer(std::shared_ptr<Player> playerPtr)
{
	if (_missedUno == playerPtr->Id) {
		_nextDraw += 2;
	}
	if (_nextDraw == 0) {
		_nextDraw = 1;
	}

	for (int i = 0; i < _nextDraw; i++) {
		playerPtr->Hand.push_back(_deck->DrawCard());
		playerPtr->Hand.back().SetPositionInHand(playerPtr->Hand.size() - 1);
	}

	_nextDraw = 0;
	_missedUno = -1;

	if (_forcedDraw) {
		_forcedDraw = false;
	}
}

void GameManager::StartGame()
{
	// Game prep initialization
	ShuffleDeck();
	DistributeCards();
	DiscardFirstValid();
}

void GameManager::ShuffleDeck()
{
	_deck->Shuffle();
}

void GameManager::DiscardFirst()
{
	_deck->Discard(_deck->DrawCard());
}

void GameManager::DiscardFirstValid()
{
	DiscardFirst();
	if (_deck->LastDiscard().GetType() == CardType::Wild) {
		_deck->ResetDeckFromDiscardPile();
		DiscardFirstValid();
	}
}

void GameManager::PrintLastDiscard()
{
	std::cout << "Last Discard : " << std::endl;
	_deck->LastDiscard().PrintFromFile();
}

void GameManager::InvertGameOrder() 
{
	_invertedGameOrder = !_invertedGameOrder;
}

bool GameManager::IsGameOrderInverted()
{
	return _invertedGameOrder;
}