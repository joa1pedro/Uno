#pragma once

class SkipCommand : public Command {
private:
	GameManager* _gameManager;

public:
	SkipCommand(GameManager* gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Skipping Next Player Turn.\n";
		this->_gameManager->PassTurn();
	}
};