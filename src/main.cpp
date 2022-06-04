#include <iostream>
#include <stdio.h>
#include <fstream>
#include <regex.h>
#include "../include/player.h"
#include "../include/funcoes.h"


int main() {

    int n = 0, di = 0, j = 0, pin = 0, pote = 0, bet = 0, origin = 0;
    char name [256];

    Player nullplayer;
    Player table[SIZET];
    Player semitable[SIZET];
    
    FILE *inFile;
    ofstream outFile;

    outFile.open("saida.txt");
    inFile = fopen("entrada.txt", "r");

    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    for (int i = 0; i < SIZET; i++)
    {
        table[i] = nullplayer;
    }
    
    origin = InitGame(inFile, outFile, &n, &di, &j, &pin);

    /* GAME */

    for (int i = 0; i < n; i++)
    {
        /* -------------------------------------------------------------- FIRST ROUND ----------------------------------------------------------------------------- */
        if (i == 0)
        {   
            FirstTableSet(inFile, table, name, bet, di, pin, &pote, j);
            
            int inv = InvalidFirstRound(table, pin, di, j, outFile);

            if (inv == 1)
            {
                continue;
            }

            SeeWhoWinF(table, &pote, j, outFile);
            ResetHand(table);
        }
        /* ----------------------------------------------------------- FIRST ROUND - END -------------------------------------------------------------------------- */
 
        /* ---------------------------------------------------------------- ROUNDS -------------------------------------------------------------------------------- */
        else
        {
            pote = 0;

            Player auxtable[SIZET];
            for (int x = 0; x < SIZET; x++)
            {
                auxtable[x] = table[x];
            }
            
            for (int x = 0; x < SIZET; x++)
            {
                semitable[x] = nullplayer;
            }

            InitRound(inFile, outFile, &j, &pin, &di);

            for (int x = 0; x < origin; x++)
            {
                if (table[x].name != "NULL")
                {
                    table[x].money -= pin;
                    pote += pin;
                }
            }

            for (int k = 0; k < j; k++)
            {
                fscanf(inFile, "%[^0-9]", name);
                for (int x = 0; x < origin; x++)
                {
                    if (table[x].name == name)
                    {
                        
                        Player p = table[x];
                        RoundSet(inFile, bet, &p, &pote, &pin, di);
                        semitable[k] = p;
                        table[x] = p;
                    }
                }
            }

            if (InvalidRounds(pin, di, origin, table, auxtable, outFile))
            {
                continue;
            }
        
            RoundWinner(origin, table, semitable, &pote, j, outFile);
            ResetHand(table);
            
        }
        /* ---------------------------------------------------------------- ROUNDS - END -------------------------------------------------------------------------------- */

    }

    /* GAME END  */

    bubbleSortplayer(table, sizeof(table)/sizeof(table[0]));

    outFile << endl;
    outFile << "####";

    for (int i = 0; i < origin; i++)
    {
        outFile << table[i].name << " " << table[i].money;
    }

    outFile << endl;

    outFile.close();
    fclose(inFile);

    return 0;
}