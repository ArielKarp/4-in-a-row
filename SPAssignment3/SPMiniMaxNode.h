#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include "SPFIARGame.h"

//Put all decleartions and constants here

int spMiniMaxAlgorithm(SPFiarGame* currentGame, int depth);

int spMiniMaxHelper(SPFiarGame* src, int depth, bool minOrMax);

int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]);

int findMinIndexAndValue(int possibleStepsValueArr[], int sizeOfArr,
		int* minValueIn);
int findMaxIndexAndValue(int possibleStepsValueArr[], int sizeOfArr,
		int* maxValueIn);

#endif
