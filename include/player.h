#include <iostream>
#include <string>
#include "deck.h"

#define SIZEH 5

#ifndef PLAYER
#define PLAYER

class Player{

    public:
        Card hand[5];
        int points;
        int contribuition;

        Player();
        void Setname(std::string name);
        void Setmoney(int money);
        void Setcardhand(Card card);
        void Resethand();
        std::string Getname();
        int Getmoney();
        Card Getcardhand(int i);
        
    private:
        std::string name;
        int money;
};

#endif