#include "CardType.h"

std::string CardTypeEnumToString(CardType type)
{
	switch (type)
	{
	case CardType::Green:
		return "Green";
		break;
	case CardType::Blue:
		return "Blue";
		break;
	case CardType::Yellow:
		return "Yellow";
		break;
	case CardType::Red:
		return "Red";
		break;
	case CardType::Wild:
		return "Wild";
		break;
	default:
		return "Undefined";
		break;
	}
}
