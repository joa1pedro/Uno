#pragma once
#include <iostream>
#include "Command.h"
#include "GameManager.h"
#include "Card.h"
#include "Player.h"

//class PlayCommand : public Command {
//private:
//    GameManager* _gameManager;
//    Card* _card;
//    Player* _player;
//
//public:
//    PlayCommand(GameManager* gameManager, Card* card, Player* player)
//        : _gameManager(gameManager), _card(card), _player(player)
//    { }
//
//    void Execute() const override {
//        std::cout << "Attempting to Play Card.\n";
//        this->_gameManager->ProcessCard(this->_card);
//        this->_gameManager->ProcessPlayer(this->_player);
//    }
//};