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
	returnGame->historySize = historySize;
	initGameBoard(returnGame->gameBoard);
	initTops(returnGame->tops);
	returnGame->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	return returnGame;
}

void initGameBoard(char board[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS]) {
	int i = 0, j = 0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			board[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
		}
	}
}
void initTops(int tops[SP_FIAR_GAME_N_COLUMNS]) {
	int i = 0;
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		tops[i] = 0;
	}
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src) {
	if (src == NULL) {
		return NULL;
	}
	SPFiarGame* returnGame = spFiarGameCreate(src->historySize);
	if (returnGame == NULL) {
		return NULL;
	}
	returnGame->currentPlayer = src->currentPlayer;
	returnGame->historyMoves = spArrayListCopy(src->historyMoves);
	if (returnGame->historyMoves == NULL) {
		return NULL;
	}
	copyBoard(returnGame->gameBoard, src->gameBoard);
	copyTops(returnGame->tops, src->tops);
	return returnGame;
}

void copyBoard(char destBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS],
		char srcBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS]) {
	int i = 0, j = 0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			destBoard[i][j] = srcBoard[i][j];
		}
	}

}
void copyTops(int desTops[SP_FIAR_GAME_N_COLUMNS],
		int srcTops[SP_FIAR_GAME_N_COLUMNS]) {
	int i = 0;
	for (; i < SP_FIAR_GAME_N_COLUMNS; i++) {
		desTops[i] = srcTops[i];
	}
}

void spFiarGameDestroy(SPFiarGame* src) {
	if (src == NULL) {
		return;
	}
	spArrayListDestroy(src->historyMoves);
	src = NULL;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (src == NULL || col >= SP_FIAR_GAME_N_ROWS) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}
	if (src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		rc = SP_FIAR_GAME_INVALID_MOVE;
		return rc;
	}
	src->gameBoard[src->tops[col]][col] = src->currentPlayer;
	if (spArrayListAddLast(src->historyMoves, col) != SP_ARRAY_LIST_SUCCESS) {
		printf("DEBUG: EROOR in list addd");
	}
	// Change player's turn
	if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	} else {
		src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}
	src->tops[col]++;
	return rc;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col) {
	if (src == NULL || col >= SP_FIAR_GAME_N_ROWS) {
		return false;
	}
	if (src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		return false;
	}
	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (src == NULL) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}
	if (spArrayListIsEmpty(src->historyMoves)) {
		rc = SP_FIAR_GAME_NO_HISTORY;
		return rc;
	}
	// Change player's turn
	if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
	} else {
		src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}
	int lastMove = spArrayListGetLast(src->historyMoves);

	if (spArrayListRemoveLast(src->historyMoves) != SP_ARRAY_LIST_SUCCESS) {
		printf("DEBUG: error in remove list last");
	}
	return rc;
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
				src->gameBoard[line][1], src->gameBoard[line][2],
				src->gameBoard[line][3], src->gameBoard[line][4],
				src->gameBoard[line][5], src->gameBoard[line][6]);
	}
	printf("-----------------\n");
	printf("| 1 2 3 4 5 6 7 |\n");

	return rc;
}
