#pragma once
#include <string>

enum class CardType {
	Green,
	Blue,
	Yellow,
	Red,
	Wild
};

std::string CardTypeEnumToString(CardType type);
