/*
 * SPMiniMaxNode.c
 *
 *      Author: Ariel
 */

#include "SPMiniMaxNode.h"

int memAllocFail = 0;


int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]) {
	assert(currentGame != NULL);
	int i = 0, possibleMoves = 0;
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		// If move is possible, set relevant entry in array to 1
		if (spFiarGameIsValidMove(currentGame, i) == true) {
			possibleMoves++;
			possbileStepsArr[i] = 1;
		}
	}
	return possibleMoves;
}

int findMinIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[],
		int sizeOfArr, int* minValueIn) {
	assert(possibleStepsValueArr != NULL);
	assert(possibleStepsArr != NULL);
	int i = 0, minValue = 0, minIndex = 0, flag = 0;
	// Find index of minimum value, using a single iteration with a flag for first value, depends if it is possible
	for (; i < sizeOfArr; ++i) {
		if (possibleStepsArr[i] == 1) {
			if (flag == 0) {
				minValue = possibleStepsValueArr[i];
				minIndex = i;
				flag = 1;
				continue;
			} else {
				if (possibleStepsValueArr[i] < minValue) {
					minValue = possibleStepsValueArr[i];
					minIndex = i;
				}
			}
		}
	}
	// Set minimum value to input pointed parameter
	*minValueIn = minValue;
	return minIndex;
}

int findMaxIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[],
		int sizeOfArr, int* maxValueIn) {
	assert(possibleStepsValueArr != NULL);
	assert(possibleStepsArr != NULL);
	int i = 0, maxValue = 0, maxIndex = 0, flag = 0;
	// Find index of maximum value, using a single iteration with a flag for first value, depends if it is possible
	for (; i < sizeOfArr; ++i) {
		if (possibleStepsArr[i] == 1) {
			if (flag == 0) {
				maxValue = possibleStepsValueArr[i];
				maxIndex = i;
				flag = 1;
				continue;
			} else {
				if (possibleStepsValueArr[i] > maxValue) {
					maxValue = possibleStepsValueArr[i];
					maxIndex = i;
				}
			}
		}
	}
	// Set maximum value to input pointed parameter
	*maxValueIn = maxValue;
	return maxIndex;
}

int spMiniMaxAlgorithm(SPFiarGame* currentGame, int depth) {
	int possibleSteps = 0, i = 0, j = 0, value = 0;
	char currentPlayer = currentGame->currentPlayer;
	int possbileStepsArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	int possbileStepsValueArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	// Calculate number of possible steps, and populate with 1's possible steps array
	possibleSteps = possibleMoves(currentGame, possbileStepsArr);

	// Create root's children, as number of possible steps
	SPFiarGame** rootChildren = (SPFiarGame**) malloc(
			possibleSteps * sizeof(SPFiarGame*));

	// If failed to allocate, return '-2'
	if (NULL == rootChildren) {
		memAllocFail = -2;
		return memAllocFail;
	}

	// for every column and if the play is possible and no allocation error has occurred
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (possbileStepsArr[i] == 1) {
			if (memAllocFail == 0) {
				rootChildren[j] = spFiarGameCopy(currentGame);
				if (NULL != rootChildren[j]) {
					spFiarGameSetMove(rootChildren[j], i);
					possbileStepsValueArr[i] = spMiniMaxHelper(rootChildren[j], depth,
							currentPlayer,
							true);
					spFiarGameDestroy(rootChildren[j]);
					j++;
				} else {
					// Allocation issue- set flat to '-2'
					memAllocFail = -2;
				}
			}
		}
	}
	// Destroy root node
	if (NULL != rootChildren) {
		free(rootChildren);
		rootChildren = NULL;
	}
	// If some allocation failed during the algorithm
	if (memAllocFail != 0) {
		return memAllocFail;
	}
	// Find index to the collumn to play
	return findMaxIndexAndValue(possbileStepsValueArr, possbileStepsArr,
	SP_FIAR_GAME_N_COLUMNS, &value);

}


// minOrMax - if min- true else- false
int spMiniMaxHelper(SPFiarGame* src, int depth, char currentPlayer,
		bool minOrMax) {
	assert(src != NULL);
	int possibleSteps = 0, i = 0, j = 0, newDepth = 0, value = 0, gameScore = 0;
	newDepth = depth - 1;
	int possbileStepsArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	int possbileStepsValueArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	possibleSteps = possibleMoves(src, possbileStepsArr);
	gameScore = gameScoringFunc(src, currentPlayer);
	if (newDepth
			== 0|| possibleSteps == 0 || gameScore == INT_MAX || gameScore == INT_MIN) {
		return gameScore;
	}
	// Create nodes's children, as number of possible steps
	SPFiarGame** children = (SPFiarGame**) malloc(
			possibleSteps * sizeof(SPFiarGame*));

	if (NULL == children) {
		memAllocFail = -2;
		return memAllocFail;
	}

	// Move i in child j
	// Number of children (j's) == Number of possibleSteps
	// for every column and if the play is possible and no allocation error has occurred
	for (; i < SP_FIAR_GAME_N_COLUMNS; ++i) {
		if (possbileStepsArr[i] == 1) {
			if (memAllocFail == 0) {
				children[j] = spFiarGameCopy(src);
				if (NULL != children[j]) {
					spFiarGameSetMove(children[j], i);
					possbileStepsValueArr[i] = spMiniMaxHelper(children[j], newDepth,
							currentPlayer, !minOrMax);
					spFiarGameDestroy(children[j]);
					j++;
				} else {
					memAllocFail = -2;
				}
			}
		}
	}
	// Free node's children array
	if (NULL != children) {
		free(children);
		children = NULL;
	}
	// If some memory allocation has occurred, return an error code
	if (memAllocFail != 0) {
		return memAllocFail;
	}
	// If it is a min node then return minimum value, o/w return maximum value
	if (minOrMax == true) {
		findMinIndexAndValue(possbileStepsValueArr, possbileStepsArr,
		SP_FIAR_GAME_N_COLUMNS, &value);
	} else {
		findMaxIndexAndValue(possbileStepsValueArr, possbileStepsArr,
		SP_FIAR_GAME_N_COLUMNS, &value);
	}
	return value;
}
