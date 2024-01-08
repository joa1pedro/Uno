#pragma once
#include <string>
#include <vector>
#include "CardType.h"
#include "CardAction.h"
#include "CardValue.h"

class Card {
public:
	Card(CardType type, CardValue value);
	int GetPositionInHand();

private:
	int _id;
	CardType _type;
	CardValue _value = CardValue::Undefined;
	std::vector<CardAction> _actions; 
	bool _isPlayable = false;
	int _positionInHand;
};
