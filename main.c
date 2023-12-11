// 901828

#include "function.h"

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
