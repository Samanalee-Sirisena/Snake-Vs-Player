#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "eatmake.h"

#define MAP_BORDER '*'
#define FOOD '@'
#define SNAKE '~'
#define PLAYER 'P'
#define MAP_PATH ' '

int main(int argc, char* argv[]) {
    /* Variable declarations */
    int a, b;
    int mrow, mcol, pcol, prow, scol, srow, fcol, frow;
    char **map;

    /* Argument check */
    if (argc != 3) {
        printf("Usage: %s <mrow> <mcol>\n", argv[0]);
        return 1;
    }

    /* Convert arguments to integers */
    mrow = atoi(argv[1]);
    mcol = atoi(argv[2]);

    /* Check if map size is valid */
    if (mrow <= 5 || mcol <= 5) {
        printf("Invalid size. Rows and columns size must be over 5.\n");
        return 1;
    }

    /* Allocate memory for the map */
    map = (char **)malloc(mrow * sizeof(char *));
    for (a = 0; a < mrow; a++) {
        map[a] = (char *)malloc(mcol * sizeof(char));
    }

    /* Initialize random number generator */
    initRandom();

    /* Place the player and snake randomly within the map boundaries */
    prow = randomUCP(1, mrow - 2);
    pcol = randomUCP(1, mcol - 2);
    srow = randomUCP(1, mrow - 2);
    scol = randomUCP(1, mcol - 2);

    /* Ensure the player and snake are not placed at the same position */
    while (prow == srow && pcol == scol) {
        prow = randomUCP(1, mrow - 2);
        pcol = randomUCP(1, mcol - 2);
    }

    /* Place the food randomly within the map boundaries */
    fcol = randomUCP(1, mcol - 2);
    frow = randomUCP(1, mrow - 2);

    /* Ensure the food is not placed at the same position as the player or snake */
    while ((fcol == pcol && frow == prow) || (fcol == scol && frow == srow)) {
        fcol = randomUCP(1, mcol - 2);
        frow = randomUCP(1, mrow - 2);
    }

    /* Initialize the map */
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


    /* Call make function */
    make(map, prow, pcol, mrow, mcol, srow, scol, frow, fcol);

    /* Free memory allocated for map */
    for (a = 0; a < mrow; a++) {
        free(map[a]);
    }
    free(map);

    return 0;
}
