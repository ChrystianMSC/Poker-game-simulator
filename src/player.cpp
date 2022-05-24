#include "player.h"

Player::Player()
{
    this->name = "NULL";
    this->money = 0;
    Card card;
    for (int i = 0; i < 5; i++)
    {
        this->hand[i] = card;
    }
    
}

void Player::Setname(string name)
{
    this->name = name;
}

void Player::Setmoney(int money)
{
    this->money = money;
}

void Player::Setcardhand(Card card)
{
    for (int i = 0; i < 5; i++)
    {
        if (this->hand[i].num == 0)
        {
            this->hand[i] = card;
            break;
        }

    }
    
}

string Player::Getname()
{
    return this->name;
}

int Player::Getmoney()
{
    return this->money;
}

Card Player::Getcardhand(int i)
{
    return this->hand[i];
}