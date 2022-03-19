#ifndef GENERATION_H
#define GENERATION_H
#include <iostream>
#define ROWS 20
#define COLS 20
using namespace std;
int countCellNeighbors(bool board[ROWS][COLS], int r, int c);
string printBoard(bool board[ROWS][COLS]);
void computeNextGeneration(bool board[ROWS][COLS]);
#endif