#include "player.h"
#include <string>

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

#ifndef FUNCOES
#define FUNCOES

string Classification(int n);
int Ratehand(Card arr[]);
void bubbleSort(Card arr[], int n);
void bubbleSortplayer(Player arr[], int n);
int InvalidRound(Player table[], int pin, int di, int j);
void TableSet(FILE * inFile, Player table[], char name[], int bet, int di, int pin , int *pote, int j);
void SeeWhoWinF(Player table[], int *pote, int j);
void RoundSet(FILE *inFile, int bet, Player *p, int *pote, int *pin, int di);
void RoundWinner(int origin, Player table[], Player semitable[], int *pote, int j);

#endif