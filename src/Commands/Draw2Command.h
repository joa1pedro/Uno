#pragma once

class Draw2Command : public Command {
private:
	GameManager* _gameManager;
	std::shared_ptr<Player> _player;

public:
	Draw2Command(GameManager* gameManager, std::shared_ptr<Player> player) :
		Command(), _gameManager(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 2 cards.\n";
		this->_gameManager->DrawForPlayer(_player, 2);
	}
};