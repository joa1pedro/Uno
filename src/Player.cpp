#include "Player.h"
#include "Card.h"

Player::Player(int id)
 : _id(id)
{}

std::vector<Card> Player::GetHand()
{
    return Player::_hand;
}

void Player::Draw(Deck& deck, int numCards /*= 1*/)
{
    // TODO Implement
}

void Player::Play(int cardIndex, Card& topCard)
{
    // Todo Implement
}
