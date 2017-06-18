/*
 * SPMiniMax.c
 *
 *      Author: Ariel
 */

#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth) {
	if (NULL == currentGame || maxDepth <= 0) {
		return -1;
	}
	// if MiniMax failed in memory allocation- return -2
	return spMiniMaxAlgorithm(currentGame, maxDepth);
}
