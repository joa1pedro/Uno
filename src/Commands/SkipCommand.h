#pragma once

class SkipCommand : public Command {
private:
	GameManager* _gameManager;

public:
	SkipCommand(GameManager* gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "Skipping Next Player Turn Command.\n";
		this->_gameManager->PassTurn();
	}
};