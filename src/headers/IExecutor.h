#pragma once
#include <memory>
#include "Player.h"

class IExecutor {
public:
	virtual void PlayCard(std::shared_ptr<Player> playerPtr, PlayableCard card) = 0;
	virtual void DrawForPlayer(std::shared_ptr<Player> player) = 0;

	virtual int  PassTurn() = 0;
	virtual void InvertGameOrder() = 0;
	virtual void ForceDrawNextPhase(int numberOfCards, bool canBeChallenged) = 0;
};

