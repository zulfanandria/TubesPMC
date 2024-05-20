#ifndef ASTAR_H
#define ASTAR_H

typedef struct
{
    int x, y;
} Point;

void findPath(char **maze, int baris, int kolom, Point start, Point end);
void findLongestPath(char **maze, int baris, int kolom, Point start, Point end);

#endif
