#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

class Draw4Command : public Command {
public:
	Draw4Command() = default;
	Draw4Command(std::shared_ptr<IExecutor> gameManager) :
		Command(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 4 cards." << std::endl;
		this->_executor->ForceDrawNextPhase(4, true);
	}
};
