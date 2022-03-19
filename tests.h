#ifndef TESTS_H
#define TESTS_H

#include <string>
#include <iostream>
#include "generation.h"
#include "generation.cpp"

using namespace std;

 /**
  * a group of tests that validate the countCellNeighbors() function
  * testing function must have the prototype: int countCellNeighbors(bool board[ROWS][COLS], int r, int c);
  * @param none
  * @return none
  */
void testCountNeighbors();

 /**
  * a group of tests that validate the computeNextGeneration() function
  * testing function must have the prototype: void computeNextGeneration(bool board[ROWS][COLS]);
  * @param none
  * @return none
  */
void testComputeNextGeneration();

 /**
  * Runs all unit tests 
  * @param none
  * @return none
  */
void runUnitTests();

#endif