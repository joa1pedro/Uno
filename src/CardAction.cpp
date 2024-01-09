#include "CardAction.h"
#include <string>

std::string ToString(CardAction action)
{
	switch (action)
	{
	case CardAction::Default:
		return "";
		break;
	case CardAction::Plus2:
		return "+2";
		break;
	case CardAction::Skip:
		return "Skip";
		break;
	case CardAction::Reverse:
		return "Reverse;";
		break;
	default:
		return "Undefined";
		break;
	}
}
