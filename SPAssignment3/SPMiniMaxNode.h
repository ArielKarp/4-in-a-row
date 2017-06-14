#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include "SPFIARGame.h"

extern int cout_num_of_rec;
//Put all decleartions and constants here

int spMiniMaxAlgorithm(SPFiarGame* currentGame, int depth);

int spMiniMaxHelper(SPFiarGame* src, int depth, char currentPlayer, bool minOrMax);

int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]);

int findMinIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* minValueIn);
int findMaxIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[], int sizeOfArr,
		int* maxValueIn);

#endif
