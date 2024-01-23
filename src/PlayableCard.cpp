#include <iostream>
#include <fstream>
#include <string>
#include "headers/PlayableCard.h"
#include "headers/color.hpp" // https://github.com/aafulei/color-console
#include "headers/CardUtils.h"

PlayableCard::PlayableCard(int id, CardType type, CardValue value)
	: _id(id), _type(type), _value(value)
{}

PlayableCard::PlayableCard(Card card)
	: _id(card.Id()), _type(card._type), _value(card._value)
{}

void PlayableCard::Print() const
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

void PlayableCard::PrintType(CardType type) const {
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

void PlayableCard::PrintFromFile() const {
	std::string filename = "./ascii/";

	std::string type = CardUtils::ParseCardTypeToStr(this->GetType());
	std::string value = CardUtils::ParseCardValueToStr(this->GetValue());

	std::ifstream file(filename.append(value).append(".txt"));

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;

	std::string result = type;
	for (char& c : result) {
		c = std::tolower(c);
	}

	while (std::getline(file, line)) {
		std::string result = type;
		std::cout << dye::colorize(line, result) << std::endl;
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

CardType PlayableCard::GetType() const
{
	return _type;
}

CardValue PlayableCard::GetValue() const
{
	return _value;
}

CardType PlayableCard::GetTypeOverride() const
{
	return _typeOverride;
}

void PlayableCard::SetTypeOverride(CardType typeOverride)
{
	_typeOverride = typeOverride;
}
