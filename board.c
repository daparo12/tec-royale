#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define BOARDX  5
#define BOARDY  5
#define BOARDW  (BOARDX*2)              // length of text line

char board [BOARDY][BOARDW+1];          // allow for string terminator

void print_board(void)
{
    int y, x;
    for(y=BOARDY-1; y>=0; y--) {
        printf("%-2d|%s\n", y, board[y]);
    }

    printf("   ");
    for(x=0; x<BOARDX; x++)
        printf(" -");
    printf("\n");

    printf("   ");
    for(x=0; x<BOARDX; x++)
        printf("%2d", x);
    printf("\n");
}

void empty_board(void)
{
    int y, x;
    for(y=0; y<BOARDY; y++) {
        for(x=0; x<BOARDW; x++) {
            board[y][x] = ' ';
        }
        board[y][x] = '\0';
    }
}

void poke_board(int x, int y, char c)
{
    if (y >= 0 && y < BOARDY && x >= 0 && x < BOARDX)
       board[y][x*2+1] = c;               // correctly spaced
}



int main(void)
{
    int posX[]= {2,4,2,1};
    int posY[]= {2,3,4,4};
    int len = sizeof(posX) / sizeof(posX[0]);
    int n;
    empty_board();
    for(n=0; n<len; n++) {

        poke_board(posX[n], posY[n], '*');
    }
    print_board();
    empty_board();
    print_board();
    return 0;
}
