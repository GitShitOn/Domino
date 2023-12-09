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
