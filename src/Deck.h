#pragma once
#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();
    void Shuffle();
    Card DrawCard();

private:
    std::vector<Card> cards;
};
