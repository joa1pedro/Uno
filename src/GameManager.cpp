#include "headers/GameManager.h"

#include "Commands/Draw2Command.h"
#include "Commands/DrawCommand.h"
#include "Commands/SkipCommand.h"
#include "Commands/ReverseCommand.h"
#include "Commands/PlayCardCommand.h"
#include "headers/CardUtils.h"

#define NormalGameOrder +1
#define InvertedGameOrder -1

// 0 indexed turn players, first player is index 0 and last one is numberOfPlayers-1
int GameManager::NextPlayer()
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

void GameManager::DistributeCards(std::vector<std::shared_ptr<Player>>& players) 
{
	for (const std::shared_ptr<Player>& player : players)
	{
		for (int i = 0; i < INITIAL_HAND_SIZE; i++) {
			player->Hand.push_back(_deck->DrawCard());
			player->Hand.back().SetPositionInHand(i);
		}
	}
}

bool GameManager::FetchTurnCommands(Player* player, PlayableCard* cardPtr, const std::string& aditionalCommand)
{
	Card card = _deck->GetCardMap()[cardPtr->Id()];
	
	for (int i = 0; i < card.GetCardActions().size(); i++) {
		if (card.GetCardActions()[i] == CardAction::Default) {
			if (!(card._type == _deck->LastDiscard().GetType()
				|| card._type == _deck->LastDiscard().GetTypeOverride()
				|| card._value == _deck->LastDiscard().GetValue()))
			{
				std::cout << "Invalid Card Selected." << std::endl;
				_turnCommands.clear();
				return false;
			}
		}
		if (card.GetCardActions()[i] == CardAction::Reverse) {
			_turnCommands.emplace_back(std::make_shared<ReverseCommand>(this));
		}
		if (card.GetCardActions()[i] == CardAction::Plus2) {
			_beginTurnCommands.emplace_back(std::make_shared<Draw2Command>(this, player));
		}
		if (card.GetCardActions()[i] == CardAction::Skip) {
			_turnCommands.emplace_back(std::make_shared<SkipCommand>(this));
		}
	}

	
	CardType typeOverride = CardUtils::ParseStrToCardType(aditionalCommand);
	if (cardPtr->GetType() == CardType::Wild && CardUtils::ParseStrToCardType(aditionalCommand) != CardType::Undefined) {
		cardPtr->SetTypeOverride(typeOverride);
	}

	_turnCommands.emplace_back(std::make_shared<PlayCardCommand>(this, player, cardPtr));
	return true;
}

void GameManager::SkipNextPlayerTurn() {
	NextPlayer();
}

void GameManager::ExecuteBeginTurn() 
{
	for (const std::shared_ptr<Command>& commandPtr : _beginTurnCommands) {
		commandPtr->Execute();
	}
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

void GameManager::PlayCard(Player* player, PlayableCard* card) 
{
	std::cout << "Discarding card: ";
	card->Print();
	_deck->LastDiscard().SetTypeOverride(CardType::Undefined);
	_deck->Discard(*card);
	player->Discard(*card);
}

void GameManager::DrawForPlayer(Player* player, int numberCards) 
{
	for (int i = 0; i < numberCards; i++) {
		player->Hand.push_back(_deck->DrawCard());
		player->Hand.back().SetPositionInHand(player->Hand.size() - 1);
	}
}

void GameManager::ShuffleDeck()
{
	_deck->Shuffle();
}

// Discard first card from the deck in case theres no card in the discard pile
void GameManager::DiscardFirst()
{
	_deck->Discard(_deck->DrawCard());
}

void GameManager::PrintLastDiscard()
{
	_deck->LastDiscard().Print();
}

void GameManager::InvertGameOrder() 
{
	_invertedGameOrder = !_invertedGameOrder;
}

bool GameManager::IsGameOrderInverted()
{
	return _invertedGameOrder;
}