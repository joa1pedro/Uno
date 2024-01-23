#pragma once

class SkipCommand : public Command {
private:
	std::shared_ptr<GameManager> _gameManager;

public:
	SkipCommand(std::shared_ptr<GameManager> gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Skipping Next Player Turn." << std::endl;
		this->_gameManager->PassTurn();
	}
};