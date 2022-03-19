#include"generation.h"
 #include <iostream>
#include"generation.h"
#define ROWS 20
#define COLS 20
using namespace std;
int countCellNeighbors(bool board[ROWS][COLS], int r, int c);
string printBoard(bool board[ROWS][COLS]);
void computeNextGeneration(bool board[ROWS][COLS]); 
int countCellNeighbors(bool board[ROWS][COLS], int r, int c)
{
    int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++)
    {
        for (j = c - 1; j <= c + 1; j++)
        {
            if ((i == r && j == c) || (i < 0 || j < 0) || (i >= ROWS || j >= COLS))
            {
                continue;
            }
            if (board[i][j] == true)
            {
                count++;
            }
        }
    }
    return count;
}
string printBoard(bool board[ROWS][COLS])
{
    int p = 0;
    string stboard;
    char chboard[400];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == true)
            {
                chboard[p] = char(178);
                p++;
            }
            else
            {
                chboard[p] = '*';
                p++;
            }
        }
    }
    stboard = chboard;
    return stboard;
}
void computeNextGeneration(bool board[ROWS][COLS])
{
    bool toggle[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int num = countCellNeighbors(board, i, j);
            if (board[i][j] == true && (num == 2 || num == 3))
            {
                toggle[i][j] = true;
            }

            else if (board[i][j] == false && num == 3)
            {
                toggle[i][j] = true;
            }

            else
            {
                toggle[i][j] = false;
            }
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {

            board[i][j] = toggle[i][j];
        }
    }
}
