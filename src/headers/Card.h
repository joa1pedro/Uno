#pragma once
#include <array>
#include "CardType.h"
#include "CardAction.h"
#include "CardValue.h"
#include "Mediator.h"

int const MAX_ACTIONS_PER_CARD = 3;

// Class to be implemented with no complex Class members, only primitive types as a struct would be
// This allow us to save time without moving things, copies can be made easily.
class Card {
public:
	// Constructors
	Card() = default;
	Card(int _id, CardType type, CardValue value, std::array<CardAction, MAX_ACTIONS_PER_CARD> actions);

	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;

	// Functions
	int Id() const;
	std::array<CardAction, MAX_ACTIONS_PER_CARD> GetCardActions() const;
private:
	int _id = -1;
	std::array<CardAction, MAX_ACTIONS_PER_CARD> _actions = {
		CardAction::Undefined,
		CardAction::Undefined,
		CardAction::Undefined 
	};
	Mediator* mediator;
};
