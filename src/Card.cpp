#include <iostream>
#include "headers/Card.h"
#include "headers/color.hpp" // https://github.com/aafulei/color-console
#include "headers/CardUtils.h"

Card::Card(int id, CardType type, CardValue value, std::array<CardAction, MAX_ACTIONS_PER_CARD> actions)
: _id(id), _type(type), _value(value), _actions(actions)
{
}

// Pattern: [_id] CardType(Colored) CardValue
void Card::Print()
{
	std::cout << "[" << _id << "] ";

	//Set to Color Type
	switch (_type)
	{
	case CardType::Green:
		std::cout << dye::green(CardUtils::ParseCardTypeToStr(_type));
		break;
	case CardType::Blue:
		std::cout << dye::blue(CardUtils::ParseCardTypeToStr(_type));
		break;
	case CardType::Yellow:
		std::cout << dye::yellow(CardUtils::ParseCardTypeToStr(_type));
		break;
	case CardType::Red:
		std::cout << dye::red(CardUtils::ParseCardTypeToStr(_type));
		break;
	case CardType::Wild:
		std::cout << dye::black_on_white(CardUtils::ParseCardTypeToStr(_type));
		break;
	case CardType::Undefined:
		std::cout << dye::vanilla(CardUtils::ParseCardTypeToStr(_type));
		break;
	default:
		break;
	}

	std::cout << " " << CardUtils::ParseCardValueToStr(_value) << std::endl;
}

int Card::PositionInHand()
{
    return _positionInHand;
}

int Card::Id() 
{
    return _id;
}
