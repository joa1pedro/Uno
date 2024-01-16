#pragma once
#include <iostream>
#include "../headers/Command.h"

class DrawCommand : public Command {
private:
	GameManager* _gameManager;
	Player* _player;

public:
	DrawCommand(GameManager* gameManager, Player* player) :
		Command(), _gameManager(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "Draw 2 Game Order .\n";
		this->_gameManager->DrawForPlayer(_player, 1);
	}
};