#include "funcoes.h"

void RoundWinner(int origin, Player table[], Player semitable[], int *pote, int j)
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
    if (numwin == 1)
    {
        cout << numwin << " " << *pote << " " << Classification(semitable[winner].points);
        cout << semitable[winner].name << endl;
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
        cout << numwin << " " << gain << " " << Classification(semitable[winner].points);
        cout << semitable[winner].name;
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
                cout << semitable[x].name;
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
        cout << endl;
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


void SeeWhoWinF(Player table[], int *pote, int j)
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
            if (table[x].points > table[z].points)
            {
                winner = x;
            }
        }
    }

    for (int x = 0; x < j; x++)
    {
        if ((table[x].points == table[winner - 1].points) && (table[x].name != table[winner - 1].name))
        {
            numwin++;
        }
    }
    if (numwin == 1)
    {
        cout << numwin << " " << *pote << " " << Classification(table[winner - 1].points);
        cout << table[winner - 1].name << endl;
        table[winner-1].money += *pote;
    }
    if (numwin > 1)
    {
        int gain = (*pote/numwin);
        cout << numwin << " " << gain << " " << Classification(table[winner - 1].points);
        cout << table[winner - 1].name << endl;
        table[winner-1].money += gain;
        for (int x = 0; x < j; x++)
        {
            if ((table[x].points == table[winner - 1].points) && (table[x].name != table[winner - 1].name))
            {
                cout << table[x].name;
                table[x].money += gain;
            }
        }
    }
}

void TableSet(FILE * inFile, Player table[], char name[], int bet, int di, int pin , int *pote, int j)
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

int InvalidRound(Player table[], int pin, int di, int j)
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
        cout << 0 << " " << 0 << " " << "I" << endl;
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
            if ((arr[j].money < arr[j + 1].money) && (arr[j].name != "NULL") && (arr[j + 1].name != "NULL"))
                swap(arr[j], arr[j + 1]);
    
}
