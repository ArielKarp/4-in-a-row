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
	int i, j = 0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (; j < SP_FIAR_GAME_N_COLUMNS; i++) {
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


void copyBoard(char destBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS], char srcBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS]) {
	int i, j = 0;
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (; j < SP_FIAR_GAME_N_COLUMNS; i++) {
			destBoard[i][j] = srcBoard[i][j];
		}
	}

}
void copyTops(int desTops[SP_FIAR_GAME_N_COLUMNS], int srcTops[SP_FIAR_GAME_N_COLUMNS]) {
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
	if(src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		rc = SP_FIAR_GAME_INVALID_MOVE;
		return rc;
	}
	src->gameBoard[src->tops[col]][col] = src->currentPlayer;
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
	if(src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		return false;
	}
	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src) {

}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {

}
