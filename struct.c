

// int l_cell, int r_cell
typedef struct {
    int l_cell;
    int r_cell;
} tessera;

// tessera me, node* next
typedef struct node {
    tessera me;
    struct node* next;
} node;

// node* field, node* hand
typedef struct {
    node* field;
    node* hand;
} nodes;

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
    int side;
} move;
