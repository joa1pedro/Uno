#pragma once

class DrawCommand : public Command {
private:
	std::shared_ptr<GameManager> _gameManager;
	std::shared_ptr<Player> _player;

public:
	DrawCommand(std::shared_ptr<GameManager> gameManager, std::shared_ptr<Player> player) :
		Command(), _gameManager(gameManager), _player(player)
	{}

	void Execute() const override {
		std::cout << "[Command] Draw 1 Card.\n" << std::endl;;
		this->_gameManager->DrawForPlayer(_player, 1);
	}
};
