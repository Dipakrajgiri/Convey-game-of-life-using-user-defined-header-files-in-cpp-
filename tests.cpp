#include "tests.h"

#include <vector>

struct Coordinate {
    int row;
    int col;
};


/**
  * Utility function that will generate a list of occupied cells for a given generation
  * 
  * NOTE! For the curious and clever student, you may NOT use this methodology
  * to compute generations.  See the canvas assignment page for the intended
  * purpose of this exercise.  This technique is only used to verify 
  * the correctness of your implementation
 
  * @param generation id of the generation to generate
  * @return a list of cells that should be occupied
*/
vector<Coordinate> getGenerationOccupiedCells(int generation) {
    Coordinate occupiedGenerationCells[4][5] = {
        { {0,1}, {1,2}, {2,0}, {2,1}, {2,2} },  // generation 1
        { {1,0}, {1,2}, {2,1}, {2,2}, {3,1} },  // generation 2
        { {1,2}, {2,0}, {2,2}, {3,1}, {3,2} },  // generation 3
        { {1,1}, {2,2}, {2,3}, {3,1}, {3,2} }   // generation 4
    };  
    vector<Coordinate> occupiedCells;
    if (generation >= 0) {
        int shift = generation / 4;
        for (int i = 0; i < 5; i++) {
            int row = occupiedGenerationCells[generation % 4][i].row + shift;
            int col = occupiedGenerationCells[generation % 4][i].col + shift;
            occupiedCells.push_back( { row,col });
        }
    }
    return occupiedCells;
}

/**
  * Utility function that will reset the 2d board to specified generation configuration
  * @param board the 2d array to be reset
  * @param expectedOccupants a list of cells that should be occupied
  * @return none
*/
void resetBoard(bool board[ROWS][COLS], vector<Coordinate> expectedOccupants) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            board[i][j] = false;
        }
    }
    for(unsigned int i = 0; i < expectedOccupants.size(); i++) {
        int row = expectedOccupants[i].row;
        int col = expectedOccupants[i].col;
        board[row][col] = true;
    }
}
/**
  * Utility function that will reset the 2d board to specified generation configuration
  * @param board the 2d array to be reset
  * @param generation the generation to set the board to, negative if the board should be completely empty.
  * @return none
*/
void resetBoard(bool board[ROWS][COLS], int generation = -1) {
    vector<Coordinate> expectedOccupants = getGenerationOccupiedCells(generation);
    resetBoard(board, expectedOccupants);
}

/**
  * tests a boolean expression if it is true, if false it will output to cout the 
  * provided description string 
  * @param test boolean expression to evaluate
  * @param description descriptive statement of test if the test expression evaluates to false
  * @return 0 if test passed, 1 if test failed
*/
int assert(bool test, string description) {
    if (!test) {
        cout << "Failed Test: " << description << endl;
        return 1;
    }
    return 0;
} 

/**
  * Utility function that will validate the board for an expected
  * occupied cells for a particular generation
  * @param board to test
  * @param expectedOccupants a list of converted coordinates (row*ROWS + col) of cells that should be occupied
  * @param message a message to print for a failed assertion
  * @return count of tests that fail the expected generation
  */
int validateBoard(bool board[ROWS][COLS], vector<Coordinate> expectedOccupants, string message) {
    int failed = 0;
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            bool isExpectedOccupant = false;
            for(unsigned int i = 0; i < expectedOccupants.size(); i++) {
                if (expectedOccupants[i].row == row && expectedOccupants[i].col == col) {
                    isExpectedOccupant = true;
                    break;
                }
            }
            if (isExpectedOccupant) {
                failed += assert(board[row][col], message + " - should be occupied: " + to_string(row) + "," + to_string(col));    
            }
            else {
                failed += assert(!board[row][col], message + " - should be empty: " + to_string(row) + "," + to_string(col));    
            }
        }
    }
  
    return failed;  
}

void testPrintBoard(char c) {
    bool board[ROWS][COLS] = {{false}};
    string line(COLS, ' ');
    line += '\n';
    string blank = "";
    for (int i = 0; i < ROWS; i++) blank += line;
   
    int failedTests = 0;
    failedTests += assert(printBoard(board) == blank, "printBoard - blank board");

    board[0][0] = true;
    string singleTest(blank);
    singleTest[0] = c;
    failedTests += assert(printBoard(board) == singleTest, "printBoard - single cell");
    
    resetBoard(board, 0);
    string gen1Test(blank);
    gen1Test[1] = c;
    gen1Test[23] = c;
    gen1Test[42] = c;    
    gen1Test[43] = c;    
    gen1Test[44] = c;    
    failedTests += assert(printBoard(board) == gen1Test, "printBoard - generation 1");  
    
    resetBoard(board, 1);
    string gen2Test(blank);
    gen2Test[21] = c;
    gen2Test[23] = c;
    gen2Test[43] = c;    
    gen2Test[44] = c;    
    gen2Test[64] = c;    
    failedTests += assert(printBoard(board) == gen2Test, "printBoard - generation 2"); 
 
    string result = (failedTests > 0) ? to_string(failedTests) + " failed test(s)" : "Success!"; 
    cout << "All printBoard Tests Finished: " << result << endl;
}

void testCountNeighbors() {
    bool board[ROWS][COLS] = {{false}};
    
    board[1][2] = true;
    board[2][3] = true;
    board[3][1] = true;
    board[3][2] = true;
    board[3][3] = true;
    
    int failedTests = 0;
    failedTests += assert(countCellNeighbors(board,0,0) == 0, "countCellNeighbors - corner1");
    failedTests += assert(countCellNeighbors(board,0,COLS-1) == 0, "countCellNeighbors - corner2");
    failedTests += assert(countCellNeighbors(board,ROWS-1,0) == 0, "countCellNeighbors - corner3");
    failedTests += assert(countCellNeighbors(board,ROWS-1,COLS-1) == 0, "countCellNeighbors - corner4");
    
    failedTests += assert(countCellNeighbors(board,3,0) == 1, "countCellNeighbors - left side interior");
    failedTests += assert(countCellNeighbors(board,0,2) == 1, "countCellNeighbors - top side interior");
    failedTests += assert(countCellNeighbors(board,ROWS-1,10) == 0, "countCellNeighbors - bottom side interior");
    failedTests += assert(countCellNeighbors(board,10,COLS-1) == 0, "countCellNeighbors - right side interior");
    
    failedTests += assert(countCellNeighbors(board,2,2) == 5, "countCellNeighbors - interior multiple - center empty");
    failedTests += assert(countCellNeighbors(board,3,2) == 3, "countCellNeighbors - interior multiple - center occupied");
    
    string result = (failedTests > 0) ? to_string(failedTests) + " failed test(s)" : "Success!"; 
    cout << "All countCellNeighbors Tests Finished: " << result << endl;
}

void testComputeNextGeneration() {
    bool board[ROWS][COLS] = {{false}};
    int failedTests = 0;

    // now test each generation, every 4th generation the cells get shifted down, over
    for(int gen = 0; gen < 64; gen++) {
        // setup test generation data and expected outcome data
        vector<Coordinate> start = getGenerationOccupiedCells(gen);
        vector<Coordinate> end = getGenerationOccupiedCells(gen+1);
        resetBoard(board, start);
        computeNextGeneration(board);
        failedTests += validateBoard(board, end, "computeNextGeneration - " + to_string(gen) + "->" + to_string(gen+1));
        if (failedTests >= 10) {
            cout << "Maximum errors reached testing computeNextGeneration, skipping remainder of tests..." << endl;
            break;
        }
    }
    
    string result = (failedTests > 0) ? to_string(failedTests) + " failed test(s)" : "Success!"; 
    cout << "All computeNextGeneration Tests Finished: " << result << endl;
}

void runUnitTests() {
    testPrintBoard(178);
    testCountNeighbors();
    testComputeNextGeneration();
    cout << "All Unit Tests Finished" << endl;
}
