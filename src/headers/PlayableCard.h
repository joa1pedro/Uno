#pragma once
#include <string>
#include "Card.h"
#include "CardType.h"
#include "CardValue.h"
#include "IPrintable.h"

class PlayableCard : IPrintable {
public:
	// Constructors
	PlayableCard() = default;
	PlayableCard(int _id, CardType type, CardValue value);
	PlayableCard(Card card);

	CardType _typeOverride = CardType::Undefined; // Used for Wild Type purposes

	// Functions
	int Id();
	int PositionInHand();
	void Print();
	void SetPositionInHand(int position);
	void SetTypeOverride(CardType typeOverride);
	CardType GetType();
	CardType GetTypeOverride();
	CardValue GetValue();
private:
	void PrintType(CardType type);

	CardType _type = CardType::Undefined;
	CardValue _value = CardValue::Undefined;
	int _positionInHand = 0;
	int _id = -1;
	bool _isPlayable = false;
};
