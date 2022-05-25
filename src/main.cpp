#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

#define RSF 9
#define SF 8
#define FK 7
#define FH 6
#define F 5
#define S 4
#define TK 3
#define TP 2
#define OP 1

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
    
    for (int i = 0; i < 5; i++)
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
    for (int i = 0; i < 5; i++)
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
    if ((P == 5 || E == 5 || C == 5 || O == 5) && counter == 5)
    {
        if (vec[8] == 1)
        {
            return RSF;
        }
        else
        {
            return SF;
        }
    }
    if ((P == 5 || E == 5 || C == 5 || O == 5) && counter == 0)
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
    if (!(P == 5 || E == 5 || C == 5 || O == 5) && counter == 5)
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
        return FH;
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
void printArray(Card arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i].num << arr[i].suit << " ";
    cout << endl;
}

int main() {

    int n = 0, di = 0, j = 0, pin = 0, pote = 0, bet = 0;
    string name;

    Player table[8];
    Player semitable[8];
    Player nullplayer;

    ifstream inFile;

    for (int i = 0; i < 8; i++)
    {
        table[i] = nullplayer;
    }
    
    inFile.open("entrada.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    inFile >> n;
    inFile >> di;


    for (int i = 0; i < n; i++)
    {
        pote = 0;
        if (i == 0)
        {
            /* Set players and hands */
            inFile >> j;
            if (j < 2 && j >8)
            {
                cout << "Number of players invalid, please enter a number between 2 and 8" << endl;
                return 0;
            }
            inFile >> pin;

            for (int x = 0; x < j; x++)
            {
                Player p;
                inFile >> name;
                p.Setname(name);
                inFile >> bet;
                p.Setmoney(di - bet);
                pote += bet;

                Card card;
                int num;
                char suit;
                for (int z = 0; z < 5; z++)
                {
                    inFile >> num;
                    inFile >> suit;
                    card.Setcard(num, suit);
                    p.Setcardhand(card);
                }
                bubbleSort(p.hand, sizeof(p.hand)/sizeof(p.hand[0]));
                // printArray(p.hand, sizeof(p.hand)/sizeof(p.hand[0]));
                table[x] = p;
            }
            /* Set players and hands - END */

            /* See who wins */

            for (int x = 0; x < j; x++)
            {
                table[x].points = Ratehand(table[x].hand);
                cout << table[x].points << endl;
            }
            

            // for (int x = 0; x < j; x++)
            // {
            //     cout << table[x].Getname() << " " << table[x].Getmoney() << endl; 
            // }
            // cout << endl;

            /* See who wins - END */

            /* Reset the hands */
            for (int x = 0; x < j; x++)
            {
                Card card;
                for (int z = 0; z < 5; z++)
                {
                    table[x].Setcardhand(card);
                }
            }
            /* Reset the hands - END */

        }
        else
        {
            /* Set players hands */
            
            for (int f = 0; f < 8; f++)
            {
                semitable[f] = nullplayer;
            }
            int aux = 8;
            inFile >> j;
            if (j < 2 && j >8)
            {
                cout << "Number of players invalid, please enter a number between 2 and 8" << endl;
                return 0;
            }
            inFile >> pin;

            for (int k = 0; k < j; k++)
            {
                inFile >> name;
                for (int x = 0; x < aux; x++)
                {
                    if (table[x].Getname() == name)
                    {
                        inFile >> bet;
                        table[x].Setmoney(table[x].Getmoney() - bet);
                        pote += bet;

                        Card card;
                        int num;
                        char suit;
                        for (int z = 0; z < 5; z++)
                        {
                            inFile >> num;
                            inFile >> suit;
                            card.Setcard(num, suit);
                            table[x].Setcardhand(card);
                        }
                        semitable[k] = table[x];
                    }
                    else
                    {
                        table[x].Setmoney(table[x].Getmoney() - pin);
                        pote += pin;
                    }
                    
                    
                }
                
            }
            /* Set players hands - END */

            /* See who wins semitable */
            for (int x = 0; x < j; x++)
            {
                cout << semitable[x].Getname() << " " << semitable[x].Getmoney() << endl; 
            }
            cout << endl;

            /* See who wins semitable - END */

            /* Reset the hands */
            for (int x = 0; x < j; x++)
            {
                Card card;
                for (int z = 0; z < 5; z++)
                {
                    table[x].Setcardhand(card);
                }
            }
            /* Reset the hands - END */
        }

    }

    // int n, di, j, pin, pote = 0, bet, cardnum;
    // char cardsu;
    // string name;
    
    // ifstream inFile;
    // inFile.open("entrada.txt");
    // if (!inFile) {
    //     cout << "Unable to open file";
    //     exit(1); // terminate with error
    // }
    
    // inFile >> n;
    // inFile >> di;
    // inFile >> j;
    // inFile >> pin;
    // inFile >> name;
    // inFile >> bet;
    // pote += bet;
    // inFile >> cardnum;
    // inFile >> cardsu;

    // inFile.close();

    // cout << "Numero de rodadas: " << n << endl;
    // cout << "Dinheiro inicial: " << di << endl;
    // cout << "Numero de jogadores da rodada: " << j << endl;
    // cout << "Pingo minimo do pingo: " << pin << endl;
    // cout << "Nome do jogador: " << name << endl;
    // cout << "Aposta do jogador: " << bet << endl;
    // cout << "Numero da primeira carta: " << cardnum << endl;
    // cout << "Naipe da primeira carta: " << cardsu << endl;
    // cout << "Valor presente no pote: " << pote << endl;



    // Player p;
    // p.Setname("Chrystian");
    // p.Setmoney(1000000);
    // Card card;
    // int num;
    // char suit;
    // for (int i = 0; i < 5; i++)
    // {
    //     cin >> num;
    //     cin >> suit;
    //     card.Setcard(num, suit);
    //     p.Setcardhand(card);
    // }
    
    // cout << p.Getname() << endl;
    // cout << p.Getmoney() << endl;
    // for (int i = 0; i < 5; i++)
    // {
    //     cout << p.Getcardhand(i).num;
    //     cout << p.Getcardhand(i).suit << " ";
    // }
    // cout << endl;
    


    return 0;
}