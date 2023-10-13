#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int l_cell;
    int r_cell;
} tessera;

typedef struct nod{
    tessera me;
    struct nod* next;
} node;

void menu(void);
void soloGame();
void printHand(node*);
void printField(node*);
void makeMove(node*, node*);
node* createHand(int);
tessera playerMove(node*);
tessera createTessera();
tessera removeTessera(node*, int);

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
        printf("\nBenvenuto!\n\n");
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
    bool fine = false;
    node* field = NULL;
/*
    do {
        printf("\nScegliere il numero di tessere: ");
        scanf("%d",&n);
    } while(n<=0);
*/

    node* head = createHand(n);

    printf("\nLa tua mano:");
    printHand(head);

    int count = 10;
    while(!fine && count > 0) {
        printField(field);
        makeMove(field, head);
        count--;
    // continuare
    }

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

// Rimuove la tessera in posizione n dalla lista - BUGGED
tessera removeTessera(node* hand, int n) {
    n = n-1;
    if(n == 0) {
        tessera t = hand->me;
        if(hand->next != NULL)
            *hand = *hand->next;
        else
            hand = NULL;
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
void makeMove(node* field, node* hand) {
    tessera t = playerMove(hand);

    // continuare con modifica del campo
    // e check fine partita

    printHand(hand);
}

// Fa scegliere la tessera da giocare, la rimuove dalla mano e la restituisce al controller
tessera playerMove(node* hand) {
    int n = 1;
    // n = 2;
    int count = 0;
    tessera t;
    node* head = hand;

    printf("\nScegli la tessera che vuoi giocare");

    while(hand != NULL) {
        count++;
        printf("\n%d - [%d|%d]", count, hand->me.l_cell, hand->me.r_cell);
        hand = hand->next;
    }
    printf("\nScelta: ");
/*
    scanf("%d",&n);
    while(n<1 || n>count) {
        printf("Inserire un valore valido: ");
        scanf("%d", &n);
    }
*/

    t = removeTessera(&head, n);

    return t;
}
