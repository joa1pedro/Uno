#pragma once

class PlayCardCommand : public Command {
private:
	PlayableCard* _card;
	GameManager* _gameManager;
	Player* _player;

public:
	PlayCardCommand(GameManager* gameManager, Player* player, PlayableCard* card, CardType typeOverride = CardType::Undefined) :
		Command(), _card(card), _gameManager(gameManager), _player(player)
	{ }

	void Execute() const override {
		std::cout << "Attempting to Play Card Command.\n";
		this->_gameManager->PlayCard(_player, _card);
	}
};