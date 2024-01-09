#pragma once
#include <string>

enum class CardValue {
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Plus2,
	Plus4,
	Skip,
	Reverse,
	Undefined
};

std::string ToString(CardValue cardValue);
CardValue ParseCharToCardValue(char& character);