#include "struct.c"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define dx 0
#define sx 1

//  "menu.c"

void menu();

void soloGame();

void aiGame();

void challenge();


//  "nodeFunction.c"

node* createHand();

tessera createTessera();

tessera createTesseraValue(int, int);

node* removeTessera(node*, int);

node* addToField(node*, tessera, int);


//  "print.c"

void printNodes(node*);

void printHand(node*);

void printField(node*);

int printPossibleMoves(node*);


//  "util.c"

bool isValidMove(node*, tessera, int);

tessera peekHand(node*, int);

bool checkFine(node*, node*);

int contaPunti(node*);

tessera swapTessera(tessera);


//  "challenge.c"

result resolveChallenge(node*, tessera, result);


//  "ai.c"

int findBestMove(node*, node*, int);
