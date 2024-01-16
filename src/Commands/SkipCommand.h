#pragma once
#include <iostream>
#include "../headers/GameManager.h"

class SkipCommand : public Command {
private:
	GameManager* _gameManager;

public:
	SkipCommand(GameManager* gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "Skipping Next Player.\n";
		this->_gameManager->SkipNextPlayerTurn();
	}
};