#pragma once
#include <string>
#include <vector>
#include "CardType.h"
#include "CardAction.h"
#include "CardValue.h"
#include "IPrintable.h"
#include <array>

int const MAX_ACTIONS_PER_CARD = 3;

// Class to be implemented with no complex Class members, only primitive types as a struct would be
// This allow us to save time without moving things, copies can be made easily.
class Card : IPrintable {
public:
	// Constructors
	Card() = default;
	Card(int _id, CardType type, CardValue value, std::array<CardAction, MAX_ACTIONS_PER_CARD> actions);

	// Functions
	int Id();
	int PositionInHand();
	void Print();

private:
	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;
	int _id = -1;
	std::array<CardAction, MAX_ACTIONS_PER_CARD> _actions = {
		CardAction::Undefined,
		CardAction::Undefined,
		CardAction::Undefined 
	};
	bool _isPlayable = false;
	int _positionInHand = 0;
};
