#pragma once

class Draw2Command : public Command {
private:
	std::shared_ptr<GameManager> _gameManager;
	std::shared_ptr<Player> _player;

public:
	Draw2Command(std::shared_ptr<GameManager> gameManager, std::shared_ptr<Player> player) :
		Command(), _gameManager(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 2 cards." << std::endl;
		this->_gameManager->ForceDrawNextPhase(2);
	}
};