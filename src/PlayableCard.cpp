#include <iostream>
#include "headers/PlayableCard.h"
#include "headers/color.hpp" // https://github.com/aafulei/color-console
#include "headers/CardUtils.h"

PlayableCard::PlayableCard(int id, CardType type, CardValue value)
	: _id(id), _type(type), _value(value)
{
}

PlayableCard::PlayableCard(Card card)
	: _id(card.Id()), _type(card._type), _value(card._value)
{
}

// Pattern: [_id] CardType(Colored) CardValue
void PlayableCard::Print()
{
	//Set to Color Type
	PrintType(_type);

	if (_typeOverride != CardType::Undefined) {
		std::cout << " " << CardUtils::ParseCardValueToStr(_value) << " [";
		PrintType(_typeOverride);
		std::cout << "]" << std::endl;
	}
	else {
		std::cout << " " << CardUtils::ParseCardValueToStr(_value) << std::endl;
	}
}

void PlayableCard::PrintType(CardType type) {
	switch (type)
	{
	case CardType::Green:
		std::cout << dye::green(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardType::Blue:
		std::cout << dye::blue(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardType::Yellow:
		std::cout << dye::yellow(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardType::Red:
		std::cout << dye::red(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardType::Wild:
		std::cout << dye::black_on_white(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardType::Undefined:
		std::cout << dye::vanilla(CardUtils::ParseCardTypeToStr(type));
		break;
	default:
		break;
	}
}

int PlayableCard::PositionInHand()
{
	return _positionInHand;
}

void PlayableCard::SetPositionInHand(int position)
{
	_positionInHand = position;
}

int PlayableCard::Id()
{
	return _id;
}

CardType PlayableCard::GetType() 
{
	return _type;
}

CardValue PlayableCard::GetValue()
{
	return _value;
}

CardType PlayableCard::GetTypeOverride()
{
	return _typeOverride;
}

void PlayableCard::SetTypeOverride(CardType typeOverride)
{
	_typeOverride = typeOverride;
}
