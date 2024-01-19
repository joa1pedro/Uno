#include <iostream>
#include "headers/Card.h"
#include "headers/CardUtils.h"

Card::Card(int id, CardType type, CardValue value, std::array<CardAction, MAX_ACTIONS_PER_CARD> actions)
: _id(id), _type(type), _value(value), _actions(actions)
{
}

std::array<CardAction, MAX_ACTIONS_PER_CARD> Card::GetCardActions() const
{
	return _actions;
}

int Card::Id() const
{
    return _id;
}