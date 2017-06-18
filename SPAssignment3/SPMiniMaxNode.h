#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include <assert.h>
#include "SPFIARGame.h"


//Put all decleartions and constants here

// Defines a flag to catch an error
extern int memAllocFail;

int spMiniMaxAlgorithm(SPFiarGame* currentGame,int depth);

int spMiniMaxHelper(SPFiarGame* src, int depth, char currentPlayer,
		bool minOrMax);

int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]);

int findMinIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* minValueIn);
int findMaxIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* maxValueIn);

#endif
