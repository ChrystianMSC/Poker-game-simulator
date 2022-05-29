#include <iostream>
#include <string>
#include "deck.h"

#define SIZEH 5

#ifndef PLAYER
#define PLAYER

class Player{

    public:
        Player();

        Card hand[5];
        int points;
        int contribuition;
        int money;
        std::string name;

        void Setcardhand(Card card);
        void Resethand();

};

#endif