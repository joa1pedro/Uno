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
	Card(std::string _id, CardType type, CardValue value);

	// Functions
	int GetPositionInHand();
	std::string GetId();
	CardType GetType();
	CardValue GetValue();
	void Print();

private:
	std::string _id = "";
	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;
	std::vector<CardAction> _actions {};
	bool _isPlayable = false;
	int _positionInHand = 0;
};
