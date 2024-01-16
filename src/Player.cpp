#include <iostream>
#include <vector>
#include "headers/Player.h"
#include "headers/PlayableCard.h"

Player::Player(int id)
 : Id(id)
{}

// Only removes the desired card from the Player hand
// Make sure to add that card to the Discard Pile
void Player::Discard(PlayableCard& card)
{
	Hand.erase(Hand.begin() + card.PositionInHand());
	// Refresh position in hand for the cards
	for (int i = 0; i < Hand.size(); i++) {
		Hand[i].SetPositionInHand(i);
	}
}

void Player::Print() 
{
	std::cout << "Player: " << Id << std::endl;
}

void Player::PrintHand()
{
	for (PlayableCard& card : Hand)
	{
		std::cout << "[" << card.PositionInHand() << "] ";
		card.Print();
	}
}
