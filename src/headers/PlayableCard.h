#pragma once
#include <string>
#include "Card.h"
#include "CardType.h"
#include "CardValue.h"
#include "IPrintable.h"

class PlayableCard : IPrintable {
public:
	PlayableCard() = default;
	PlayableCard(int _id, CardType type, CardValue value);
	PlayableCard(Card card);

	//Returns this card ID
	int Id() const;

	//Returns this card position in the hand
	int PositionInHand() const;

	// Pattern: [_id] CardType(Colored) CardValue
	void Print() const;

	//Sets where this card is in the hand of the player
	void SetPositionInHand(int position);

	//Sets the type override for this card. Used for Wild Cards
	void SetTypeOverride(CardType typeOverride);

	//Returns this card type
	CardType GetType() const;

	//Returns this card type override. Undefined if theres no override
	CardType GetTypeOverride() const;

	//Returns this card value
	CardValue GetValue() const;
private:
	// Prints this card Type using colors
	void PrintType(CardType type) const;

	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;
	CardType _typeOverride = CardType::Undefined;

	int _positionInHand = 0;
	int _id = -1;
};
