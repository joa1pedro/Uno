#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

// PlayCardCommand is GameManager Exclusive usage. Do not use for Extra Card Implementation
class PlayCardCommand : public Command {
private:
	PlayableCard _card;
	std::shared_ptr<Player> _player;

public:
	PlayCardCommand(std::shared_ptr<IExecutor> gameManager, std::shared_ptr<Player> player, PlayableCard card, CardColor typeOverride = CardColor::Undefined) :
		Command(gameManager), _card(card), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Playing Card." << std::endl;
		this->_executor->PlayCard(_player, _card);
	}
};
