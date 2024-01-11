#pragma once
#include <string>
#include <vector>
#include "CardType.h"
#include "CardAction.h"
#include "CardValue.h"
#include "IPrintable.h"

class Card : IPrintable {
public:
	// Constructors
	Card() {};
	Card(std::string _id, CardType type, CardValue value, std::vector<CardAction> actions);

	// Functions
	std::string Id();
	int PositionInHand();
	void Print();

private:
	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;
	std::string _id = "";
	std::vector<CardAction> _actions {};
	bool _isPlayable = false;
	int _positionInHand = 0;
};
