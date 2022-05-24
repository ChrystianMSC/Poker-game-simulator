#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

int main() {

    int n = 0, di = 0, j = 0, pin = 0, pote = 0, bet = 0;
    string name;

    Player table[8];
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
                table[x] = p;
            }
            /* Set players and hands - END */

            /* See who wins */
            for (int x = 0; x < j; x++)
            {
                cout << table[x].Getname() << " " << table[x].Getmoney() << endl; 
            }
            cout << endl;

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
            Player semitable[8];
            for (int f = 0; f < 8; f++)
            {
                semitable[f] = nullplayer;
            }
            int aux = j;
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