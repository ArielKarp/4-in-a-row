/*
 * SPFIARHame.c
 *
 *      Author: Ariel
 */

#include "SPFIARGame.h"

SPFiarGame* spFiarGameCreate(int historySize) {
	if (historySize <= 0) {
		return NULL;
	}
	SPFiarGame* returnGame = (SPFiarGame*)malloc(sizeof(SPFiarGame));
	if (returnGame == NULL) {
		return NULL;
	}
	returnGame->historyMoves = spArrayListCreate(historySize);
	if (returnGame->historyMoves == NULL) {
		return NULL;
	}
	initGameBoard(returnGame->gameBoard);
	returnGame->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	return returnGame;
}

void initGameBoard(char board[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS]) {
	int i, j =0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for(;j < SP_FIAR_GAME_N_COLUMNS; i++) {
			board[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
		}
	}
}


