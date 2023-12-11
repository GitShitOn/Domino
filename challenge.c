#include "function.h"

// Copia di ai x challenge
move findBestMoveChallenge(node* field, node* hand, int score) {
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

        hand = hand->next;
        i++;
    }

    return bestMove;
}
