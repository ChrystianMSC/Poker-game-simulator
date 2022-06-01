#include "../include/player.h"

using namespace std;
Player::Player()
{
    this->name = "NULL";
    this->money = 0;
    this->points = 0;
    this->contribuition = 0;
    Card card;
    for (int i = 0; i < SIZEH; i++)
    {
        this->hand[i] = card;
    }
    
}


void Player::Setcardhand(Card card)
{
    for (int i = 0; i < SIZEH; i++)
    {
        if (this->hand[i].num == 0)
        {
            this->hand[i] = card;
            break;
        }

    }
    
}

void Player::Resethand()
{
    for (int i = 0; i < SIZEH; i++)
    {
        Card card;
        this->hand[i] = card;
    }
    
}