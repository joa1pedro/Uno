#pragma once

class PlayCardCommand : public Command {
private:
	PlayableCard _card;
	std::shared_ptr<GameManager> _gameManager;
	std::shared_ptr<Player> _player;

public:
	PlayCardCommand(std::shared_ptr<GameManager> gameManager, std::shared_ptr<Player> player, PlayableCard card, CardType typeOverride = CardType::Undefined) :
		Command(), _card(card), _gameManager(gameManager), _player(player)
	{ }

	void Execute() const override {
		std::cout << "[Command] Playing Card." << std::endl;
		this->_gameManager->PlayCard(_player, _card);
	}
};