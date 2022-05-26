#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

#define SIZET 8

#define RSF 9
#define SF 8
#define FK 7
#define FH 6
#define F 5
#define S 4
#define TK 3
#define TP 2
#define OP 1

string Classification(int n)
{
    switch (n)
    {
    case RSF:
        return "RSF";
    case SF:
        return "SF";
    case FK:
        return "FK";
    case FH:
        return "FH";
    case F:
        return "F";
    case S:
        return "S";
    case TK:
        return "TK";
    case TP:
        return "TP";
    case OP:
        return "OP";
    default:
        return "N";
    }
}

int Ratehand(Card arr[])
{
    int P = 0, E = 0, C = 0, O = 0;
    int quad = 0;
    int tri = 0;
    int two = 0;

    int vec[13];

    int counter = 0;

    for (int i = 0; i < 13; i++)
    {
        vec[i] = 0;
    }
    
    for (int i = 0; i < SIZEH; i++)
    {
        switch (arr[i].suit)
        {
        case 'P':
            P++;
            continue;
        case 'E':
            E++;
            continue;
        case 'C':
            C++;
            continue;
        case 'O':
            O++;
            continue;
        
        default:
        continue;
        }
    }
    for (int i = 0; i < SIZEH; i++)
    {
        vec[arr[i].num - 1]++;
    }
    for (int i = 0; i < 13; i++)
    {
        if (vec[i] == 0)
        {
            continue;
        }
        
        if (i == 12 && vec[i] == vec[i-1])
        {
            counter++;
        }
        if (vec[i] == vec[i+1])
        {
            counter++;
        }
        if (vec[i] != vec[i+1] && vec[i] == vec[i-1])
        {
            counter++;
        }
    }
    for (int i = 0; i < 13; i++)
    {
        if (vec[i] == 4)
        {
            quad++;
        }
        if (vec[i] == 3)
        {
            tri++;
        }
        if (vec[i] == 2)
        {
            two++;
        }
    }
    if ((P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter > 0)
    {
        if (vec[9] == 1)
        {
            return RSF;
        }
        else
        {
            return SF;
        }
    }
    if ((P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter == 0)
    {
        return F;
    }
    if (quad == 1)
    {
        return FK;
    }
    if (tri == 1 && two == 1)
    {
        return FH;
    }
    if (!(P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter >= SIZEH)
    {
        return S;
    }
    if (tri == 1 && two != 1)
    {
        return TK;
    }
    if (two == 2)
    {
        return TP;
    }
    if (tri == 0 && two == 1)
    {
        return OP;
    }
    return 0;
}

void bubbleSort(Card arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].num > arr[j + 1].num)
                swap(arr[j], arr[j + 1]);
    
}

void bubbleSortplayer(Player arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        for (j = 0; j < n - i - 1; j++)
            if (arr[j].Getmoney() < arr[j + 1].Getmoney())
                swap(arr[j], arr[j + 1]);
    
}

void printArray(Card arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i].num << arr[i].suit << " ";
    cout << endl;
}

int main() {

    int n = 0, di = 0, j = 0, pin = 0, pote = 0, bet = 0;
    int origin = 0;
    string name;

    Player nullplayer;

    Player table[SIZET];
    for (int i = 0; i < SIZET; i++)
    {
        table[i] = nullplayer;
    }
    
    Player semitable[SIZET];

    ifstream inFile;
    
    inFile.open("entrada.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }
    
    inFile >> n;
    inFile >> di;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            /* Set players, bet and hands --------------------------------------------------------------------------- */
            inFile >> j;
            origin = j;
            if (j < 2 && j >SIZET)
            {
                cout << "Number of players invalid, please enter a number between 2 and SIZET" << endl;
                return 0;
            }
            
            inFile >> pin;
            

            for (int x = 0; x < j; x++)
            {
                Player p;
                inFile >> name;
                p.Setname(name);
                inFile >> bet;
                p.Setmoney(di);
                p.Setmoney(p.Getmoney() - bet);
                p.Setmoney(p.Getmoney() - pin);
                pote += (bet + pin);

                Card card;
                int num;
                char suit;
                for (int z = 0; z < SIZEH; z++)
                {
                    inFile >> num;
                    inFile >> suit;
                    card.Setcard(num, suit);
                    p.Setcardhand(card);
                }
                bubbleSort(p.hand, sizeof(p.hand)/sizeof(p.hand[0]));
                p.points = Ratehand(p.hand);
                table[x] = p;
            }
            for (int x = 0; x < j; x++)
            {
                if (table[x].Getmoney() < 0)
                {
                    pin = di + 1;
                }
                
            }
            
            /* Set players and hands - END ---------------------------------------------------------------------- */


            /* See who wins ------------------------------------------------------------------------------------- */
            int winner = 0;
            int numwin = 1;

            for (int x = 0; x < j; x++)
            {
                for (int z = 0; z < j; z++)
                {
                    if (x == z)
                    {
                        continue;
                    }
                    if (table[x].points > table[z].points)
                    {
                        winner = x;
                    }
                }
            }
            for (int x = 0; x < j; x++)
            {
                if ((table[x].points == table[winner - 1].points) && (table[x].Getname() != table[winner - 1].Getname()))
                {
                    numwin++;
                }
                
            }
            if (pin > di)
            {
                for (int x = 0; x < j; x++)
                {
                    table[x].Setmoney(di);
                }
                cout << 0 << " " << 0 << " " << "I" << endl;
                continue;
            }

            if (numwin == 1)
            {
                cout << numwin << " " << pote << " " << Classification(table[winner - 1].points) << endl;
                cout << table[winner - 1].Getname() << endl;
                table[winner-1].Setmoney(table[winner-1].Getmoney() + pote);
            }
            if (numwin > 1)
            {
                cout << numwin << " " << pote/numwin << " " << Classification(table[winner - 1].points) << endl;
                cout << table[winner - 1].Getname() << endl;
                table[winner-1].Setmoney(table[winner-1].Getmoney() + (pote/numwin));
                for (int x = 0; x < j; x++)
                {
                    if ((table[x].points == table[winner - 1].points) && (table[x].Getname() != table[winner - 1].Getname()))
                    {
                        cout << table[x].Getname() << endl;
                        table[x].Setmoney(table[x].Getmoney() + (pote/numwin));
                    }
                }
            }

            /* See who wins - END ------------------------------------------------------------------------------- */


            /* Reset the hands ---------------------------------------------------------------------------------- */
            for (int x = 0; x < SIZET; x++)
            {
                table[x].Resethand();
            }
            /* Reset the hands - END ----------------------------------------------------------------------------- */


        }
        else
        {
            pote = 0;
            Player auxtable[SIZET];
            for (int x = 0; x < SIZET; x++)
            {
                auxtable[x] = table[x];
            }
            
            /* Set players hands --------------------------------------------------------------------------------- */
            
            for (int x = 0; x < SIZET; x++)
            {
                semitable[x] = nullplayer;
            }


            inFile >> j;

            if (j < 2 && j >SIZET)
            {
                cout << "Number of players invalid, please enter a number between 2 and SIZET" << endl;
                return 0;
            }
            inFile >> pin;
            

            for (int k = 0; k < j; k++)
            {
                inFile >> name;
                for (int x = 0; x < SIZET; x++)
                {
                    if (table[x].Getname() == name)
                    {
                        Player p = table[x];

                        inFile >> bet;
                        p.Setmoney(p.Getmoney() - bet);
                        if (p.Getmoney() < 0)
                        {
                            pin = di+1;
                        }
                        pote += bet;

                        Card card;
                        int num;
                        char suit;
                        for (int z = 0; z < SIZEH; z++)
                        {
                            inFile >> num;
                            inFile >> suit;
                            card.Setcard(num, suit);
                            p.Setcardhand(card);
                        }
                        bubbleSort(p.hand, sizeof(p.hand)/sizeof(p.hand[0]));

                        p.points = Ratehand(p.hand);
                        semitable[k] = p;
                        
                    }
                    else
                    {
                        
                        if (table[x].contribuition == 0 && table[x].Getname() != "NULL")
                        {
                            table[x].Setmoney(table[x].Getmoney() - pin);
                            table[x].contribuition = 1; 
                            pote += pin;
                        }
                        if (table[x].Getmoney() < 0)
                        {
                            pin = di+1;
                        }
                        
                    }
                    
                }
            }
            for (int x = 0; x < SIZET; x++)
            {
                table[x].contribuition = 0; 
            }
            if (pin > di)
            {
                for (int x = 0; x < j; x++)
                {
                    table[x] = auxtable[x];
                }
                cout << 0 << " " << 0 << " " << "I" << endl;
                continue;
            }
            
            /* Set players hands - END ---------------------------------------------------------------------------- */


            /* See who wins semitable ------------------------------------------------------------------------------- */
            int winner = 0;
            int numwin = 1;

            for (int x = 0; x < j; x++)
            {
                for (int z = 0; z < j; z++)
                {
                    if (x == z)
                    {
                        continue;
                    }
                    if (semitable[x].points > semitable[z].points)
                    {
                        winner = x;
                    }
                }
            }
            for (int x = 0; x < j; x++)
            {
                if ((semitable[x].points == semitable[winner].points) && (semitable[x].Getname() != semitable[winner].Getname()))
                {
                    numwin++;
                }
                
            }
            if (numwin == 1)
            {
                cout << numwin << " " << pote << " " << Classification(semitable[winner].points) << endl;
                cout << semitable[winner].Getname() << endl;
                semitable[winner].Setmoney(semitable[winner].Getmoney() + pote);
            }
            if (numwin > 1)
            {
                cout << numwin << " " << pote/numwin << " " << Classification(semitable[winner].points) << endl;
                cout << semitable[winner].Getname() << endl;
                semitable[winner].Setmoney(semitable[winner].Getmoney() + (pote/numwin));
                for (int x = 0; x < j; x++)
                {
                    if ((semitable[x].points == semitable[winner].points) && (semitable[x].Getname() != semitable[winner].Getname()))
                    {
                        cout << semitable[x].Getname() << endl;
                        semitable[x].Setmoney(semitable[winner].Getmoney() + (pote/numwin));
                    }
                }
            }
        
            /* See who wins semitable - END ------------------------------------------------------------------------ */


            /* Reset the hands ------------------------------------------------------------------------------------- */
            for (int x = 0; x < SIZET; x++)
            {
                table[x].Resethand();
            }
            /* Reset the hands - END--------------------------------------------------------------------------------- */

        }

    }
    bubbleSortplayer(table, sizeof(table)/sizeof(table[0]));
    cout << endl;
    cout << "####" << endl;
    for (int i = 0; i < origin; i++)
    {
        cout << table[i].Getname() << " " << table[i].Getmoney() << endl;
    }
    

    return 0;
}