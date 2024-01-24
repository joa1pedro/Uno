#include <iostream>
#include <fstream>
#include <string>
#include "headers/PlayableCard.h"
#include "headers/color.hpp" // https://github.com/aafulei/color-console
#include "headers/CardUtils.h"
#include "headers/IOHelper.h"

const std::string ASCII_ART_PATH = "./ascii/";

PlayableCard::PlayableCard(int id, CardColor type, CardValue value)
	: _id(id), _color(type), _value(value)
{}

PlayableCard::PlayableCard(Card card)
	: _id(card.Id()), _color(card._color), _value(card._value)
{}

void PlayableCard::Print() const
{
	//Set to Color Type
	PrintType(_color);

	if (_colorOverride != CardColor::Undefined) {
		std::cout << " " << CardUtils::ParseCardValueToStr(_value) << " [";
		PrintType(_colorOverride);
		std::cout << "]" << std::endl;
	}
	else {
		std::cout << " " << CardUtils::ParseCardValueToStr(_value) << std::endl;
	}
}

void PlayableCard::PrintType(CardColor type) const {
	switch (type)
	{
	case CardColor::Green:
		std::cout << dye::green(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardColor::Blue:
		std::cout << dye::blue(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardColor::Yellow:
		std::cout << dye::yellow(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardColor::Red:
		std::cout << dye::red(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardColor::Wild:
		std::cout << dye::black_on_white(CardUtils::ParseCardTypeToStr(type));
		break;
	case CardColor::Undefined:
		std::cout << dye::vanilla(CardUtils::ParseCardTypeToStr(type));
		break;
	default:
		break;
	}
}

void PlayableCard::PrintFromFile() const {
	std::string type;
	if (this->GetColor() == CardColor::Wild){
		type = CardUtils::ParseCardTypeToStr(this->GetTypeOverride());
	}
	else {
		type = CardUtils::ParseCardTypeToStr(this->GetColor());
	}

	std::string value = CardUtils::ParseCardValueToStr(this->GetValue());

	std::string asciiPath = ASCII_ART_PATH;
	std::ifstream file(asciiPath.append(value).append(".txt"));

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << asciiPath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::cout << dye::colorize(line, IOHelper::ToLowerCase(type)) << std::endl;
	}

	file.close();
}

int PlayableCard::PositionInHand() const
{
	return _positionInHand;
}

void PlayableCard::SetPositionInHand(int position)
{
	_positionInHand = position;
}

int PlayableCard::Id() const
{ 
	return _id;
}

CardColor PlayableCard::GetColor() const
{
	return _color;
}

CardValue PlayableCard::GetValue() const
{
	return _value;
}

CardColor PlayableCard::GetTypeOverride() const
{
	return _colorOverride;
}

void PlayableCard::SetTypeOverride(CardColor typeOverride)
{
	_colorOverride = typeOverride;
}
