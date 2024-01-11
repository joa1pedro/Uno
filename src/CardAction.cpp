#include <string>
#include <vector>
#include "headers/CardAction.h"

bool IsValidActions(std::vector<CardAction>& actions)
{
	for (CardAction cardAction : actions) {
		if (cardAction == CardAction::Undefined) {
			return false;
		}
	}
	return true;
}