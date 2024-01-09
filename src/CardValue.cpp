#include "CardValue.h"
#include <string>

std::string ToString(CardValue cardValue) {
    switch (cardValue) {
    case CardValue::Zero: return "0";
    case CardValue::One: return "1";
    case CardValue::Two: return "2";
    case CardValue::Three: return "3";
    case CardValue::Four: return "4";
    case CardValue::Five: return "5";
    case CardValue::Six: return "6";
    case CardValue::Seven: return "7";
    case CardValue::Eight: return "8";
    case CardValue::Nine: return "9";
    case CardValue::Plus2: return "+2";
    case CardValue::Plus4: return "+4";
    case CardValue::Skip: return "Skip";
    case CardValue::Reverse: return "Reverse";
    default:
        return "Undefined";
    }
}

CardValue ParseCharToCardValue(char& character) {
    switch (character) {
    case '0': return CardValue::Zero;
    case '1': return CardValue::One;
    case '2': return CardValue::Two;
    case '3': return CardValue::Three;
    case '4': return CardValue::Four;
    case '5': return CardValue::Five;
    case '6': return CardValue::Six;
    case '7': return CardValue::Seven;
    case '8': return CardValue::Eight;
    case '9': return CardValue::Nine;
    case '+': return CardValue::Plus2;
    case 'S': return CardValue::Skip;
    case 'R': return CardValue::Reverse;
    case 'W': return CardValue::Plus4;
    default:
        return CardValue::Undefined;
    }
}
