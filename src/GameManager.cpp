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

const std::unordered_map<CardAction, std::shared_ptr<Command>> GameManager::_cardCommandMap = {
	{CardAction::Reverse, std::make_shared<ReverseCommand>()},
	{CardAction::Plus2, std::make_shared<Draw2Command>()},
	{CardAction::Plus4, std::make_shared<Draw4Command>()},
	{CardAction::Skip, std::make_shared<SkipCommand>()}
};

static std::unordered_map<int, bool> _missedUnoMap = {};

std::shared_ptr<Command> GameManager::ParseCardActionToCommand(CardAction action) {
	auto it = _cardCommandMap.find(action);
	if (it != _cardCommandMap.end()) {
		return it->second;
	}
	return nullptr;
}

std::shared_ptr<GameManager> GameManager::GetPointer()
{
	return shared_from_this();
}

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

bool GameManager::ValidDiscardPile(const Card& card)
{
	const PlayableCard& lastDiscard = _deck->LastDiscard();

	if (!CardUtils::IsValidCard(card, lastDiscard))
	{
		IOHelper::AddWarning("Invalid Card Selected.");
		return false;
	}

	return true;
}

bool GameManager::FetchTurnCommands(
	std::shared_ptr<Player> player, const int cardPositionInHand, 
	const std::string& aditionalCommand,
	const std::string& unoWordCheck)
{
	// Early exit if playing a card that you don't have in your hand.
	if (cardPositionInHand >= player->Hand.size() || cardPositionInHand < 0) {
		IOHelper::AddWarning("Invalid Card Selected.");
		return false;
	}

	// Early exit if plays missed UNO! shout out
	if (_missedUnoMap[player->Id]) {
		IOHelper::AddWarning("You missed UNO! You are forced to draw");
		return false;
	}

	// Early exit if player is being forced to draw (+2 or +4 cards)
	if (_forcedDraw) {
		IOHelper::AddWarning("You are forced to draw!");
		return false;
	}

	PlayableCard playedCard = player->Hand[cardPositionInHand];
	Card card = _deck->GetCardMap()[playedCard.Id()];
	// Early type override parse
	CardType typeOverride = CardUtils::ParseStrToCardType(aditionalCommand);

	bool validTurn = true;
	for (const auto& action : card.GetCardActions()) {
		if (action == CardAction::Wild && typeOverride == CardType::Undefined) {
			IOHelper::AddWarning("You are missing to call a new Color!");
			validTurn = false;
		}
		if (action == CardAction::Default && !ValidDiscardPile(card)) {
			IOHelper::AddWarning("That card doesn't match");
			validTurn = false;
		}

		auto it = _cardCommandMap.find(action);
		if (it != _cardCommandMap.end()) {
			it->second->SetExecutor(GetPointer());
			_turnCommands.emplace_back(it->second);
		}
	}

	if (!validTurn) {
		_turnCommands.clear();
		return false;
	}

	// Set Type override if theres additional commands for it
	if (playedCard.GetType() == CardType::Wild 
		&& CardUtils::ParseStrToCardType(aditionalCommand) != CardType::Undefined) {
		playedCard.SetTypeOverride(typeOverride);
	}

	// Add the turn commands for Playing the card Normally
	_turnCommands.emplace_back(std::make_shared<PlayCardCommand>(GetPointer(), player, playedCard));

	// Uno Word Check. Setting the flag if a plays has missed the UNO! shout out
	if (player->Hand.size() == 2 && ((unoWordCheck != "uno") && (aditionalCommand != "uno")))
		_missedUnoMap[player->Id] = true;
		
	return true;
}

void GameManager::ExecuteTurn() 
{
	// Inverted for Loop for executing command in reverse order
	for (auto itr = _turnCommands.size(); itr-- > 0;)
	{
		_turnCommands[itr]->Execute();
	}
	_turnCommands.clear();
	PassTurn();
}

void GameManager::PlayCard(std::shared_ptr<Player> playerPtr, PlayableCard card)
{
	//Reseting the type override for the last card before the new one gets discarded
	_deck->LastDiscard().SetTypeOverride(CardType::Undefined);

	_deck->Discard(card);
	playerPtr->Discard(card);
}


void GameManager::DrawRequest(std::shared_ptr<Player> playerPtr)
{
	_turnCommands.emplace_back(std::make_shared<DrawCommand>(GetPointer(), playerPtr));
}

int GameManager::GetCurrentPlayer()
{
	return _currentPlayer;
}

void GameManager::DrawForPlayer(std::shared_ptr<Player> playerPtr)
{
	if (_missedUnoMap[playerPtr->Id]) {
		_cardsToDrawNext += 2;
		_missedUnoMap[playerPtr->Id] = false;
	}

	// Next draw as 0 is the normal flow of drawing.
	// Any other value greater than 0 is going to sum up for Draw Stacking (+2, +4 or missed UNO! Shout outs)
	if (_cardsToDrawNext == 0) {
		_cardsToDrawNext = 1;
	}

	for (int i = 0; i < _cardsToDrawNext; i++) {
		playerPtr->Hand.push_back(_deck->DrawCard());
		playerPtr->Hand.back().SetPositionInHand(static_cast<int>(playerPtr->Hand.size()) - 1);
	}

	// Reseting flags
	_cardsToDrawNext = 0;
	if (_forcedDraw) {
		_forcedDraw = false;
	}
}

void GameManager::StartGame()
{
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

void GameManager::ForceDrawNextPhase(int sumForNextDraw = 0)
{
	_forcedDraw = true;
	_cardsToDrawNext += sumForNextDraw;
}