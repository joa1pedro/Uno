#pragma once
#include <string>

enum class CardType {
	Green,
	Blue,
	Yellow,
	Red,
	Wild,
	Undefined
};

std::string ToString(CardType cardValue);
CardType ParseCharToCardType(char& character);