#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

class SkipCommand : public Command {
public:
	SkipCommand() = default;
	SkipCommand(std::shared_ptr<IExecutor> gameManager) :
		Command(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Skipping Next Player Turn." << std::endl;
		this->_executor->PassTurn();
	}
};