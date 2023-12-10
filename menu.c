#include "function.h"

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
    char c;
    bool fine = false;
    bool validMove = false;
    bool valid;
    int maxHand = 0;
    int n, side;
    struct timespec ts;
    struct timespec tf;
    timespec_get(&ts, TIME_UTC);
    tessera peek;

    printHand(hand);

    while(!fine) {

        validMove = false;

        do {
            side = -1;
            valid = false;

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

            while(!valid && peek.l_cell != peek.r_cell) {
                fflush(stdin);
                printf("\nGirare la tessera? [Y/N] o [1/0]: ");
                scanf("%c", &c);
                if(c == 'y' || c == 'Y' || c == '1') {
                    peek = swapTessera(peek);
                    valid = true;
                }
                // else if(c == 'n' || c == 'N' || c=='0')
                else
                    valid = true;
            }

            while(side != 0 && side != 1 && field != NULL) {
                printf("\nScegliere il lato [Sinistra(%d) | Destra(%d)]: ", sx, dx);
                scanf("%d", &side);
            }
            // */
            
            if(isValidMove(field, peek, side))
                validMove = true;
            else
                printf("\nMossa non valida!\n");

        } while(!validMove);

        field = addToField(field, peek, side);
        removeTessera(hand, n);

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
        
        bestMove = findBestMove2(field, hand, 0);
        
        if(bestMove.n != -1) {
            field = addToField(field, bestMove.t, bestMove.side);
            hand = removeTessera(hand, bestMove.n);
        }

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

}

//  challenge
void challenge() {

    node* hand = createHandChallenge();

    if(hand != NULL) {
        result score = resolveChallenge(hand, (tessera){0,0}, (result){0,(char*)malloc(contaHand(hand)*6+1)});

        printf("%s", score.seq);
    }
}
