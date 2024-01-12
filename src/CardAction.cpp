#include <string>
#include <array>
#include "headers/CardAction.h"
#include "headers/Card.h"

bool IsValidActions(std::array<CardAction, MAX_ACTIONS_PER_CARD> actions)
{
	for (int i = 0; i < 3; i++) {
		if (actions[i] == CardAction::Undefined) {
			return false;
		}
	}
	return true;
}