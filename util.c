#include "function.h"

// controlla se una mossa è valida
bool isValidMove(node* field, tessera t, side_t side) {
    //check x challenge - plus one
    if(t.l_cell == plus_one && t.r_cell == plus_one) {
        if(field != NULL)
            return true;
        else
            return false;
    }
    
    //check x challenge - mirror
    if(t.l_cell == mirror_l && t.r_cell == mirror_r) {
        if(field != NULL)
            return true;
        else
            return false;
    }

    if(field == NULL)
        return true;
    
    // check x challenge - jolly
    if(t.l_cell == jolly && t.r_cell == jolly)
        return true;

    if(side == sx) {
        if(field->me.l_cell == t.r_cell)
            return true;
        if(field->me.l_cell == jolly)
            return true;
    }
    else if(side == dx) {
        while(field->next != NULL)
            field = field->next;
        if(field->me.r_cell == t.l_cell)
            return true;
        if(field->me.r_cell == jolly)
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

int valoreTessera(tessera t) {
    return (t.l_cell+t.r_cell);
}
