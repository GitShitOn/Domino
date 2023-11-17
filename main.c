#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define dx 0;
#define sx 1;

typedef struct {
    int l_cell;
    int r_cell;
} tessera;

typedef struct node {
    tessera me;
    struct node* next;
} node;

typedef struct {
    int n;
    int side;
} move;

typedef struct {
    node* field;
    node* hand;
} nodes;

typedef struct {
    int score;
    char* seq;
} result;

void menu();
void soloGame();
void aiGame();
void challenge();
node* createHand();
tessera createTessera();
tessera createTesseraV(int, int);
node* removeTessera(node*, int);
result resolveChallenge(node*, tessera, result);
void printHand(node*);
void printField(node*);
int printPossibleMoves(node*);
bool isValidMove(node*, node*, move);

int main(int args, char** argv) {

    srand(time(NULL));

    challenge(); return 0;

    // controllo se challenge
    if(args>1) {
        if(!strcmp("--challenge", argv[1])) {
            challenge();
            return 0;
        }
    }

    //  avvio menu per la partita
    menu();

    return 0;
}

//  menu
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
// /*       <-----
        scanf("%d", &scelta);
        while(scelta < 1 || scelta > 3) {
            printf("\nInserire una scelta valida: ");
            scanf("%d", &scelta);
        }
// */

        switch(scelta) {
            case 1:
                soloGame();

                // scelta = 3; // solo per debug

                break;
            case 2:
                aiGame();
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

// solo game
void soloGame() {
    node* hand = createHand();
    node* field = (node*)malloc(sizeof(node));

    bool fine = false, validMove = false;

    int maxHand = 0;
    int n;
    int side;

    printf("\n\nLa mano:");
    printHand(hand);

    while(!fine) {

        validMove = false;
        side = -1;

        do {
            maxHand = printPossibleMoves(hand);

            // n = rand()%count;printf("%d",n+1);       /*    <-----
            scanf("%d",&n);
            while(n<1 || n>maxHand) {
                printf("Inserire un valore valido: ");
                scanf("%d", &n);
            }
            n--;
            while(side != 0 && side != 1 && field != NULL) {
                printf("\nScegliere il lato [Destra(0) | Sinistra(1)]: ");
                scanf("%d", &side);
            }
            // */

            move m = {n, side};
            /*
            if(isValidMove(field, hand, m))
                validMove = true;
                */

        } while(!validMove);

    }


}

//  ai game
void aiGame() {
    node* hand = createHand();
    node* field = (node*)malloc(sizeof(node));

    bool fine = false;

    printf("\n\nLa mano:");
    printHand(hand);

    //  find best move order

    while(!fine) {
        printPossibleMoves(hand);

        //  print best move
    }


}

//  challenge
void challenge() {
    int n = 2, a = 2, b = 3;
    node* hand = NULL;
    node* current;

    scanf("%d", &n);

    for(int i = 0; i<n; i++) {
        // /*
        scanf("%d", &a);
        scanf("%d", &b);
        // */
        if(hand == NULL) {
            hand = (node*)malloc(sizeof(node));
            hand->me = createTesseraV(a,b);
            hand->next = NULL;
            current = hand;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTesseraV(a,b);
            nodo->next = NULL;
            current->next = nodo;
            current = current->next;
        }
    }

    if(n > 0) {
        result score = resolveChallenge(hand, (tessera){0,0}, (result){0,(char*)malloc(n*6+1)});

        printf("%s", score.seq);
    }
}

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
            hand->me = createTessera();
            hand->next = NULL;
            current = hand;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTessera();
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

tessera createTesseraV(int a, int b) {
    tessera t = {a, b};
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

int printPossibleMoves(node* hand) {
    int count = 0;
        printf("\nScegli la tessera che vuoi giocare");

        while(hand != NULL) {
            count++;
            printf("\n%d - [%d|%d]", count, hand->me.l_cell, hand->me.r_cell);
            hand = hand->next;
        }
        printf("\n\nScelta: ");

    return count;     
}

result resolveChallenge(node* hand, tessera t, result score) {
    result e_score, best_score, og_score;
    node* og = hand;
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
        best_score = score;
        og_score = score;
        while(hand != NULL) {
            if(t.r_cell == hand->me.l_cell) {
                score.score = og_score.score + hand->me.l_cell + hand->me.r_cell;
                sprintf(score.seq, "%s R %d %d ", og_score.seq, hand->me.l_cell, hand->me.r_cell);
                e_score = resolveChallenge(removeTessera(og, i), hand->me, score);
                if(e_score.score > best_score.score)
                    best_score = e_score;
            }
            if(t.r_cell == hand->me.l_cell) {
                score.score = og_score.score + hand->me.l_cell + hand->me.r_cell;
                sprintf(score.seq, "%s L %d %d ", og_score.seq, hand->me.l_cell, hand->me.r_cell);
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

// Rimuove la tessera in posizione n dalla lista - BUGGED
node* removeTessera(node* hand, int n) {
    
    if(hand == NULL)
        return NULL;
    
    if(!n)
        return hand->next;

    int i = 0;
    node* head = hand;

    while(i<n-1) {
        hand = hand->next;
        i++;
    }

    if(hand->next->next == NULL) {
        hand->next = NULL;
        return head;
    }

    hand->next = hand->next->next;

    return head;
}

/*
bool isValidMove(node* field, node* hand, move m) {
    if(field == NULL)
        return true;
    if(m.side == dx) {
        
    }
}
*/
