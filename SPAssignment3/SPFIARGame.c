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
	SPFiarGame* returnGame = (SPFiarGame*) malloc(sizeof(SPFiarGame));
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
	int i, j = 0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (; j < SP_FIAR_GAME_N_COLUMNS; i++) {
			board[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
		}
	}
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (src == NULL) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}

	int line = SP_FIAR_GAME_N_ROWS;
	for (; line > 0; line--) {
		printf("| %c %c %c %c %c %c %c |\n", src->gameBoard[line][0],
				src->gameBoard[line][1], src->gameBoard[line][2], src->gameBoard[line][3],
				src->gameBoard[line][4], src->gameBoard[line][5],src->gameBoard[line][6]);
	}
	printf("-----------------\n");
	printf("| 1 2 3 4 5 6 7 |\n");

	return rc;
}
