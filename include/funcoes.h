#include "player.h"
#include <string>
#include <fstream>

using namespace std;

#define SIZET 20

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


int InvalidFirstRound(Player table[], int pin, int di, int j, ofstream& outFile);
int InvalidRounds(int pin, int di, int origin, Player table[], Player auxtable[], ofstream& outFile);

int InitGame(FILE *inFile, ofstream &outFile, int *n,int *di,int *j,int *pin);
void InitRound(FILE* inFile, ofstream& outFile, int *j, int *pin, int *di);

void FirstTableSet(FILE * inFile, Player table[], char name[], int bet, int di, int pin , int *pote, int j);
void RoundSet(FILE *inFile, int bet, Player *p, int *pote, int *pin, int di);

void SeeWhoWinF(Player table[], int *pote, int j, ofstream& outFile);
void RoundWinner(int origin, Player table[], Player semitable[], int *pote, int j, ofstream& outFile);

void ResetHand(Player table[]);

#endif