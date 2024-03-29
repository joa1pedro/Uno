#include <unordered_map>
#include "headers/CardUtils.h"

const std::unordered_map<std::string, CardValue> CardUtils::cardValueStringToEnumMap = {
	{"0", CardValue::Zero},
	{"1", CardValue::One},
	{"2", CardValue::Two},
	{"3", CardValue::Three},
	{"4", CardValue::Four},
	{"5", CardValue::Five},
	{"6", CardValue::Six},
	{"7", CardValue::Seven},
	{"8", CardValue::Eight},
	{"9", CardValue::Nine},
	{"+2", CardValue::Plus2},
	{"Skip", CardValue::Skip},
	{"Reverse", CardValue::Reverse},
	{"+4", CardValue::Plus4},
	{"Wild", CardValue::Wild}
};

const std::unordered_map<CardValue, std::string> CardUtils::cardValueEnumToStringMap = {
	{CardValue::Zero, "0"},
	{CardValue::One, "1"},
	{CardValue::Two, "2"},
	{CardValue::Three, "3"},
	{CardValue::Four, "4"},
	{CardValue::Five, "5"},
	{CardValue::Six, "6"},
	{CardValue::Seven, "7"},
	{CardValue::Eight, "8"},
	{CardValue::Nine, "9"},
	{CardValue::Plus2, "+2"},
	{CardValue::Skip, "Skip"},
	{CardValue::Reverse, "Reverse"},
	{CardValue::Plus4, "+4"},
	{CardValue::Wild, "Wild"}
};

const std::unordered_map<std::string, CardColor> CardUtils::cardTypeStringToEnumMap = {
	{"yellow", CardColor::Yellow},
	{"blue", CardColor::Blue},
	{"green", CardColor::Green},
	{"red", CardColor::Red},
	{"wild", CardColor::Wild}
};

const std::unordered_map<CardColor, std::string> CardUtils::cardTypeEnumToStringMap = {
	{CardColor::Yellow, "yellow"},
	{CardColor::Blue, "blue"},
	{CardColor::Green, "green"},
	{CardColor::Red, "red"},
	{CardColor::Wild, "wild"}
};

const std::unordered_map<char, CardAction> CardUtils::cardActionCharToEnumMap = {
	{'D', CardAction::Default},
	{'+', CardAction::Plus2 },
	{'4', CardAction::Plus4 },
	{'S', CardAction::Skip },
	{'R', CardAction::Reverse},
	{'W', CardAction::Wild }
};

bool const CardUtils::HasMatchingType(const Card& selectedCard, const PlayableCard& lastDiscard)
{
	return selectedCard._color == lastDiscard.GetColor() || selectedCard._color == lastDiscard.GetTypeOverride();
}

bool const  CardUtils::HasMatchingValue(const Card& selectedCard, const PlayableCard& lastDiscard)
{
	return selectedCard._value == lastDiscard.GetValue();
}

bool const  CardUtils::HasMatchingTypeOrValue(const Card& selectedCard, const PlayableCard& lastDiscard) 
{
	return HasMatchingType(selectedCard, lastDiscard) || HasMatchingValue(selectedCard, lastDiscard);
}