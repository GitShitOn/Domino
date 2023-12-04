#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define dx 0
#define sx 1

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

void menu();
void soloGame();
void aiGame();
void challenge();
node* createHand();
tessera createTessera();
tessera createTesseraValue(int, int);
node* removeTessera(node*, int);
result resolveChallenge(node*, tessera, result);    //  challenge
void printNodes(node*);
void printHand(node*);
void printField(node*);
int printPossibleMoves(node*);
bool isValidMove(node*, tessera, int);
tessera peekHand(node*, int);
node* addToField(node*, tessera, int);
bool checkFine(node*, node*);
int contaPunti(node*);

int main(int args, char** argv) {

    srand(time(NULL));

    // challenge(); return 0;   //  debug x challenge

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
                // scelta = 3; // solo per debug       <------
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
    field = NULL;

    bool fine = false, validMove = false;

    int maxHand = 0;
    int n;
    int side;

    printHand(hand);

    while(!fine) {

        validMove = false;

        do {
            side = -1;
            if(field != NULL)
                printField(field);
            maxHand = printPossibleMoves(hand);

            // n = rand()%maxHand;printf("%d",n+1);side=rand()%1+1;       /*    <-----
            scanf("%d",&n);
            while(n<0 || n>maxHand) {
                printf("Inserire un valore valido: ");
                scanf("%d", &n);
            }
            if(n == 0)  // quit di emergenza con 0
                return;   
            n--;
            while(side != 0 && side != 1 && field != NULL) {
                printf("\nScegliere il lato [Sinistra(%d) | Destra(%d)]: ", sx, dx);
                scanf("%d", &side);
            }
            // */
            
            if(isValidMove(field, peekHand(hand, n), side))
                validMove = true;
            else
                printf("\nMossa non valida!\n");

        } while(!validMove);

        field = addToField(field, peekHand(hand, n), side);
        hand = removeTessera(hand, n);

        fine = checkFine(field, hand);
    }

    printf("\nFine della partita, non ci sono più mosse disponibili!\n");
    printf("\nHai totalizzato un totale di %d punti!\n", contaPunti(field));
    printField(field);
    printHand(hand);
    printf("\nPress any key to continue...");
    char c;
    fflush(stdin);
    scanf("%c",&c);
    fflush(stdin);
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
    int n = 3, a = 2, b = 2;
    node* hand = NULL;
    node* current;

    // scanf("%d", &n);

    for(int i = 0; i<n; i++) {
        /*
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
            // hand->me = createTesseraValue(3,3);
            hand->next = NULL;
            current = hand;
        }
        else {
            node* nodo = (node*)malloc(sizeof(node));
            nodo->me = createTessera();
            // nodo->me = createTesseraValue(3,3);
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

// crea una tessera passandogli i valori (non random)
tessera createTesseraValue(int a, int b) {
    tessera t = {a, b};
    return t;
}

// Stampa le tessere, utilizzata per debug principalemnte
void printNodes(node* hand) {
    printf("\n");
    while(hand != NULL) {
        printf("[%d|%d] ", hand->me.l_cell, hand->me.r_cell);
        hand = hand->next;
    }
    printf("\n");
}

void printHand(node* hand) {
    printf("\nLa tua mano:");
    printNodes(hand);
}

// Stampa il campo
void printField(node* field) {
    printf("\nTavolo attuale:");
    printNodes(field);
}

// stampa la mano (fancy)
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

// Rimuove la tessera in posizione n dalla lista - BUGGED ? 
node* removeTessera(node* hand, int n) {
    
    if(hand == NULL)
        return NULL;


    // se 0 ritorna il prossimo
    if(!n) 
        return hand->next;
    
    if(hand->next == NULL)
        return hand;

    int i = 0;
    node* head = hand;

    while(i<(n-1)) {
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

// controlla se una mossa è valida
bool isValidMove(node* field, tessera t, int side) {
    if(field == NULL)
        return true;
    if(side == sx) {
        if(field->me.l_cell == t.r_cell)
            return true;
    }
    else if(side == dx) {
        while(field->next != NULL)
            field = field->next;
        if(field->me.r_cell == t.l_cell)
            return true;
    }
    return false;
}

tessera peekHand(node* hand, int n) {
    int i = 0;
    while(i < n) {
        hand = hand->next;
        i++;
    }
    return hand->me;
}

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

//  controlla se il gioco può andare avanti
bool checkFine(node* field, node* hand) {
    if(hand == NULL)
        return true;
    while(hand != NULL) {
        if (isValidMove(field, hand->me, dx))
            return false;
        if (isValidMove(field, hand->me, sx))
            return false;
        hand = hand->next;
    }
    return true;
}

int contaPunti(node* field) {
    int punti = 0;
    while(field != NULL) {
        punti += field->me.l_cell;
        punti += field->me.r_cell;
        field = field->next;
    }
    return punti;
}
