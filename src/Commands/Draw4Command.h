#pragma once
#include "../headers/Command.h"
#include "../headers/GameManager.h"

class Draw4Command : public Command {
private:
	GameManager* _gameManager;
	std::shared_ptr<Player> _player;

public:
	Draw4Command(GameManager* gameManager, std::shared_ptr<Player> player) :
		Command(), _gameManager(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 4 cards.\n";
		this->_gameManager->ForceDrawNextPhase(4);
	}
};