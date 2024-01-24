#pragma once
#include <string>
#include "Card.h"
#include "CardType.h"
#include "CardValue.h"
#include "IPrintable.h"

// Class to be implemented with no complex Class members, only primitive types as a struct would be
// This allow us to save time without moving things, copies can be made easily.
class PlayableCard : IPrintable {
public:
	PlayableCard() = default;
	PlayableCard(int id, CardColor color, CardValue value);
	PlayableCard(Card card);

	//Returns this card ID
	int Id() const;

	//Returns this card position in the hand
	int PositionInHand() const;

	// Pattern: [_id] CardColor(Colored) CardValue
	void Print() const;

	//Sets where this card is in the hand of the player
	void SetPositionInHand(int position);

	//Sets the type override for this card. Used for Wild Cards
	void SetTypeOverride(CardColor typeOverride);

	//Returns this card type
	CardColor GetColor() const;

	//Returns this card type override. Undefined if theres no override
	CardColor GetTypeOverride() const;

	//Returns this card value
	CardValue GetValue() const;

	//Prints this card using the ASCII file
	void PrintFromFile() const;
private:
	// Prints this card Type using colors
	void PrintType(CardColor type) const;

	CardColor _color = CardColor::Undefined;
	CardValue _value = CardValue::Undefined;
	CardColor _colorOverride = CardColor::Undefined;

	int _positionInHand = 0;
	int _id = -1;
};
