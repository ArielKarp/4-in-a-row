/*
 * SPMiniMaxNode.c
 *
 *      Author: Ariel
 */

#include "SPMiniMaxNode.h"

int possibleMoves(SPFiarGame* currentGame, int possbileStepsArr[]) {
	int i = 0, possibleMoves = 0;
	if (NULL == currentGame) {
		return -1;
	}
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (spFiarGameIsValidMove(currentGame, i) == true) {
			possibleMoves++;
			possbileStepsArr[i] = 1;
		}
	}
	return possibleMoves;
}

// Add NULL test for possibleStepsArr
int findMinIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[],
		int sizeOfArr, int* minValueIn) {
	int i = 0, minValue = 0, minIndex = 0, flag = 0;
	if (NULL == possibleStepsValueArr || sizeOfArr <= 0) {
		return -1;
	}
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
	*minValueIn = minValue;
	return minIndex;
}

int findMaxIndexAndValue(int possibleStepsValueArr[], int possibleStepsArr[],
		int sizeOfArr, int* maxValueIn) {
	int i = 0, maxValue = 0, maxIndex = 0, flag = 0;
	if (NULL == possibleStepsValueArr || sizeOfArr <= 0) {
		return -1;
	}
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
	*maxValueIn = maxValue;
	return maxIndex;
}

// think of better return numbers
// Runs the recursion inside to free the need to maintain the index of the col
int spMiniMaxAlgorithm(SPFiarGame* currentGame, int depth) {
	int possibleSteps = 0, i = 0, j = 0, value = 0;
	char currentPlayer = currentGame->currentPlayer;
	int possbileStepsArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	int possbileStepsValueArr[SP_FIAR_GAME_N_COLUMNS] = { 0 }; // Change first value and use possibleStepsArr
	if (NULL == currentGame) {
		return -1;
	}
	possibleSteps = possibleMoves(currentGame, possbileStepsArr);
	if (possibleSteps == -1) {
		return -1;
	}
	SPFiarGame** rootChildren = (SPFiarGame**) malloc(
			possibleSteps * sizeof(SPFiarGame*));
	if (NULL == rootChildren) {
		return -1;
	}
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		if (possbileStepsArr[i] == 1) {
			rootChildren[j] = spFiarGameCopy(currentGame);
			if (spFiarGameSetMove(rootChildren[j], i) != SP_FIAR_GAME_SUCCESS) {
				exit(1);
				// find a better return
			}
//			printf("Calling helper!");
			possbileStepsValueArr[i] = spMiniMaxHelper(rootChildren[j], depth,
					currentPlayer,
					true);
			spFiarGameDestroy(rootChildren[j]);
			j++;
		}
	}
	// Destroy root node
	if (NULL != rootChildren) {
		free(rootChildren);
		rootChildren = NULL;
	}
	// Find index to the collumn to play
	return findMaxIndexAndValue(possbileStepsValueArr, possbileStepsArr,
	SP_FIAR_GAME_N_COLUMNS, &value);

}

// think of better return numbers
// minOrMax - if min- true else- false
int spMiniMaxHelper(SPFiarGame* src, int depth, char currentPlayer,
		bool minOrMax) {
	int possibleSteps = 0, i = 0, j = 0, value = 0, newDepth = 0, gameScore = 0;
	newDepth = depth - 1;
	int possbileStepsArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	int possbileStepsValueArr[SP_FIAR_GAME_N_COLUMNS] = { 0 };
	possibleSteps = possibleMoves(src, possbileStepsArr);
	gameScore = gameScoringFunc(src, currentPlayer);
	if (newDepth
			== 0|| possibleSteps == 0 || gameScore == INT_MAX || gameScore == INT_MIN) {
		return gameScore;
	}
	SPFiarGame** children = (SPFiarGame**) malloc(
			possibleSteps * sizeof(SPFiarGame*));

	// Move i in child j
	// Number of children (j's) == Number of possibleSteps
	for (; i < SP_FIAR_GAME_N_COLUMNS; ++i) {
		if (possbileStepsArr[i] == 1) {
			children[j] = spFiarGameCopy(src);
			if (spFiarGameSetMove(children[j], i) != SP_FIAR_GAME_SUCCESS) {
				exit(1);
				// find a better return
			}
			possbileStepsValueArr[i] = spMiniMaxHelper(children[j], newDepth,
					currentPlayer, !minOrMax);
			spFiarGameDestroy(children[j]);
			j++;
		}
	}
	if (NULL != children) {
		free(children);
		children = NULL;
	}
	if (minOrMax == true) {
		findMinIndexAndValue(possbileStepsValueArr, possbileStepsArr,
		SP_FIAR_GAME_N_COLUMNS, &value);
	} else {
		findMaxIndexAndValue(possbileStepsValueArr, possbileStepsArr,
		SP_FIAR_GAME_N_COLUMNS, &value);
	}
	return value;
}
