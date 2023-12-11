#include "function.h"

// Copia di ai x challenge
move findBestMoveChallenge(node* field, node* hand, int score) {
    node* head = hand;
    move currentMove, bestMove = {{0,0},-1,score,-1};
    int i = 0;

    while(hand != NULL) {
        // dx - noFlip
        currentMove = makeCurrentMove(hand->me, i, score, dx);
        currentMove.score = calcMoveChallenge(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // sx - noFlip
        currentMove = makeCurrentMove(hand->me, i, score, sx);
        currentMove.score = calcMoveChallenge(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        hand = hand->next;
        i++;
    }

    return bestMove;
}

// copia di calcMove di ai per challenge
int calcMoveChallenge(node* field, node* hand, move currentMove) {

    if(isValidMove(field, currentMove.t, currentMove.side)) {
        if(hand->next == NULL)
            return currentMove.score;
        node* fCopy = copyNodes(field);
        node* hCopy = copyNodes(hand);

        if(currentMove.t.l_cell == plus_one) {
            fCopy = fieldPlusOne(fCopy);
            currentMove.t = makePlusOne(fCopy, currentMove.side);
        }

        if(currentMove.t.l_cell == mirror_l) {
            currentMove.t = mirrorTessera(fCopy, currentMove.side);
        }

        int bestMoveScore = findBestMoveChallenge(
            addToField(fCopy, currentMove.t, currentMove.side),
            removeTessera(hCopy, currentMove.n),
            currentMove.score
        ).score;

        if(fCopy != NULL)
            free_nodes(fCopy);
        if(hCopy != NULL)
            free_nodes(hCopy);
        return bestMoveScore;
    }
    return -1;
}

// somma +1 ad i valori di una tessera (es. 6 -> 1)
tessera t_plusOne(tessera t) {
    if(t.l_cell == jolly && t.r_cell == jolly)
        return t;
    return (tessera) {t.l_cell == 6 ? 1 : (t.l_cell + 1), t.r_cell == 6 ? 1 : (t.r_cell + 1)};
}

// crea la tessera plus_one con il valore della cella
tessera makePlusOne(node* field, side_t side) {
    if(side == sx)
        return createTesseraValue(field->me.l_cell, field->me.l_cell);
    while(field->next != NULL)
        field = field->next;
    return createTesseraValue(field->me.r_cell, field->me.r_cell);
}

// somma +1 a tutto il field
node* fieldPlusOne(node* field) {
    node* head = field;
    while(field != NULL) {
        field->me = t_plusOne(field->me);
        field = field->next;
    }
    return head;
}

tessera mirrorTessera(node* field, side_t side) {
    if(side == dx)
        while(field->next != NULL)
            field = field->next;
    return (tessera) {field->me.r_cell, field->me.l_cell};
}

