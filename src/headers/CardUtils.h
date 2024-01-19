#pragma once
#include <unordered_map>
#include "CardValue.h"
#include "CardType.h"
#include "CardAction.h"
#include "PlayableCard.h"
#include "Card.h"

class CardUtils {
public:
	static CardValue ParseStrToCardValue(const std::string& str) {
		return ParseStringToEnum<CardValue>(str, cardValueStringToEnumMap);
	}

	static std::string ParseCardValueToStr(CardValue value) {
		return ParseEnumToString<CardValue>(value, cardValueEnumToStringMap);
	}

	static CardType ParseStrToCardType(const std::string& str) {
		return ParseStringToEnum<CardType>(str, cardTypeStringToEnumMap);
	}

	static std::string ParseCardTypeToStr(CardType type) {
		return ParseEnumToString<CardType>(type, cardTypeEnumToStringMap);
	}

	static CardAction ParseCharToCardAction(char& c) {
		return ParseCharToEnum<CardAction>(c, cardActionCharToEnumMap);
	}

	// Card Comparison. Matches the Card with PlayableCard if it has same CardValue, CardType or TypeOverride
	static const bool IsValidCard(const Card& selectedCard, const PlayableCard& lastDiscard) ;

	// Compares the selected card Type or TypeOverride with the last discard.
	static const bool HasMatchingType(const Card& selectedCard, const PlayableCard& lastDiscard) ;

	// Compares the selected card Value with the last discard
	static const bool HasMatchingValue(const Card& selectedCard, const PlayableCard& lastDiscard) ;

private:
	// Helper templates to make conversions using a lookup tables
	template <typename T>
	static T ParseStringToEnum(const std::string& str, const std::unordered_map<std::string, T>& stringToEnumMap) {
		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end()) {
			return it->second;
		}
		return T::Undefined;
	}

	template <typename T>
	static std::string ParseEnumToString(T value, const std::unordered_map<T, std::string>& enumToStringMap) {
		auto it = enumToStringMap.find(value);
		if (it != enumToStringMap.end()) {
			return it->second;
		}
		return "Undefined";
	}

	template <typename T>
	static T ParseCharToEnum(char& c, const std::unordered_map<char, T>& charToEnumMap) {
		auto it = charToEnumMap.find(c);
		if (it != charToEnumMap.end()) {
			return it->second;
		}
		return T::Undefined;
	}

	// Static member variables containing the mappings
	static const std::unordered_map<std::string, CardValue> cardValueStringToEnumMap;
	static const std::unordered_map<std::string, CardType> cardTypeStringToEnumMap;
	static const std::unordered_map<CardValue, std::string> cardValueEnumToStringMap;
	static const std::unordered_map<CardType, std::string> cardTypeEnumToStringMap;
	static const std::unordered_map<char, CardAction> cardActionCharToEnumMap;
};
