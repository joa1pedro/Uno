#include <iostream>
#include <vector>
#include "headers/Player.h"
#include "headers/PlayableCard.h"
#include "headers/IOHelper.h"
#include "headers/color.hpp" // https://github.com/aafulei/color-console

Player::Player(int id)
 : Id(id)
{}

void Player::Discard(PlayableCard card)
{
	Hand.erase(Hand.begin() + card.PositionInHand());
	// Refresh position in hand for the cards
	for (int i = 0; i < Hand.size(); i++) {
		Hand[i].SetPositionInHand(i);
	}
}

void Player::Print() const
{
	if (CurrentlyPlaying) {
		std::cout << "[";
		std::cout << dye::blue("Player: ");
		std::cout << dye::blue(Id);
		std::cout << "]";
	}
	else {
		std::cout << "Player: " << Id;
	}
}

void Player::PrintHand() const
{
	for (const PlayableCard& card : Hand)
	{
		std::cout << "[" << card.PositionInHand() << "] ";
		card.Print();
	}
}
