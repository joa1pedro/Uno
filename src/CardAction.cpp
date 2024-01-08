#include "CardAction.h"

std::string CardActionEnumToString(CardAction action)
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
