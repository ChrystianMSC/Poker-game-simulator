#include <iostream>
#include <string>
#include "deck.h"

#ifndef PLAYER
#define PLAYER

class Player{

    public:
        Card hand[5];
        int points;

        Player();
        void Setname(std::string name);
        void Setmoney(int money);
        void Setcardhand(Card card);
        std::string Getname();
        int Getmoney();
        Card Getcardhand(int i);
        
    private:
        std::string name;
        int money;
};

#endif