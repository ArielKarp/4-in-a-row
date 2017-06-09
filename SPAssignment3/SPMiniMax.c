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
	// A cast from uint to int!!!
	return spMiniMaxAlgorithm(currentGame, maxDepth);
}
