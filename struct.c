
#include <stdbool.h>

//  1 sx | 0 dx
typedef int side_t;

typedef bool vertical_t;


// int l_cell, int r_cell
typedef struct {
    int l_cell;
    int r_cell;
    char pos[4];    // 0 = riga cella left
                    // 1 = pos. in riga cella left
                    // 2 = riga cella right
                    // 3 = pos. in riga cella right
} tessera;

// tessera me, node* next
typedef struct node {
    tessera me;
    struct node* next;
    struct node* down_l;
    struct node* down_r;
} node;

/*
// node* field, node* hand
typedef struct {
    node* field;
    node* hand;
} nodes;
*/

// int score, char* seq
typedef struct {
    int score;
    char* seq;
} result;

// tessera t, int n, int score, int side
typedef struct {
    tessera t;
    int n;
    int score;
    side_t side;
    vertical_t vertical;
    int row;
} move;
