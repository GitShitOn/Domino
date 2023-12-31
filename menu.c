#include "function.h"

//  menu
void menu() {
    bool play = true;
    int scelta = 2;

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
    char c;
    bool fine = false;
    bool validMove = false;
    bool validSwap;
    int maxHand = 0;
    int n;
    side_t side;
    struct timespec ts;
    struct timespec tf;
    timespec_get(&ts, TIME_UTC);
    tessera peek;

    printHand(hand);

    while(!fine) {

        validMove = false;

        do {
            side = -1;
            validSwap = false;

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

            peek = peekHand(hand, n);

            while(!validSwap && peek.l_cell != peek.r_cell && peek.r_cell != mirror_r) {
                fflush(stdin);
                printf("\nGirare la tessera? [Y/n] o [1/0]: ");
                scanf("%c", &c);
                fflush(stdin);
                if(c == 'y' || c == 'Y' || c == '1') {
                    peek = swapTessera(peek);
                    validSwap = true;
                }
                // else if(c == 'n' || c == 'N' || c=='0')
                else
                    validSwap = true;
            }

            while(side != 0 && side != 1 && field != NULL) {
                printf("\nScegliere il lato [Sinistra(%d) | Destra(%d)]: ", sx, dx);
                scanf("%d", &side);
                fflush(stdin);
            }
            // */
            
            if(isValidMove(field, peek, side))
                validMove = true;
            else
                printf("\nMossa non valida!\n");

        } while(!validMove);

        makeMove(&field, &hand, (move){peek, n, -1, side});

        // field = addToField(field, peek, side);
        // hand = removeTessera(hand, n);

        fine = checkFine(field, hand);
    }

    timespec_get(&tf, TIME_UTC);
    printf("\n\nFine della partita, non ci sono più mosse disponibili!\n");
    printf("\nHai totalizzato un totale di %d punti in %lds!\n", contaPunti(field), tf.tv_sec - ts.tv_sec);
    printField(field);
    printHand(hand);
    printf("\nPress any key to continue...");
    fflush(stdin);
    scanf("%c",&c);
    fflush(stdin);

    if(field != NULL)
        free_nodes(field);
    if(hand != NULL)
        free_nodes(hand);
}

//  ai game
void aiGame() {
    char stall;
    node* hand = createHand();
    node* field = (node*)malloc(sizeof(node));
    field = NULL;
    move bestMove;
    bool fine = false;

    printStartingHand(hand);

    printf("\nNext...\n");
    fflush(stdin);
    scanf("%c",&stall);
    fflush(stdin);

    while(!fine) {

        bestMove = findBestMove(field, hand, 0, calcDepth(hand));
        
        makeMove(&field, &hand, bestMove);

        fine = checkFine(field, hand);

        printMossa(bestMove);
        printField(field);
        printHand(hand);

        printf("\nNext...\n");
        fflush(stdin);
        scanf("%c",&stall);
        fflush(stdin);
    }

    printf("\nFine della partita, non ci sono più mosse disponibili!\n");
    printf("\nE' stato totalizzato un totale di %d punti!\n", contaPunti(field));
    printField(field);
    printHand(hand);
    printf("\nPress any key to continue...");
    fflush(stdin);
    scanf("%c",&stall);
    fflush(stdin);

    if(field != NULL)
        free_nodes(field);
    if(hand != NULL)
        free_nodes(hand);
}

//  challenge
void challenge() {

    node* hand = createHandChallenge();
    node* field = (node*)malloc(sizeof(node));
    field = NULL;
    move bestMove, copyBestMove;
    bool start = true, fine = false;

    while(!fine) {

        bestMove = findBestMove(field, hand, 0, AI_DEPTH);

        // conversione delle tessere speciali
        copyBestMove = bestMove;

        // aggiunta al campo e rimozione dalla mano
        makeMove(&field, &hand, bestMove);

        // print della mossa
        if(start) {
            printf("S ");
            start = false;
        }
        else 
            printf("%c ", copyBestMove.side == dx ? 'R' : 'L');

        printf("%d %d ", copyBestMove.t.l_cell, copyBestMove.t.r_cell);


        fine = checkFine(field, hand);
    }

    if(field != NULL)
        free_nodes(field);
    
    if(hand != NULL)
        free_nodes(hand);
}
