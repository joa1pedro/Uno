#pragma once
#include <iostream>
#include "../headers/Command.h"
class GameManager;
class IExecutor;
class Player;

class ReverseCommand : public Command {
public:
	ReverseCommand() = default;
	ReverseCommand(std::shared_ptr<IExecutor> gameManager) :
		Command(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Inverting Game Order" << std::endl;
		this->_executor->InvertGameOrder();
	}
};
