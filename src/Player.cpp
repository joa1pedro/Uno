#include "Player.h"
#include "Card.h"
#include "GameState.h" // For the for forward declaration on player.h


Player::Player(int id)
 : _id(id)
{}

std::vector<Card> Player::GetHand()
{
    return Player::_hand;
}

int Player::CardsInHand()
{
    return Player::_hand.size();
}

