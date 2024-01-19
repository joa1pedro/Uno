#pragma once

class ReverseCommand : public Command {
private:
	GameManager* _gameManager;

public:
	ReverseCommand(GameManager* gameManager) :
		Command(), _gameManager(gameManager)
	{}

	void Execute() const override {
		std::cout << "Inverting Game Order Command.\n";
		this->_gameManager->InvertGameOrder();
	}
};