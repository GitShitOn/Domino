#include <stdio.h>
#include <unistd.h>

void msleep(int);

int max = 50;

int main() {
    for(int i=0; i<max+2;i++) {
        printf("\e[1;1H\e[2J");
        for(int y=0;y<max;y++) {
            if(y>=i)
                printf("|");
            else if(y==i-1)
                printf("/");
            else    
                printf("_");
        }
        printf("\n");
        msleep(100);
    }

    printf("\n");

    return 0;
}

void msleep(int time) {
    usleep(1000*time);
}
