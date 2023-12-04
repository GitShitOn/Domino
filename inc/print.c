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

void printHand(node* hand) {
    printf("\nLa tua mano:");
    printNodes(hand);
}

// Stampa il campo
void printField(node* field) {
    printf("\nTavolo attuale:");
    printNodes(field);
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