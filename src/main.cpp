#include <iostream>
#include <fstream>
#include "player.h"

using namespace std;

int main() {

    int n, di, j, pin, pote, bet;
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
        if (i == 0)
        {
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
                    cin >> num;
                    cin >> suit;
                    card.Setcard(num, suit);
                    p.Setcardhand(card);
                }
                table[j] = p;
            }

        }
        else
        {
            int aux = j;
            inFile >> j;
            if (j < 2 && j >8)
            {
                cout << "Number of players invalid, please enter a number between 2 and 8" << endl;
                return 0;
            }
            inFile >> pin;

            for (int i = 0; i < aux; i++)
            {
                inFile >> name;
            }
            
            
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