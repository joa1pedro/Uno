#include <iostream>
#include "Card.h"
#include "color.hpp" // https://github.com/aafulei/color-console

Card::Card(std::string id, CardType type, CardValue value)
: _id(id), _type(type), _value(value)
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
		std::cout << dye::green(ToString(_type));
		break;
	case CardType::Blue:
		std::cout << dye::blue(ToString(_type));
		break;
	case CardType::Yellow:
		std::cout << dye::yellow(ToString(_type));
		break;
	case CardType::Red:
		std::cout << dye::red(ToString(_type));
		break;
	case CardType::Wild:
		std::cout << dye::black_on_white(ToString(_type));
		break;
	case CardType::Undefined:
		std::cout << dye::vanilla(ToString(_type));
		break;
	default:
		break;
	}

	std::cout << " " << ToString(_value) << std::endl;
}

int Card::GetPositionInHand()
{
    return Card::_positionInHand;
}

std::string Card::GetId() 
{
    return _id;
}

CardType Card::GetType()
{
	return _type;
}

CardValue Card::GetValue()
{
	return _value;
}
