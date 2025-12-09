#ifndef EATMAKE_H
#define EATMAKE_H

void make(char ** map,int prow,int pcol,int mrow,int mcol,int srow,int scol,int frow,int fcol);

void movePlayer(char ** map,int *prow,int *pcol,int mrow,int mcol,int srow,int scol,int frow,int fcol);

void snakeMove(char **map, int *srow, int *scol, int mrow, int mcol, int frow, int fcol);

#endif
