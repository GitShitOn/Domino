#include "struct.c"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define dx 0
#define sx 1
#define AI_LIMIT 999

//  "menu.c"

void menu();

void soloGame();

void aiGame();

void challenge();


//  "nodeFunction.c"

node* createHand();

node* createHandChallenge();

tessera createTessera();

tessera createTesseraValue(int, int);

node* removeTessera(node*, int);

node* addToField(node*, tessera, int);

node* copyNodes(node*);

void free_nodes(node*);


//  "print.c"

void printNodes(node*);

void printText(node*, char*);

void printHand(node*);

void printField(node*);

void printStartingHand(node*);

int printPossibleMoves(node*);

void printMossa(move);

void print_debug();


//  "util.c"

bool isValidMove(node*, tessera, int);

tessera peekHand(node*, int);

bool checkFine(node*, node*);

int contaPunti(node*);

tessera swapTessera(tessera);

int valoreTessera(tessera);

int contaHand(node*);


//  "challenge.c"

result resolveChallenge(node*, tessera, result);

move findBestMoveChallenge(node*, node*, int);


//  "ai.c"

move findBestMove(node*, node*, int);

move makeCurrentMove(tessera, int, int ,int);

int calcMove(node*, node*, move);
