#include <stdio.h>
#include <stdlib.h>
#include "eatmake.h"
#include "random.h"
#include "terminal.h"

void make(char **map, int prow, int pcol, int mrow, int mcol, int srow, int scol, int frow, int fcol) {
    /* Define constants */
    #define MAP_BORDER '*'
    #define FOOD '@'
    #define SNAKE '~'
    #define PLAYER 'P'
    #define MAP_PATH ' '

    int a, b;

    while (1) {
        system("clear");

        /* Update map */
        for (a = 0; a < mrow; a++) {
            for (b = 0; b < mcol; b++) {
                if (a == 0 || a == mrow - 1 || b == 0 || b == mcol - 1) {
                    map[a][b] = MAP_BORDER;
                } else if (a == prow && b == pcol) {
                    map[a][b] = PLAYER;
                } else if (a == srow && b == scol) {
                    map[a][b] = SNAKE;
                } else if (a == frow && b == fcol) {
                    map[a][b] = FOOD;
                } else {
                    map[a][b] = MAP_PATH;
                }
            }
        }

        /* Display map */
        for (a = 0; a < mrow; a++) {
            for (b = 0; b < mcol; b++) {
                printf("%c", map[a][b]);
            }
            printf("\n");
        }

        printf("Press w to go up\n");
        printf("Press s to go down\n");
        printf("Press a to go left\n");
        printf("Press d to go right\n");

        movePlayer(map, &prow, &pcol, mrow, mcol, srow, scol, frow, fcol);
        snakeMove(map, &srow, &scol, mrow, mcol, frow, fcol);

        /* Check if snake eats player */
        if (srow == prow && scol == pcol) {
            printf("You Lost.Try again\n");
            break;
        }

        /* Check if player eats food */
        if (prow == frow && pcol == fcol) {
            printf("Congrats.You won");
            break;
        }
    }
}

void movePlayer(char **map, int *prow, int *pcol, int mrow, int mcol, int srow, int scol, int frow, int fcol) {
    int new_prow, new_pcol;
    char button;

    new_prow = *prow;
    new_pcol = *pcol;

    disableBuffer();
    scanf(" %c", &button);
    enableBuffer();

    if (button == 'w' && *prow > 1) {
        new_prow--;
    } else if (button == 's' && *prow < mrow - 2) {
        new_prow++;
    } else if (button == 'a' && *pcol > 1) {
        new_pcol--;
    } else if (button == 'd' && *pcol < mcol - 2) {
        new_pcol++;
    }

    if (map[new_prow][new_pcol] != MAP_BORDER) {
        *prow = new_prow;
        *pcol = new_pcol;
    }
}

void snakeMove(char **map, int *srow, int *scol, int mrow, int mcol, int frow, int fcol) {
    int way;
    initRandom();

    do {
        way = randomUCP(1, 8);

        if (way == 1 && *srow > 1) {
            (*srow)--;
        } else if (way == 2 && *srow < mrow - 2) {
            (*srow)++;
        } else if (way == 3 && *scol > 1) {
            (*scol)--;
        } else if (way == 4 && *scol < mcol - 2) {
            (*scol)++;
        } else if (way == 5 && *srow > 1 && *scol > 1) {
            (*srow)--;
            (*scol)--;
        } else if (way == 6 && *srow > 1 && *scol < mcol - 2) {
            (*srow)--;
            (*scol)++;
        } else if (way == 7 && *srow < mrow - 2 && *scol > 1) {
            (*srow)++;
            (*scol)--;
        } else if (way == 8 && *srow < mrow - 2 && *scol < mcol - 2) {
            (*srow)++;
            (*scol)++;
        }

    } while (*srow == frow && *scol == fcol);
}
