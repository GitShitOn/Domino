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
void printCard(node* hand) {
    switch(hand->me.l_cell) {
        case jolly:
            printf("[J|J] ");
            break;
        case plus_one:
            printf("[Field +1] ");
            break;
        case mirror_l:
            printf("[Mirror] ");
            break;
        default:
            printf("[%d|%d] ", hand->me.l_cell, hand->me.r_cell);
            // printf("[%d(%d/%d)|%d(%d/%d)] ", hand->me.l_cell,hand->me.pos[0],hand->me.pos[1], hand->me.r_cell,hand->me.pos[2],hand->me.pos[3]);           // print debug posizioni
    }
}

void printHalfCard(node* hand) {
    switch(hand->me.l_cell) {
        case jolly:
            printf("[J| ");
            break;
        default:
            printf("[%d| ", hand->me.l_cell);

    }
}

void recursivePrint(node* n) {

}

// Stampa il campo
void printField(node* field) {          // rifare ricorsiva
    printf("\n%s", "Tavolo attuale");
    int depth = 0;
    int count = 0;
    node* curr;
    do {
        curr = field;
        while(curr) {
            if(curr->me.pos[0] < curr->me.pos[2] && ) {
                depth = curr->me.pos[2] > depth ? curr->me.pos[2] : depth;
                printHalfCard(curr);
            }
            else if(curr->me.pos[0] < curr->me.pos[2]) {
                recursivePrint(curr->down_l);

            }
            curr = curr->next;
        }
        printf("\n");
        count++;
    } while(count <= depth);
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
