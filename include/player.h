#include <iostream>
#include <string>
#include "deck.h"

using namespace std;

#ifndef PLAYER
#define PLAYER

class Player{

    public:
        Player();
        void Setname(string name);
        void Setmoney(int money);
        void Setcardhand(Card card);
        string Getname();
        int Getmoney();
        Card Getcardhand(int i);
    private:
        string name;
        int money;
        Card hand[5];
};

#endif