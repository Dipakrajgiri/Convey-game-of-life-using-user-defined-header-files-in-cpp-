#include <iostream>
#include <iomanip>
#include <windows.h>
#include "generation.h"
#include "generation.cpp"
#include "tests.h"
#include "tests.cpp"

using namespace std;

/**
 * Utility function that will clear the console screen, this will only work on Windows
 * and requires a #include <windows.h>
 * Reference: https://www.cplusplus.com/articles/4z18T05o/
 * @param none
 * @return none
 */
void ClearScreen()
{

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (hStdOut != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Calculate how big the buffer
        DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        // Fill the entire buffer with spaces
        COORD homeCoords = {0, 0};
        DWORD count;
        if (FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        {
            // Fill the entire buffer with the current colors and attributes
            if (FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
            {
                // Move the cursor home
                SetConsoleCursorPosition(hStdOut, homeCoords);
            }
        }
    }
}

int main()
{
    // Note! When you first compile this it will not work until you at least
    // create your generation.h and generation.cpp and minimally satisfy the
    // interfaces in generation.h -- see the assignment
    runUnitTests();
    // You will also note after you successfully compile it, your unit tests
    // will fail because you haven't completed the implementation.

    // TODO:  Now create an animation for the first 64 generations!
    // See the assignment page for detailed requirements!

    bool board[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = false;
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 1) || (i == 2 && j == 2))
            {
                board[i][j] = true;
                cout << board[i][j];
            }
        }
    }
    for (int i = 0; i < 64; i++)
    {
        ClearScreen(); 
         cout << "this is generation : " << i + 1;
        cout << endl;
         for (int j = 0; j < 400; j++)
        {
           if(j%20==0)
           {
               cout<<"\n";
           }
           cout << printBoard(board)[j]<<" ";
        }
        cout<<endl;
    Sleep(100);
    computeNextGeneration(board);
    }
    return 0;
}