#include "function.h"

// Stampa le tessere, utilizzata per debug principalemnte
void printNodes(node* hand) {
    printf("\n");
    while(hand != NULL) {
        printf("[%d|%d] ", hand->me.l_cell, hand->me.r_cell);
        hand = hand->next;
    }
    printf("\n");
}

void printText(node* nodes, char* str) {
    printf("\n%s", str);
    printNodes(nodes);
}

void printHand(node* hand) {
    printText(hand, "La tua mano:");
}

// Stampa il campo
void printField(node* field) {
    printText(field, "Tavolo attuale");
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
            printf("\n%d - [%d|%d]", count, hand->me.l_cell, hand->me.r_cell);
            hand = hand->next;
        }
        printf("\n\nScelta: ");

    return count;     
}

void printMossa(move mossa) {
    printf("\nGiocata la tessera [%d|%d] a %s!\n", mossa.t.l_cell, mossa.t.r_cell, mossa.side==dx?"dx":"sx");
}
