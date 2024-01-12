#pragma once
#include <iostream>
#include "Command.h"

class DrawCommand : public Command {
private:
	int _cardNumber;

public:
	explicit DrawCommand(int cardNumber) 
		: _cardNumber(cardNumber) 
	{ }

	void Execute() const override 
	{
		std::cout << "Attempting to Draw: " << _cardNumber << " Cards.\n";
	}
};
