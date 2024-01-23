#pragma once

class ReverseCommand : public Command {
private:
	std::shared_ptr<GameManager> _gameManager;

public:
	ReverseCommand(std::shared_ptr<GameManager> gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "[Command] Inverting Game Order" << std::endl;
		this->_gameManager->InvertGameOrder();
	}
};