#include "deck.h"


Deck::Deck()
{
    Card card;
    int count = 1;
    for (int i = 0; i < SETC; i++)
    {
        if (i < 13)
        {
            card.Setcard(count, 'P');
            deck[i] = card;
            count++;
            continue;
        }
        count = 1;

        if (i > 12 && i < 26)
        {
            card.Setcard(count, 'E');
            deck[i] = card;
            count++;
            continue;
        }
        count = 1;

        if (i > 26 && i < 39)
        {
            card.Setcard(count, 'C');
            deck[i] = card;
            count++;
            continue;
        }

        count = 1;

        if (i > 39 && i < SETC)
        {
            card.Setcard(count, 'O');
            deck[i] = card;
            count++;
            continue;
        }
        
    }
    
}