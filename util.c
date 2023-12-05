#include "function.h"

// controlla se una mossa è valida
bool isValidMove(node* field, tessera t, int side) {
    if(field == NULL)
        return true;
    if(side == sx) {
        if(field->me.l_cell == t.r_cell)
            return true;
    }
    else if(side == dx) {
        while(field->next != NULL)
            field = field->next;
        if(field->me.r_cell == t.l_cell)
            return true;
    }
    return false;
}

tessera peekHand(node* hand, int n) {
    int i = 0;
    while(i < n) {
        hand = hand->next;
        i++;
    }
    return hand->me;
}

//  controlla se il gioco può andare avanti
bool checkFine(node* field, node* hand) {
    if(hand == NULL)
        return true;
    while(hand != NULL) {
        if (isValidMove(field, hand->me, dx))
            return false;
        if (isValidMove(field, hand->me, sx))
            return false;
        if (isValidMove(field, swapTessera(hand->me), dx))
            return false;
        if (isValidMove(field, swapTessera(hand->me), sx))
            return false;
        hand = hand->next;
    }
    return true;
}

int contaPunti(node* field) {
    int punti = 0;
    while(field != NULL) {
        punti += field->me.l_cell;
        punti += field->me.r_cell;
        field = field->next;
    }
    return punti;
}

tessera swapTessera(tessera t) {
    int aus = t.l_cell;
    t.l_cell = t.r_cell;
    t.r_cell = aus;
    return t;
}

int contaHand(node* hand) {
    int i = 0;
    if(hand == NULL)
        return i;
    while(hand->next != NULL) {
        hand = hand->next;
        i++;
    }
    return ++i;
}
