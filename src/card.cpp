#include "card.h"

Card::Card()
{
    this->num = 0;
    this->suit = 'N';
}

void Card::Setcard(int num, char suit)
{
    this->num = num;
    this->suit = suit;
}
