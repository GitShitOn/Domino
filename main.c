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
tessera printFancyHand(node*);
void printField(node*);
void makeMove(node*, node*);
node* createHand(int);
tessera createTessera();
tessera removeTessera(node*, int);

int main(void) {

    srand(time(NULL));
    menu();

    return 0;
}

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
///*
        scanf("%d", &scelta);
        while(scelta < 1 || scelta > 3) {
            printf("\nInserire una scelta valida: ");
            scanf("%d", &scelta);
        }
//*/

        switch(scelta) {
            case 1:
                soloGame();
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

void soloGame() {
    int n = 5;
    bool fine = false;
    node* field = NULL;
// /*
    do {
        printf("\nScegliere il numero di tessere: ");
        scanf("%d",&n);
    } while(n<=0);
// */

    node* head = createHand(n);

    printf("\nLa tua mano:");
    printHand(head);

    while(!fine) {
        printField(field);
        makeMove(field, head);
    // continuare
    }

}

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

tessera createTessera() {
    tessera t = {rand()%6+1, rand()%6+1};
    return t;
}

tessera removeTessera(node* hand, int n) {
    n = n-1;
    if(n == 0) {
        tessera t = hand->me;
        *hand = *hand->next;
        return t;
    }

    node* head = hand;
    for(int i = 1; i<n; i++) {
        hand = hand->next;
    }
    tessera t = hand->next->me;
    hand->next = hand->next->next;
    hand = head;
    return t;

}

void printHand(node* hand) {
    printf("\n");
    while(hand != NULL) {
        printf("[%d|%d] ", hand->me.l_cell, hand->me.r_cell);
        hand = hand->next;
    }
    printf("\n");
}

void printField(node* field) {
    printf("\nTavolo attuale:");
    printHand(field);
}

void makeMove(node* field, node* hand) {
    tessera t = printFancyHand(hand);
    printHand(hand);
}

tessera printFancyHand(node* hand) {
    int n = 0;
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
///*
    scanf("%d",&n);
    while(n<1 || n>count) {
        printf("Inserire un valore valido: ");
        scanf("%d", &n);
    }
//*/

    t = removeTessera(head, n);

    return t;
}
