#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

class Draw2Command : public Command {
public:
	Draw2Command() = default;
	Draw2Command(std::shared_ptr<IExecutor> gameManager) :
		Command(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 2 cards." << std::endl;
		this->_executor->ForceDrawNextPhase(2);
	}
};
