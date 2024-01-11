#include <unordered_map>
#include "headers/CardUtils.h"

// Initialize the static member variables outside the class definition
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
	{"+4", CardValue::Plus4}
};


// Initialize the static member variables outside the class definition
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
	{CardValue::Plus4, "+4"}
};


const std::unordered_map<std::string, CardType> CardUtils::cardTypeStringToEnumMap = {
	{"Yellow", CardType::Yellow},
	{"Blue", CardType::Blue},
	{"Green", CardType::Green},
	{"Red", CardType::Red},
	{"Wild", CardType::Wild}
};

const std::unordered_map<CardType, std::string> CardUtils::cardTypeEnumToStringMap = {
	{CardType::Yellow, "Yellow"},
	{CardType::Blue, "Blue"},
	{CardType::Green, "Green"},
	{CardType::Red, "Red"},
	{CardType::Wild, "Wild"}
};

const std::unordered_map<char, CardAction> CardUtils::cardActionCharToEnumMap = {
	{'D', CardAction::Default},
	{'+', CardAction::Plus2 },
	{'S', CardAction::Skip },
	{'R', CardAction::Reverse }
};