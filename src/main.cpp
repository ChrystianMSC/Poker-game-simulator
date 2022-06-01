#include <iostream>
#include <stdio.h>
#include <fstream>
#include <regex.h>
#include "player.h"
#include "funcoes.h"

int main() {

    int n = 0, di = 0, j = 0, pin = 0, pote = 0, bet = 0, origin = 0;
    char name [20];

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
    
    fscanf(inFile, "%d", &n);
    if (n < 1)
    {
        outFile << "Invalid number of rounds" << endl;
        return 0;
    }

    fscanf(inFile, "%d", &di);
    if (di < 1)
    {
        outFile << "Invalid initial money" << endl;
        return 0;
    }
    fscanf(inFile, "%d", &j);
            
    if (j < 2 || j >SIZET)
    {
        outFile << "Number of players invalid, please enter a number between 2 and 8" << endl;
        return 0;
    }
    
    origin = j;
            
    fscanf(inFile, "%d", &pin);
    if (pin < 1 || pin > di)
    {
        outFile << "Pingo is invalid, pingo most be a number greater than 0 and less than di" << endl;
        return 0;
    }

    /* GAME */

    for (int i = 0; i < n; i++)
    {
        /* -------------------------------------------------------------- FIRST ROUND ----------------------------------------------------------------------------- */
        if (i == 0)
        {   
            if (j < 2 && j >SIZET)
            {
                outFile << "Number of players invalid, please enter a number between 2 and 8" << endl;
                break;
            }
            TableSet(inFile, table, name, bet, di, pin, &pote, j);
            
            int inv = InvalidRound(table, pin, di, j, outFile);
            if (inv == 1)
            {
                continue;
            }

            SeeWhoWinF(table, &pote, j, outFile);
            
            for (int x = 0; x < SIZET; x++)
            {
                table[x].Resethand();
            }
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

            fscanf(inFile, "%d", &j);
            if (j < 2 || j >SIZET)
            {
                cout << "Number of players invalid, please enter a number between 2 and SIZET" << endl;
                return 0;
            }

            fscanf(inFile, "%d", &pin);
            if (pin < 1 || pin > di)
            {
                cout << "Pingo is invalid, pingo most be a number greater than 0 and less than di" << endl;
                return 0;
            }

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
            
            if (pin > di)
            {
                for (int x = 0; x < origin; x++)
                {
                    for (int z = 0; z < origin; z++)
                    {
                        if (table[x].name == auxtable[z].name && table[x].money != auxtable[z].money)
                        {
                            table[x].money = auxtable[z].money;
                        }
                    }
                }
                outFile << 0 << " " << 0 << " " << "I" << endl;
                continue;
            }

            RoundWinner(origin, table, semitable, &pote, j, outFile);

            for (int x = 0; x < SIZET; x++)
            {
                table[x].Resethand();
            }
            
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