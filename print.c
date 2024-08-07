#include "function.h"

// Stampa le tessere, utilizzata per debug principalemnte
void printNodes(node* hand) {
    printf("\n");
    while(hand != NULL) {
        printCard(hand);
        // printf("[%d(%d/%d)|%d(%d/%d)] ", hand->me.l_cell,hand->me.pos[0],hand->me.pos[1], hand->me.r_cell,hand->me.pos[2],hand->me.pos[3]);           // print debug posizioni
        hand = hand->next;
    }
    printf("\n");
}

//  test print formattato
int printCard(node* hand) {
    if(!hand)
        return 0;
    switch(hand->me.l_cell) {
        case jolly:
            printf("[J|J]");
            break;
        case plus_one:
            printf("[Field +1]");
            break;
        case mirror_l:
            printf("[Mirror]");
            break;
        default:
            printf("[%d|%d]", hand->me.l_cell, hand->me.r_cell);
            // printf("[%d(%d/%d)|%d(%d/%d)] ", hand->me.l_cell,hand->me.pos[0],hand->me.pos[1], hand->me.r_cell,hand->me.pos[2],hand->me.pos[3]);           // print debug posizioni
    }
    return 5;
}

int printHalfCard(node* hand, bool top) {
    switch(hand->me.l_cell) {
        case jolly:
            if(top)
                printf("[J:");
            else
                printf(":J]");
            break;
        default:
            if(top)
                printf("[%d:", hand->me.l_cell);
            else
                printf(":%d]", hand->me.r_cell);

    }
    return 3;
}

int recursivePrintLineForward(node* n, int cursPoint) {
    if(n) {
        cursPoint += printCard(n);
        recursivePrintLineForward(n->next, cursPoint);
    }
    return cursPoint;
}
int recursivePrintLineReverse(node* n, int cursPoint) {
    if(n) 
       recursivePrintLineReverse(n->next, cursPoint);
    for(int i = 0; i < n->me.pos[1]; i++)
        printf(" ");
    return cursPoint + printCard(n); 
    
} 

int recursivePrint(node* n, int depth) {
    node* head = n;
    bool end = true;
    int cursPoint = 0;
    while(n) {
        if(n->me.pos[0] != n->me.pos[2]) {
            if(n->me.pos[2] == depth) {
                cursPoint = recursivePrintLineReverse(n->down_l, cursPoint);
                printHalfCard(n, false);
                cursPoint += 3;
                cursPoint = recursivePrintLineForward(n->down_r, cursPoint);
            }
            else {
                printHalfCard(n, true);
                cursPoint += 3;
                end = false;
            }
        }
        else if(n->me.pos[0] == depth) {
            cursPoint += printCard(n);
        }
        n = n->next;
    }
    printf("\n");
    if(end)
        return depth;
    return recursivePrint(head, depth+1);
}

// Stampa il campo
int printField(node* field) {
    printf("\n%s", "Tavolo attuale\n");
    return recursivePrint(field, 0);
}

void printText(node* nodes, char* str) {
    printf("\n%s", str);
    printNodes(nodes);
}

void printHand(node* hand) {
    printText(hand, "La tua mano:");
}

void printStartingHand(node* hand) {
    printText(hand, "La tua mano di partenza");
}

// stampa la mano (fancy)
int printPossibleMoves(node* hand) {
    int count = 0;
        printf("\nScegli la tessera che vuoi giocare");

        while(hand != NULL) {
            count++;
            printf("\n%d - ", count);
            printCard(hand);
            // printf("\n%d - [%d|%d]", count, hand->me.l_cell, hand->me.r_cell);
            switch(hand->me.l_cell) {
                case jolly:
                    printf("\t(Jolly!)");
                    break;
                case plus_one:
                    printf("\t(Aumenta di 1 il valore di tutte le tessere sul campo) (es.:[3|6]->[4|1])");
                    break;
                case mirror_l:
                    printf("\t(Specchia la carta più esterna dal lato che viene giocata)");
                    break;
            }
            hand = hand->next;
        }
        printf("\n\nScelta: ");

    return count;     
}

void printMossa(move mossa) {
    printf("\nGiocata la tessera [%d|%d] a %s!\n", mossa.t.l_cell, mossa.t.r_cell, mossa.side==dx?"dx":"sx");
    // printf("\nGiocata la tessera [%d|%d] a %d!\n", mossa.t.l_cell, mossa.t.r_cell, mossa.side);
}

// print di debug per forzare la stampa
void print_debug() {
    printf("\n#DEBUG#\n");
}
