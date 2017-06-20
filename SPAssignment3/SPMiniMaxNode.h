#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include <assert.h>
#include "SPFIARGame.h"


//Put all decleartions and constants here

// Defines a flag to catch an error
extern int memAllocFail;

/**
 * Main function that calculates  suggest's move column
 * @param currentGame- current game board
 * @param depth- number between 1 to 7
 * @return column in 0-based
 */
int spMiniMaxAlgorithm(SPFiarGame* currentGame,int depth);

/**
 * In MiniMax tree, compute node's value
 * @param src- source game board
 * @param depth- current depth as defined in MiniMax algorithm
 * @param currentPlayer- symbol of the player that initiated MiniMax algorithm
 * @param minOrMax- for every depth in the tree, alternate between min or max nodes
 * @return tree node value
 */
int spMiniMaxHelper(SPFiarGame* src, int depth, char currentPlayer,
		bool minOrMax);

/**
 * Return number of possible moves, for every possible move i in (0 to 6), set possibleStrpsArr[i] to 1
 * @param currentGame- current game board
 * @param possbileStepsArr- array to be set with 1's for every possible move
 * @return number of possible moves
 */
int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]);

/**
 * Return index of minimum value in possible steps value array
 * @param possibleStepsValueArr- array containing values of every possible step (i.e. value of node in MiniMax tree)
 * @param possibleStepsArr- array containing possible moves (if entry in 1, o/w 0)
 * @param sizeOfArr- size of arrays
 * @param minValueIn- pointer to integer to minimum value itself
 * @return index of minimum value if possible steps value array
 */
int findMinIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* minValueIn);

/**
 * Return index of maximum value in possible steps value array
 * @param possibleStepsValueArr- array containing values of every possible step (i.e. value of node in MiniMax tree)
 * @param possibleStepsArr- array containing possible moves (if entry in 1, o/w 0)
 * @param sizeOfArr- size of arrays
 * @param maxValueIn- pointer to integer to maximum value itself
 * @return index of maximum value if possible steps value array
 */
int findMaxIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* maxValueIn);

#endif
