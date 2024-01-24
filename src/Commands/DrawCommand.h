#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

// DrawCommand is GameManager Exclusive usage. Do not use for Extra Card Implementation
class DrawCommand : public Command {
private:
	std::shared_ptr<Player> _player;

public:
	DrawCommand(std::shared_ptr<IExecutor> gameManager, std::shared_ptr<Player> player) :
		Command(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 1 Card.\n" << std::endl;
		this->_executor->DrawForPlayer(_player);
	}
};
