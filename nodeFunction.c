#include "function.h"

// Chiede quante carte creare e restituisce il nodo che contiene la prima
node* createHand() {
    int n = 5;
    node* hand = NULL;
    node* current = NULL;

    // /*       <----
    do {
        printf("\nScegliere il numero di tessere: ");
        scanf("%d",&n);
    } while(n<=0);
// */

    for(int i = 0;i<n;i++) {
        if(hand == NULL) {
            hand = (node*)malloc(sizeof(node));
            hand->me = createTesseraSpecial();
            // hand->me = createTesseraValue(3,3);
            hand->next = NULL;
            current = hand;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTesseraSpecial();
            // nodo->me = createTesseraValue(3,3);
            nodo->next = NULL;
            current->next = nodo;
            current = current->next;
        }
    }

    return hand;
}

node* createHandChallenge() {
    node* hand = NULL;
    node* current;
    int n, a, b;

    scanf("%d", &n);    //  <-----

    for(int i = 0; i<n; i++) {
        // /*       <-----
        scanf("%d", &a);
        scanf("%d", &b);
        // */
        if(hand == NULL) {
            hand = (node*)malloc(sizeof(node));
            hand->me = createTesseraValue(a,b);
            hand->next = NULL;
            current = hand;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTesseraValue(a,b);
            nodo->next = NULL;
            current->next = nodo;
            current = current->next;
        }
    }

    return hand;
}

// Crea una tessera e la restituisce
tessera createTessera() {
    tessera t = {rand()%6+1, rand()%6+1};
    return t;
}

// Crea una tessera e la restituisce
tessera createTesseraSpecial() {
    tessera t;
    switch(rand()%9 + 1) {
        case 1: // jolly
            t = (tessera) {jolly, jolly};
            break;
        case 2: // plus_one
            t = (tessera) {plus_one, plus_one};
            break;
        case 3: // mirror
            t = (tessera) {mirror_l, mirror_r};
            break;
        default:    // 1-6
            t = (tessera){rand()%6+1, rand()%6+1};
            break;
    }
    return t;
}

// crea una tessera passandogli i valori (non random)
tessera createTesseraValue(int a, int b) {
    tessera t = {a, b};
    return t;
}

// Rimuove la tessera in posizione n dalla lista - BUGGED ? 
node* removeTessera(node* hand, int n) {
    
    if(hand == NULL)
        return NULL;


    // se 0 ritorna il prossimo
    if(!n) {
        node* next = hand->next;
        free(hand);
        return next;
    }
    
    // in teoria non serve
    if(hand->next == NULL)
        return hand;

    int i = 0;
    node* head = hand;

    while(i<(n-1)) {
        hand = hand->next;
        i++;
    }

    if(hand->next->next == NULL) {
        free(hand->next);
        hand->next = NULL;
        return head;
    }

    node* next = (node*)hand->next->next;
    free(hand->next);
    hand->next = next;

    return head;
}

//
node* addToField(node* field, tessera t, int side) {
    node* head = (node*)malloc(sizeof(node));
    head->me = t;
    if(field == NULL) {
        head->next = NULL;
        return head;
    }
    if(side == sx) {
        head->next = field;
        return head;
    }
    else if(side == dx) {
        node* fHead = field;
        while(field->next != NULL)
            field = field->next;
        head->next = NULL;
        field->next = head;
        return fHead;
    }
    return NULL;
}

node* copyNodes(node* nodes) {
    node* copy = NULL;
    node* head;
    if(nodes == NULL)
        return NULL;
    while(nodes != NULL) {
        if(copy == NULL) {
            copy = (node*)malloc(sizeof(node));
            copy->me = nodes->me;
            copy->next = NULL;
            head = copy;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = nodes->me;
            nodo->next = NULL;
            copy->next = nodo;
            copy = copy->next;
        }
        nodes = nodes->next;
    }
    return head;
}

void free_nodes(node* nodes) {
    if(!nodes) {
        free_nodes(nodes->next);
        free(nodes);
    }
}
