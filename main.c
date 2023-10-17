#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int l_cell;
    int r_cell;
} tessera;

typedef struct node{
    tessera me;
    struct node* next;
} node;

void menu(void);
void soloGame();
void printHand(node*);
void printField(node*);
node* makeMove(node*, node*);
node* createHand(int);
tessera playerMove(node*, node*);
tessera createTessera();
node* addTessera(node*, tessera, int);
tessera removeTessera(node*, int);
bool isValidMove(node*, tessera);
bool canConnectLeft(tessera, tessera);
bool canConnectRight(tessera, tessera);
node* addToField(node*, tessera);
tessera rotateTessera(tessera, tessera, bool);
bool checkEndGame(node*, node*);
int contaPunti(node*);

// Main
int main(void) {

    srand(time(NULL));
    menu();

    return 0;
}

// Funzione che serve da menu e dalla quale si avviano le partite
void menu() {
    bool play = true;
    int scelta = 1;

    while(play) {
        printf("\n\nBenvenuto!\n\n");
        printf("Scegli la tua modalita' di gioco:\n");
        printf("1 - Solo\n");
        printf("2 - AI\n");
        printf("3 - Quit");
        printf("\nScelta: ");
/*
        scanf("%d", &scelta);
        while(scelta < 1 || scelta > 3) {
            printf("\nInserire una scelta valida: ");
            scanf("%d", &scelta);
        }
*/

        switch(scelta) {
            case 1:
                soloGame();

                scelta = 3; //modificare, solo per debug

                break;
            case 2:
                break;
            case 3:
                play = false;
                printf("\nArrivederci!\n");
                break;
            default:
                printf("\nDebuf time!\n");
                break;
        }
    }
}

// Funzione per la gestione di una partita in solo
void soloGame() {
    int n = 5;
    int punti = 0;
    bool fine = false;
    node* field = NULL;
/*
    do {
        printf("\nScegliere il numero di tessere: ");
        scanf("%d",&n);
    } while(n<=0);
*/

    node* hand = createHand(n);

    printf("\n\nLa tua mano:");
    printHand(hand);

    int count = 10;
    while(!fine && count > 0) {
        printField(field);
        field = makeMove(field, hand);
        count--;
        if(checkEndGame(field, hand))
            fine = true;
    }

    printf("\n\nImpossibile continuare a giocare!\n");
    printField(field);
    printf("\nLa tua mano:");
    printHand(hand);

    punti = contaPunti(field);
    printf("\nHai realizzato un totale di %d punti!\n", punti);

}

// Crea n carte e restituisce il nodo che contiene la prima
node* createHand(int n) {
    node* head = NULL;
    node* current = NULL;
    for(int i = 0;i<n;i++) {
        if(head == NULL) {
            head = (node*)malloc(sizeof(node));
            head->me = createTessera();
            head->next = NULL;
            current = head;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTessera();
            nodo->next = NULL;
            current->next = nodo;
            current = current->next;
        }
    }

    return head;
}

// Crea una tessera e la restituisce
tessera createTessera() {
    tessera t = {rand()%6+1, rand()%6+1};
    return t;
}

node* addTessera(node* hand, tessera t, int n) {
    int i = 0;
    node* prev = NULL;
    node* new = (node*)malloc(sizeof(node));
    node* head = hand;
    new->me = t;
    new->next = NULL;
    n--;
    if(hand == NULL) {
        return new;
    }
    while(i<n && hand->next != NULL) {
        prev = hand;
        hand = head->next;
    }
    if(prev == NULL) {
        new->next = hand;
        return new;
    }
    prev->next = new;
    new->next = hand;
    return head;
}

// Rimuove la tessera in posizione n dalla lista - BUGGED
tessera removeTessera(node* hand, int n) {
    n--;;
    if(n == 0) {
        tessera t = hand->me;
        if(hand->next != NULL)
            *hand = *hand->next;
        return t;
    }

    for(int i = 1; i<n; i++) {
        hand = hand->next;
    }
    tessera t = hand->next->me;
    hand->next = hand->next->next;
    return t;

}

// Stampa le tessere, utilizzata per debug principalemnte
void printHand(node* hand) {
    printf("\n");
    while(hand != NULL) {
        printf("[%d|%d] ", hand->me.l_cell, hand->me.r_cell);
        hand = hand->next;
    }
    printf("\n");
}

// Stampa il campo
void printField(node* field) {
    printf("\nTavolo attuale:");
    printHand(field);
}

// Controlla il turno del giocatore
node* makeMove(node* field, node* hand) {
    tessera t = playerMove(hand, field);
    //printHand(hand);

    return field = addToField(field, t);
}

// Fa scegliere la tessera da giocare, la rimuove dalla mano e la restituisce al controller
tessera playerMove(node* hand, node* field) {
    int n = 3;
    int count = 0;
    tessera t;
    node* head = hand;
    bool check = true;

    do {
        printf("\nScegli la tessera che vuoi giocare");
        hand = head;

        while(head != NULL) {
            count++;
            printf("\n%d - [%d|%d]", count, head->me.l_cell, head->me.r_cell);
            head = head->next;
        }
        printf("\n\nScelta: ");
    /*
        scanf("%d",&n);
        while(n<1 || n>count) {
            printf("Inserire un valore valido: ");
            scanf("%d", &n);
        }
    */

        t = removeTessera(hand, n);
        hand = head;
        if(!isValidMove(field, t)) {
            printf("\nMossa non valida, riprovare!\n");
            head = addTessera(hand, t, n);
            check = false;
        }
    } while(!check);

    printf("\n");

    return t;
}


bool isValidMove(node* field, tessera t) {
    if(field == NULL)
        return true;
    if(canConnectLeft(field->me, t))
        return true;
    while(field->next != NULL)
        field = field->next;
    if(canConnectRight(field->me, t))
        return true;
    return false;
}

// field - t
bool canConnectRight(tessera t1, tessera t2) {
    return (
            t1.r_cell == t2.l_cell || 
            t1.r_cell == t2.r_cell
            );
}

// field - t
bool canConnectLeft(tessera t1, tessera t2) {
    return (
            t1.l_cell == t2.l_cell || 
            t1.l_cell == t2.r_cell
            );
}

node* addToField(node* field, tessera t) {
    node* new = (node*)malloc(sizeof(node));
    node* head = field;
    new->next = NULL;
    if(field == NULL ) {
        new->me = t;
        return new;
    }
    if(canConnectLeft(field->me, t)) {
        new->me = rotateTessera(t, field->me, false);
        new->next = field;
        return new;
    }
    while(field->next != NULL)
        field = field->next;
    new->me = rotateTessera(field->me, t, true);
    field->next = new;
    return head;
}

/* 
    side = false
    Combacia il lato destro di t1 con quello sinistro di t2
    [2|1] & [2|5] -> [1|2] & [2|5];
    side = true
    Combacia il lato sinistro di t2 con quello destro di t1
    [2|1] & [2|1] -> [2|1] & [1|2];
*/
tessera rotateTessera(tessera t1, tessera t2, bool side) {
    if(!side) {
        if(t1.r_cell == t2.l_cell)
            return t1;
        int aus = t1.l_cell;
        t1.l_cell = t1.r_cell;
        t1.r_cell = aus;
        return t1;
    }
    if(t2.l_cell == t1.r_cell)
        return t2;
    int aus = t2.l_cell;
    t2.l_cell = t2.r_cell;
    t2.r_cell = aus;
    return t2;
}

bool checkEndGame(node* field, node* hand) {
    if(hand == NULL)
        return true;
    if(field == NULL) {
        return false;
    }
    tessera first = field->me;
    while(field->next != NULL)
        field = field->next;
    while(hand->next != NULL) {
        if(canConnectLeft(first, hand->me) || canConnectRight(field->me, hand->me))
            return false;
        hand = hand->next;
    }
    return true;
}

int contaPunti(node* field) {
    int punti = 0;
    do {
        punti += field->me.l_cell + field->me.r_cell;
        field = field->next;
    } while(field->next != NULL);
    return punti;
}

/*
    TODO: 
        -fixare problema quando si toglie l'ultima tessera dalla mano
        -permettere di scegliere lato dal quale aggiungere la tessera (priorità attuale: lx dx)
*/
