#include "CardType.h"
#include <string>

std::string ToString(CardType cardType) {
    switch (cardType) {
    case CardType::Green: return "Green";
    case CardType::Blue: return "Blue";
    case CardType::Yellow: return "Yellow";
    case CardType::Red: return "Red";
    case CardType::Wild: return "Wild";
    default:
        return "Unknown";
    }
}

CardType ParseCharToCardType(char& character) {
	switch (character)
	{
	case ('y'): return CardType::Yellow;
	case ('Y'): return CardType::Yellow;

	case ('b'): return CardType::Blue;
	case ('B'): return CardType::Blue;

	case ('g'): return CardType::Green;
	case ('G'): return CardType::Green;

	case ('r'): return CardType::Red;
	case ('R'): return CardType::Red;

	case ('w'): return CardType::Wild;
	case ('W'): return CardType::Wild;
	default:
		return CardType::Undefined;
		break;
	}
}
