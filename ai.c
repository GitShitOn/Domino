#include "function.h"

move findBestMove(node* field, node* hand, int score) {
    move currentMove, bestMove = {{0,0},-1,0,-1};\
    node* head = hand;
    int i = 0;
    if(hand == NULL)
        return (move){{0,0}, -1, score, 0};
    while(hand != NULL) {
        currentMove.n = i;
        
        //no gira
        currentMove.t = hand->me;
        if(checkAndMake(field, head, &currentMove, i, score, dx)) 
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        if(checkAndMake(field, head, &currentMove, i, score, sx))
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;

        //gira
        currentMove.t = swapTessera(currentMove.t);
        if(checkAndMake(field, head, &currentMove, i, score, dx))
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        if(checkAndMake(field, head, &currentMove, i, score, sx))
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        
        hand = hand->next;
        i++;
    }
    return bestMove;
}

bool checkAndMake(node* field, node* hand, move* currentMove, int i, int score, int side) {
    if(isValidMove(field, currentMove->t, side)) {
        currentMove->score = findBestMove(
                addToField(copyNodes(field),hand->me, side), 
                removeTessera(copyNodes(hand), i), 
                score + valoreTessera(hand->me)
            ).score;
        currentMove->side = side;
        return true;
    }
    return false;
    
}


move findBestMove2(node* field, node* hand, int score) {
    node* head = hand;
    move currentMove, bestMove = {{0,0},-1,score,-1};
    int i = 0;

    while(hand != NULL) {
        // dx - noFlip
        currentMove = makeCurrentMove(hand->me, i, score, dx);
        currentMove.score = calcMove(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // sx - noFlip
        currentMove = makeCurrentMove(hand->me, i, score, sx);
        currentMove.score = calcMove(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // dx - flip
        currentMove = makeCurrentMove(swapTessera(hand->me), i, score, dx);
        currentMove.score = calcMove(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // sx - flip
        currentMove = makeCurrentMove(swapTessera(hand->me), i, score, sx);
        currentMove.score = calcMove(field, head, currentMove);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        hand = hand->next;
        i++;
    }

    return bestMove;
}

// solo score, viene calcolato lo score totale in automatico
move makeCurrentMove(tessera t, int n, int score, int side) {
    return (move) {t, n, score + valoreTessera(t), side};
}

int calcMove(node* field, node* hand, move currentMove) {
    if(isValidMove(field, currentMove.t, currentMove.side)) {
        if(hand->next == NULL)
            return currentMove.score;
        return findBestMove2(
            addToField(copyNodes(field), currentMove.t, currentMove.side),
            removeTessera(copyNodes(hand), currentMove.n),
            currentMove.score
            ).score;
    }
    return -1;
}

// bug se non si riesce a trovare una sequenza con tutte le mosse
