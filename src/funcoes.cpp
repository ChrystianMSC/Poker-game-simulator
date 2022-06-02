#include "../include/funcoes.h"


int InvalidRounds(int pin, int di, int origin, Player table[], Player auxtable[], ofstream& outFile)
{
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
        return 1;
    }
    return 0;
}

void ResetHand(Player table[])
{
    for (int x = 0; x < SIZET; x++)
    {
        table[x].Resethand();
    }
}

void InitRound(FILE* inFile, ofstream& outFile, int *j, int *pin, int *di)
{
    fscanf(inFile, "%d", j);
    if (*j < 2 || *j >SIZET)
    {
        outFile << "Number of players invalid, please enter a number between 2 and SIZET" << endl;
        exit(1);
    }

    fscanf(inFile, "%d", pin);
    if (*pin < 1 || *pin > *di)
    {
        outFile << "Pingo is invalid, pingo most be a number greater than 0 and less than di" << endl;
        exit(1);
    }
}

int InitGame(FILE *inFile, ofstream &outFile, int *n,int *di,int *j,int *pin)
{
    int origin = 0;
    fscanf(inFile, "%d", n);
    if (*n < 1)
    {
        outFile << "Invalid number of rounds" << endl;
        exit(1);
    }

    fscanf(inFile, "%d", di);
    if (*di < 1)
    {
        outFile << "Invalid initial money" << endl;
        exit(1);
    }
    fscanf(inFile, "%d", j);
            
    if (*j < 2 || *j >SIZET)
    {
        outFile << "Number of players invalid, please enter a number between 2 and 8" << endl;
        exit(1);
    }
    
    origin = *j;
            
    fscanf(inFile, "%d", pin);
    if (*pin < 1 || *pin > *di)
    {
        outFile << "Pingo is invalid, pingo most be a number greater than 0 and less than di" << endl;
        exit(1);
    }
    return origin;
}

void RoundWinner(int origin, Player table[], Player semitable[], int *pote, int j, ofstream& outFile)
{
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
        if ((semitable[x].points == semitable[winner].points) && (semitable[x].name != semitable[winner].name))
        {
            numwin++;
        }
    }

    if (numwin > 1)
    {
        int quad1 = 0;
        int quad2 = 0;
        int card1 = 0;
        int card2 = 0;

        int pair1 = 0;
        int pair2 = 0;

        int tri1 = 0;
        int tri2 = 0;
        int cards1 = 0;
        int cards2 = 0;

        int par11 = 0;
        int par12 = 0;
        int par21 = 0;
        int par22 = 0;
        int single1 = 0;
        int single2 = 0;

        int par1 = 0;
        int par2 = 0;

        switch (semitable[winner].points)
        {
            case RSF:
                break;
            case SF:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                            if (semitable[i].hand[4].num > semitable[winner].hand[4].num)
                            {
                                semitable[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (semitable[i].hand[4].num < semitable[winner].hand[4].num)
                            {
                                semitable[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case FK:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        int x = 0;
                        if (x == 0 && semitable[winner].hand[x+1].num != semitable[winner].hand[x].num)
                        {
                            quad1 = 1; 
                        }
                        else
                        {
                            card1 = 4;
                        }
                        if (x == 0 && semitable[i].hand[x+1].num != semitable[i].hand[x].num)
                        {
                            quad2 = 1;
                        }
                        else
                        {
                            card2 = 4;
                        }
                    }
                    if (semitable[i].hand[quad2].num > semitable[winner].hand[quad1].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (semitable[i].hand[quad2].num < semitable[winner].hand[quad1].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                    }
                    if (semitable[i].hand[quad2].num == semitable[winner].hand[quad1].num)
                    {
                        if (semitable[i].hand[card2].num > semitable[winner].hand[card1].num)
                        {
                            semitable[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (semitable[i].hand[card2].num < semitable[winner].hand[card1].num)
                        {
                            semitable[i].points = 0;
                            numwin--;
                        }
                        
                    }
                }
                break;
            case FH:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        
                            if ((semitable[winner].hand[0].num == semitable[winner].hand[1].num) && (semitable[winner].hand[0].num == semitable[winner].hand[2].num))
                            {
                                pair1 = 3;
                            }
                            else
                            {
                                tri1 = 2;
                            }
                            if ((semitable[i].hand[0].num == semitable[i].hand[1].num) && (semitable[i].hand[0].num == semitable[i].hand[2].num))
                            {
                                pair2 = 3;
                            }
                            else
                            {
                                tri2 = 2;
                            }
                    }
                    if (semitable[i].hand[tri2].num > semitable[winner].hand[tri1].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (semitable[i].hand[tri2].num < semitable[winner].hand[tri1].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                    }
                    if (semitable[i].hand[tri2].num == semitable[winner].hand[tri1].num)
                    {
                        if (semitable[i].hand[pair2].num > semitable[winner].hand[pair1].num)
                        {
                            semitable[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (semitable[i].hand[pair2].num < semitable[winner].hand[pair1].num)
                        {
                            semitable[i].points = 0;
                            numwin--;
                        }
                        
                    }
                }
                break;
            case F:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                            if (semitable[i].hand[4].num > semitable[winner].hand[4].num)
                            {
                                semitable[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (semitable[i].hand[4].num < semitable[winner].hand[4].num)
                            {
                                semitable[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case S:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                            if (semitable[i].hand[4].num > semitable[winner].hand[4].num)
                            {
                                semitable[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (semitable[i].hand[4].num < semitable[winner].hand[4].num)
                            {
                                semitable[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case TK:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        
                            if ((semitable[winner].hand[0].num == semitable[winner].hand[1].num) && (semitable[winner].hand[0].num == semitable[winner].hand[2].num))
                            {
                                cards1 = 3;
                            }
                            else
                            {
                                tri1 = 2;
                            }
                            if ((semitable[i].hand[0].num == semitable[i].hand[1].num) && (semitable[i].hand[0].num == semitable[i].hand[2].num))
                            {
                                cards2 = 3;
                            }
                            else
                            {
                                tri2 = 2;
                            }
                    }
                    if (semitable[i].hand[tri2].num > semitable[winner].hand[tri1].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (semitable[i].hand[tri2].num < semitable[winner].hand[tri1].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                    }
                    if (semitable[i].hand[tri2].num == semitable[winner].hand[tri1].num)
                    {
                        if (semitable[i].hand[cards2].num > semitable[winner].hand[cards1].num || semitable[i].hand[cards2 + 1].num > semitable[winner].hand[cards1 + 1].num)
                        {
                            semitable[winner].points = 0;
                            winner = i;
                            numwin--;
                            continue;
                        }
                        if (semitable[i].hand[cards2].num < semitable[winner].hand[cards1].num || semitable[i].hand[cards2 + 1].num < semitable[winner].hand[cards1 + 1].num)
                        {
                            semitable[i].points = 0;
                            numwin--;
                            continue;
                        }
                    }
                }
                break;
            case TP:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        
                            if ((semitable[winner].hand[2].num != semitable[winner].hand[1].num) && (semitable[winner].hand[2].num != semitable[winner].hand[3].num))
                            {
                                single1 = 2;
                                par11 = 0;
                                par12 = 3;
                            }
                            else if ((semitable[winner].hand[0].num != semitable[winner].hand[1].num))
                            {
                                par11 = 1;
                                par12 = 3;
                            }
                            else
                            {
                                single1 = 4;
                                par11 = 0;
                                par12 = 2;
                            }
                            if ((semitable[i].hand[2].num != semitable[i].hand[1].num) && (semitable[i].hand[2].num != semitable[i].hand[3].num))
                            {
                                single2 = 2;
                                par11 = 0;
                                par12 = 3;
                            }
                            else if ((semitable[i].hand[0].num != semitable[i].hand[1].num))
                            {
                                par11 = 1;
                                par12 = 3;
                            }
                            else
                            {
                                single2 = 4;
                                par11 = 0;
                                par12 = 2;
                            }
                            
                    }
                    if (semitable[i].hand[par21].num > semitable[winner].hand[par11].num && semitable[i].hand[par21].num > semitable[winner].hand[par12].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    else if (semitable[i].hand[par22].num > semitable[winner].hand[par11].num && semitable[i].hand[par22].num > semitable[winner].hand[par12].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    if (semitable[i].hand[par21].num < semitable[winner].hand[par11].num && semitable[i].hand[par21].num < semitable[winner].hand[par12].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                        continue;
                    }
                    else if (semitable[i].hand[par22].num < semitable[winner].hand[par11].num && semitable[i].hand[par22].num < semitable[winner].hand[par12].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                        continue;
                    }
                    if (semitable[i].hand[single2].num > semitable[winner].hand[single1].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    if (semitable[i].hand[single2].num < semitable[winner].hand[single1].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                        continue;
                    }
                }
                break;
            case OP:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        for (int x = 0; x < 5; x++)
                        {
                            if (semitable[winner].hand[x].num == semitable[winner].hand[x+1].num)
                            {
                                par1 = x;
                            }
                            if (semitable[i].hand[x].num == semitable[i].hand[x+1].num)
                            {
                                par2 = x;
                            }   
                        }
                    }
                    if (semitable[i].hand[par2].num > semitable[winner].hand[par1].num)
                    {
                        semitable[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (semitable[i].hand[par2].num < semitable[winner].hand[par1].num)
                    {
                        semitable[i].points = 0;
                        numwin--;
                    }
                    if (semitable[i].hand[par2].num == semitable[winner].hand[par1].num)
                    {
                        int maior1 = 0;
                        int maior2 = 0;
                        for (int x = 0; x < 5; x++)
                        {
                            if (semitable[winner].hand[x].num > semitable[winner].hand[maior1].num && semitable[winner].hand[x].num != semitable[winner].hand[par1].num)
                            {
                                maior1 = x;
                            }
                        }
                        for (int x = 0; x < 5; x++)
                        {
                            if (semitable[i].hand[x].num > semitable[i].hand[maior1].num && semitable[i].hand[x].num != semitable[i].hand[par2].num)
                            {
                                maior2 = x;
                            }
                        }
                        if (semitable[i].hand[maior2].num > semitable[winner].hand[maior1].num)
                        {
                            semitable[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (semitable[i].hand[maior2].num < semitable[winner].hand[maior1].num)
                        {
                            semitable[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                    }
                }
                break;
            default:
                for (int i = 0; i < j; i++)
                {
                    if ((semitable[i].points == semitable[winner].points) && (semitable[i].name != semitable[winner].name))
                    {
                        for (int x = 0; x < 5; x++)
                        {
                            if (semitable[i].hand[x].num > semitable[winner].hand[x].num)
                            {
                                semitable[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (semitable[i].hand[x].num < semitable[winner].hand[x].num)
                            {
                                semitable[i].points = 0;
                                numwin--;
                            }
                        }
                    }
                }
                break;
        }
    
    }


    if (numwin <= 1)
    {
        outFile << 1 << " " << *pote << " " << Classification(semitable[winner].points);
        outFile << semitable[winner].name << endl;
        semitable[winner].money += *pote;
        for (int x = 0; x < origin; x++)
        {
            if (table[x].name == semitable[winner].name)
            {
            
                table[x] = semitable[winner];
            }  
        }
    }
    if (numwin > 1)
    {
        int gain = (*pote/numwin);
        outFile << numwin << " " << gain << " " << Classification(semitable[winner].points);
        outFile << semitable[winner].name;
        semitable[winner].money += gain;
        for (int x = 0; x < origin; x++)
        {
            if (table[x].name == semitable[winner].name)
            {
                table[x].money = semitable[winner].money;
            }  
        }
        for (int x = 0; x < j; x++)
        {
            if ((semitable[x].points == semitable[winner].points) && (semitable[x].name != semitable[winner].name))
            {
                outFile << semitable[x].name;
                semitable[x].money += gain;
                for (int z = 0; z < origin; z++)
                {
                    if (table[z].name == semitable[x].name)
                    {
                        table[z].money = semitable[x].money;
                    }  
                }
            }
        }
        outFile << endl;
    }
}

void RoundSet(FILE *inFile, int bet, Player *p, int *pote, int *pin, int di)
{
    bet = 0;
    fscanf(inFile, "%d", &bet);
    p->money -= bet;

    if (p->money < 0)
    {
        *pin = di+1;
    }
    *pote += bet;

    Card card;
    int num;
    char suit;

    for (int z = 0; z < SIZEH; z++)
    {
        fscanf(inFile, "%d", &num);
        fscanf(inFile, "%c", &suit);
        card.Setcard(num, suit);
        p->Setcardhand(card);
    }

    bubbleSort(p->hand, sizeof(p->hand)/sizeof(p->hand[0]));
    p->points = Ratehand(p->hand);
}

void SeeWhoWinF(Player table[], int *pote, int j, ofstream& outFile)
{
    int winner = 0;
    int numwin = 1;

    for (int x = 0; x < j; x++)
    {
        if (table[winner].points < table[x].points)
        {
            winner = x;
            numwin = 1;
        }
        if ((table[x].points == table[winner].points) && (table[x].name != table[winner].name))
        {
            numwin++;
        }
    }
    if (numwin > 1)
    {
        int quad1 = 0;
        int quad2 = 0;
        int card1 = 0;
        int card2 = 0;

        int pair1 = 0;
        int pair2 = 0;

        int tri1 = 0;
        int tri2 = 0;
        int cards1 = 0;
        int cards2 = 0;

        int par11 = 0;
        int par12 = 0;
        int par21 = 0;
        int par22 = 0;
        int single1 = 0;
        int single2 = 0;

        int par1 = 0;
        int par2 = 0;

        switch (table[winner].points)
        {
            case RSF:
                break;
            case SF:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                            if (table[i].hand[4].num > table[winner].hand[4].num)
                            {
                                table[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (table[i].hand[4].num < table[winner].hand[4].num)
                            {
                                table[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case FK:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        int x = 0;
                        if (x == 0 && table[winner].hand[x+1].num != table[winner].hand[x].num)
                        {
                            quad1 = 1; 
                        }
                        else
                        {
                            card1 = 4;
                        }
                        if (x == 0 && table[i].hand[x+1].num != table[i].hand[x].num)
                        {
                            quad2 = 1;
                        }
                        else
                        {
                            card2 = 4;
                        }
                    }
                    if (table[i].hand[quad2].num > table[winner].hand[quad1].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (table[i].hand[quad2].num < table[winner].hand[quad1].num)
                    {
                        table[i].points = 0;
                        numwin--;
                    }
                    if (table[i].hand[quad2].num == table[winner].hand[quad1].num)
                    {
                        if (table[i].hand[card2].num > table[winner].hand[card1].num)
                        {
                            table[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (table[i].hand[card2].num < table[winner].hand[card1].num)
                        {
                            table[i].points = 0;
                            numwin--;
                        }
                        
                    }
                }
                break;
            case FH:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        
                            if ((table[winner].hand[0].num == table[winner].hand[1].num) && (table[winner].hand[0].num == table[winner].hand[2].num))
                            {
                                pair1 = 3;
                            }
                            else
                            {
                                tri1 = 2;
                            }
                            if ((table[i].hand[0].num == table[i].hand[1].num) && (table[i].hand[0].num == table[i].hand[2].num))
                            {
                                pair2 = 3;
                            }
                            else
                            {
                                tri2 = 2;
                            }
                    }
                    if (table[i].hand[tri2].num > table[winner].hand[tri1].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (table[i].hand[tri2].num < table[winner].hand[tri1].num)
                    {
                        table[i].points = 0;
                        numwin--;
                    }
                    if (table[i].hand[tri2].num == table[winner].hand[tri1].num)
                    {
                        if (table[i].hand[pair2].num > table[winner].hand[pair1].num)
                        {
                            table[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (table[i].hand[pair2].num < table[winner].hand[pair1].num)
                        {
                            table[i].points = 0;
                            numwin--;
                        }
                        
                    }
                }
                break;
            case F:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                            if (table[i].hand[4].num > table[winner].hand[4].num)
                            {
                                table[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (table[i].hand[4].num < table[winner].hand[4].num)
                            {
                                table[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case S:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                            if (table[i].hand[4].num > table[winner].hand[4].num)
                            {
                                table[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (table[i].hand[4].num < table[winner].hand[4].num)
                            {
                                table[i].points = 0;
                                numwin--;
                            }
                    }
                }
                break;
            case TK:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        
                            if ((table[winner].hand[0].num == table[winner].hand[1].num) && (table[winner].hand[0].num == table[winner].hand[2].num))
                            {
                                cards1 = 3;
                            }
                            else
                            {
                                tri1 = 2;
                            }
                            if ((table[i].hand[0].num == table[i].hand[1].num) && (table[i].hand[0].num == table[i].hand[2].num))
                            {
                                cards2 = 3;
                            }
                            else
                            {
                                tri2 = 2;
                            }
                    }
                    if (table[i].hand[tri2].num > table[winner].hand[tri1].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (table[i].hand[tri2].num < table[winner].hand[tri1].num)
                    {
                        table[i].points = 0;
                        numwin--;
                    }
                    if (table[i].hand[tri2].num == table[winner].hand[tri1].num)
                    {
                        if (table[i].hand[cards2].num > table[winner].hand[cards1].num || table[i].hand[cards2 + 1].num > table[winner].hand[cards1 + 1].num)
                        {
                            table[winner].points = 0;
                            winner = i;
                            numwin--;
                            continue;
                        }
                        if (table[i].hand[cards2].num < table[winner].hand[cards1].num || table[i].hand[cards2 + 1].num < table[winner].hand[cards1 + 1].num)
                        {
                            table[i].points = 0;
                            numwin--;
                            continue;
                        }
                    }
                }
                break;
            case TP:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        
                            if ((table[winner].hand[2].num != table[winner].hand[1].num) && (table[winner].hand[2].num != table[winner].hand[3].num))
                            {
                                single1 = 2;
                                par11 = 0;
                                par12 = 3;
                            }
                            else if ((table[winner].hand[0].num != table[winner].hand[1].num))
                            {
                                par11 = 1;
                                par12 = 3;
                            }
                            else
                            {
                                single1 = 4;
                                par11 = 0;
                                par12 = 2;
                            }
                            if ((table[i].hand[2].num != table[i].hand[1].num) && (table[i].hand[2].num != table[i].hand[3].num))
                            {
                                single2 = 2;
                                par11 = 0;
                                par12 = 3;
                            }
                            else if ((table[i].hand[0].num != table[i].hand[1].num))
                            {
                                par11 = 1;
                                par12 = 3;
                            }
                            else
                            {
                                single2 = 4;
                                par11 = 0;
                                par12 = 2;
                            }
                            
                    }
                    if (table[i].hand[par21].num > table[winner].hand[par11].num && table[i].hand[par21].num > table[winner].hand[par12].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    else if (table[i].hand[par22].num > table[winner].hand[par11].num && table[i].hand[par22].num > table[winner].hand[par12].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    if (table[i].hand[par21].num < table[winner].hand[par11].num && table[i].hand[par21].num < table[winner].hand[par12].num)
                    {
                        table[i].points = 0;
                        numwin--;
                        continue;
                    }
                    else if (table[i].hand[par22].num < table[winner].hand[par11].num && table[i].hand[par22].num < table[winner].hand[par12].num)
                    {
                        table[i].points = 0;
                        numwin--;
                        continue;
                    }
                    if (table[i].hand[single2].num > table[winner].hand[single1].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                        continue;
                    }
                    if (table[i].hand[single2].num < table[winner].hand[single1].num)
                    {
                        table[i].points = 0;
                        numwin--;
                        continue;
                    }
                }
                break;
            case OP:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        for (int x = 0; x < 5; x++)
                        {
                            if (table[winner].hand[x].num == table[winner].hand[x+1].num)
                            {
                                par1 = x;
                            }
                            if (table[i].hand[x].num == table[i].hand[x+1].num)
                            {
                                par2 = x;
                            }   
                        }
                    }
                    if (table[i].hand[par2].num > table[winner].hand[par1].num)
                    {
                        table[winner].points = 0;
                        winner = i;
                        numwin--;
                    }
                    if (table[i].hand[par2].num < table[winner].hand[par1].num)
                    {
                        table[i].points = 0;
                        numwin--;
                    }
                    if (table[i].hand[par2].num == table[winner].hand[par1].num)
                    {
                        int maior1 = 0;
                        int maior2 = 0;
                        for (int x = 0; x < 5; x++)
                        {
                            if (table[winner].hand[x].num > table[winner].hand[maior1].num && table[winner].hand[x].num != table[winner].hand[par1].num)
                            {
                                maior1 = x;
                            }
                        }
                        for (int x = 0; x < 5; x++)
                        {
                            if (table[i].hand[x].num > table[i].hand[maior1].num && table[i].hand[x].num != table[i].hand[par2].num)
                            {
                                maior2 = x;
                            }
                        }
                        if (table[i].hand[maior2].num > table[winner].hand[maior1].num)
                        {
                            table[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                        if (table[i].hand[maior2].num < table[winner].hand[maior1].num)
                        {
                            table[winner].points = 0;
                            winner = i;
                            numwin--;
                        }
                    }
                }
                break;
            default:
                for (int i = 0; i < j; i++)
                {
                    if ((table[i].points == table[winner].points) && (table[i].name != table[winner].name))
                    {
                        for (int x = 0; x < 5; x++)
                        {
                            if (table[i].hand[x].num > table[winner].hand[x].num)
                            {
                                table[winner].points = 0;
                                winner = i;
                                numwin--;
                            }
                            if (table[i].hand[x].num < table[winner].hand[x].num)
                            {
                                table[i].points = 0;
                                numwin--;
                            }
                        }
                    }
                }
                break;
        }
    }

    if (numwin <= 1)
    {
        outFile << 1 << " " << *pote << " " << Classification(table[winner].points);
        outFile << table[winner].name << endl;
        table[winner].money += *pote;
    }
    if (numwin > 1)
    {
        int gain = (*pote/numwin);
        outFile << numwin << " " << gain << " " << Classification(table[winner].points);
        outFile << table[winner].name;
        table[winner].money += gain;
        for (int x = 0; x < j; x++)
        {
            if ((table[x].points == table[winner].points) && (table[x].name != table[winner].name))
            {
                outFile << table[x].name << endl;
                table[x].money += gain;
            }
        }
    }
}

void FirstTableSet(FILE * inFile, Player table[], char name[], int bet, int di, int pin , int *pote, int j)
{
    for (int x = 0; x < j; x++)
    {
        Player p;
        fscanf(inFile, "%[^0-9]", name);
        fscanf(inFile, "%d", &bet);
        p.name = name;
        p.money = di;
        p.money -= bet;
        p.money -= pin;
        *pote += bet;
        *pote += pin;

        Card card;

        int num;
        char suit;

        for (int z = 0; z < SIZEH; z++)
        {
            fscanf(inFile, "%d", &num);
            fscanf(inFile, "%c", &suit);
            card.Setcard(num, suit);
            p.Setcardhand(card);
        }

        bubbleSort(p.hand, sizeof(p.hand)/sizeof(p.hand[0]));
        p.points = Ratehand(p.hand);
        
        table[x] = p;
    }
}

int InvalidFirstRound(Player table[], int pin, int di, int j, ofstream& outFile)
{
    for (int x = 0; x < j; x++)
    {
        if (table[x].money < 0)
        {
            pin = di + 1;
        }
    }
    if (pin > di)
    {
        for (int x = 0; x < j; x++)
        {
            table[x].money = di;
        }
        outFile << 0 << " " << 0 << " " << "I" << endl;
        return 1;
    }
    return 0;
}

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
        return "HC";
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
            continue;
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
    if ((P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter == 4)
    {
        if (vec[0] == 1)
        {
            return RSF;
        }
    }
    if ((P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter == 5)
    {
        return SF;
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
    if (!(P == SIZEH || E == SIZEH || C == SIZEH || O == SIZEH) && counter > 4)
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
            if ((arr[j].money < arr[j + 1].money) && (arr[j].name != "NULL") && (arr[j + 1].name != "NULL"))
                swap(arr[j], arr[j + 1]);
    
}
