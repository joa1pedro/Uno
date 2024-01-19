#pragma once
#include <array>
#include "CardType.h"
#include "CardAction.h"
#include "CardValue.h"
#include "Mediator.h"

int const MAX_ACTIONS_PER_CARD = 3;

class Card {
public:
	Card() = default;
	Card(int _id, CardType type, CardValue value, std::array<CardAction, MAX_ACTIONS_PER_CARD> actions);

	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;

	//Returns the ID of this card
	int Id() const;

	// Returns an array of CardActions for this Card
	std::array<CardAction, MAX_ACTIONS_PER_CARD> GetCardActions() const;
private:
	int _id = -1;
	std::array<CardAction, MAX_ACTIONS_PER_CARD> _actions = {
		CardAction::Undefined,
		CardAction::Undefined,
		CardAction::Undefined 
	};
};
