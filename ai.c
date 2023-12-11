#include "function.h"

move findBestMove(node* field, node* hand, int score, int depth) {
    
    node* head = hand;
    move currentMove, bestMove = {{0,0}, -1, score, -1};
    int i = 0;

    if(depth == 0) {
        return bestMove;
    }

    while(hand != NULL) {
        // dx - noFlip
        currentMove = createCurrentMove(hand->me, i, score, dx);
        currentMove.score = calcMove(field, head, currentMove, depth);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }
        
        // sx - noFlip
        currentMove = createCurrentMove(hand->me, i, score, sx);
        currentMove.score = calcMove(field, head, currentMove, depth);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // dx - flip
        currentMove = createCurrentMove(swapTessera(hand->me), i, score, dx);
        currentMove.score = calcMove(field, head, currentMove, depth);
        if(currentMove.score != -1) {
            if(bestMove.score < currentMove.score)
                bestMove = currentMove;
        }

        // sx - flip
        currentMove = createCurrentMove(swapTessera(hand->me), i, score, sx);
        currentMove.score = calcMove(field, head, currentMove, depth);
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
move createCurrentMove(tessera t, int n, int score, side_t side) {
    return (move) {t, n, score + valoreTessera(t), side};
}

// CalcMove con valori speciali
int calcMove(node* field, node* hand, move currentMove, int depth) {

    if(isValidMove(field, currentMove.t, currentMove.side)) {

        //  Controlli tessere speciali
        //  Jolly
        if(currentMove.t.l_cell == jolly) {
            currentMove.score++;
        }

        if(hand->next == NULL)
            return currentMove.score;

        //  Copia di field e hand
        node* fCopy = copyNodes(field);
        node* hCopy = copyNodes(hand);

        //  Controlli tessere speciali
        //  Plus_One
        if(currentMove.t.l_cell == plus_one) {
            fCopy = fieldPlusOne(fCopy);
            currentMove.t = makePlusOne(fCopy, currentMove.side);
            currentMove.score = contaPunti(fCopy) + valoreTessera(currentMove.t);
        }
        //  Mirror
        if(currentMove.t.l_cell == mirror_l) {
            currentMove.t = mirrorTessera(fCopy, currentMove.side);
        }

        //  Calcola miglior mossa
        int bestMoveScore = findBestMove(
            addToField(fCopy, currentMove.t, currentMove.side),
            removeTessera(hCopy, currentMove.n),
            currentMove.score,
            (depth - 1)
        ).score;

        //  Free
        if(fCopy != NULL)
            free_nodes(fCopy);
        if(hCopy != NULL)
            free_nodes(hCopy);

        
        return bestMoveScore;
    }
    return -1;
}

//  Da migliorare
int calcDepth(node* hand) {
    double max = contaHand(hand);
    double dep = AI_DEPTH;
    dep = ceil(dep / (contaJolly(hand)+1));

    while(max > AI_DEPTH) {
        max = max / 3;
        dep = ceil(dep / 3.0);
    }
    // printf("\nDepth: %d", (int)dep);
    return (int)dep;
}
