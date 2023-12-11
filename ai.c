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

// CalcMove con valori speciali
int calcMove(node* field, node* hand, move currentMove) {

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

/*  CalcMove senza valori speciali
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

        if(fCopy != NULL)
            free_nodes(fCopy);
        if(hCopy != NULL)
            free_nodes(hCopy);
        return bestMoveScore;
    }
    return -1;
}
*/
