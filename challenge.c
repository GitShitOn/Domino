#include "function.h"

// Challenge
result resolveChallenge(node* hand, tessera t, result score) {
    result e_score, best_score, og_score;
    node* og = hand;
    best_score = score;
    og_score = score;
    char* og_seq = (char*)malloc(strlen(score.seq));
    strcpy(og_seq, score.seq);
    int i = 0;
    if(t.l_cell == 0) {
        while(hand != NULL) {
            score.score = hand->me.l_cell + hand->me.r_cell;
            sprintf(score.seq, "S %d %d ", hand->me.l_cell, hand->me.r_cell);
            e_score = resolveChallenge(removeTessera(og, i), hand->me, score);
            if(e_score.score > best_score.score)
                best_score = e_score;
            hand = hand->next;
            i++;
        }
    }
    else {
        while(hand != NULL) {
            if(t.r_cell == hand->me.l_cell) {
                score.score = og_score.score + hand->me.l_cell + hand->me.r_cell;
                sprintf(score.seq, "%sR %d %d ", og_seq, hand->me.l_cell, hand->me.r_cell);
                e_score = resolveChallenge(removeTessera(og, i), hand->me, score);
                if(e_score.score > best_score.score)
                    best_score = e_score;
            }
            if(t.l_cell == hand->me.r_cell) {
                score.score = og_score.score + hand->me.l_cell + hand->me.r_cell;
                sprintf(score.seq, "%sL %d %d ", og_seq, hand->me.l_cell, hand->me.r_cell);
                e_score = resolveChallenge(removeTessera(og, i), hand->me, score);
                if(e_score.score > best_score.score)
                    best_score = e_score;
            }

            hand = hand->next;

            i++;
        }
    }

    return best_score;
}