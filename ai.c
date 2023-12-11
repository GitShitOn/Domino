#include "function.h"

move findBestMove(node* field, node* hand, int score) {
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
move makeCurrentMove(tessera t, int n, int score, side_t side) {
    return (move) {t, n, score + valoreTessera(t), side};
}

/*  senza free
int calcMove(node* field, node* hand, move currentMove) {
    if(isValidMove(field, currentMove.t, currentMove.side)) {
        if(hand->next == NULL)
            return currentMove.score;
        return findBestMove(
            addToField(copyNodes(field), currentMove.t, currentMove.side),
            removeTessera(copyNodes(hand), currentMove.n),
            currentMove.score
            ).score;
    }
    return -1;
}
// */

// /*
int calcMove(node* field, node* hand, move currentMove) {
    if(isValidMove(field, currentMove.t, currentMove.side)) {
        if(hand->next == NULL)
            return currentMove.score;
        node* fCopy = copyNodes(field);
        node* hCopy = copyNodes(hand);
        int bestMoveScore = findBestMove(
            addToField(fCopy, currentMove.t, currentMove.side),
            removeTessera(hCopy, currentMove.n),
            currentMove.score
        ).score;
        free_nodes(fCopy);
        free_nodes(hCopy);
        return bestMoveScore;
    }
    return -1;
}
// */
