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
	if (NULL == returnGame) {
		return NULL;
	}
	returnGame->historyMoves = spArrayListCreate(historySize);
	if (NULL == returnGame->historyMoves) {
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
	if (NULL == src) {
		return NULL;
	}
	SPFiarGame* returnGame = spFiarGameCreate(src->historySize);
	if (NULL == returnGame) {
		return NULL;
	}
	returnGame->currentPlayer = src->currentPlayer;
	returnGame->historyMoves = spArrayListCopy(src->historyMoves);
	if (NULL == returnGame->historyMoves) {
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
	if (NULL == src) {
		return;
	}
	spArrayListDestroy(src->historyMoves);
	if (NULL != src) {
		free(src);
	}
	src = NULL;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (NULL == src || col >= SP_FIAR_GAME_N_COLUMNS) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}
	if (src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		rc = SP_FIAR_GAME_INVALID_MOVE;
		return rc;
	}
	src->gameBoard[src->tops[col]][col] = src->currentPlayer;
	// History is full- shift to left
	if (spArrayListSize(src->historyMoves) == src->historySize) {
		if (spArrayListRemoveFirst(src->historyMoves)
				!= SP_ARRAY_LIST_SUCCESS) {
			printf("DEBUG: EROOR in list remove last");
		}
	}
	if (spArrayListAddLast(src->historyMoves, col) != SP_ARRAY_LIST_SUCCESS) {
		printf("DEBUG: EROOR in list add");
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
	if (NULL == src || col >= SP_FIAR_GAME_N_COLUMNS) {
		return false;
	}
	if (src->tops[col] == SP_FIAR_GAME_N_ROWS) {
		return false;
	}
	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (NULL == src) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}
	if (spArrayListIsEmpty(src->historyMoves) == true) {
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
	if (lastMove == -1) {
		printf("DEBUG: ERROR in getting last in array list of historyMoves\n");
		return rc;
	}
	src->gameBoard[src->tops[lastMove] - 1][lastMove] =
	SP_FIAR_GAME_EMPTY_ENTRY;
	src->tops[lastMove]--;
	if (spArrayListRemoveLast(src->historyMoves) != SP_ARRAY_LIST_SUCCESS) {
		printf("DEBUG: error in remove list last");
	}
	return rc;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src) {
	SP_FIAR_GAME_MESSAGE rc = SP_FIAR_GAME_SUCCESS;
	if (NULL == src) {
		rc = SP_FIAR_GAME_INVALID_ARGUMENT;
		return rc;
	}

	int row = SP_FIAR_GAME_N_ROWS - 1;

	for (; row >= 0; row--) {

		printf("| %c %c %c %c %c %c %c |\n", src->gameBoard[row][0],
				src->gameBoard[row][1], src->gameBoard[row][2],
				src->gameBoard[row][3], src->gameBoard[row][4],
				src->gameBoard[row][5], src->gameBoard[row][6]);

	}
	printf("-----------------\n");
	printf("  1 2 3 4 5 6 7  \n");

	return rc;
}

char spFiarCheckWinner(SPFiarGame* src) {
	int result = 0;
	result = gameScoringFuncWinner(src);
	if (result == INT_MAX) {
		if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			return SP_FIAR_GAME_PLAYER_2_SYMBOL;
		} else {
			return SP_FIAR_GAME_PLAYER_1_SYMBOL;
		}
	}
	bool checkIfFull = true;
	int i = 0, j = 0;
	// TODO- improve complexity
	for (; i < SP_FIAR_GAME_N_ROWS; i++) {
		for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
			if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY) {
				checkIfFull = false;
			}
		}
	}
	if (checkIfFull == true) {
		return SP_FIAR_GAME_TIE_SYMBOL;
	}
	return '\0';
}

/* vector types:
 // 1- horizontal
 // 2- vertical
 // 3- diagonal \
// 4- diagonal / */
bool checkSpanVector(SPFiarGame* src, int r, int c, int vector,
		int sumSpanVec[], char currentPlayer) {
	int span = SP_FIAR_GAME_SPAN;
	char candidate = currentPlayer;
	int playerNumCnt = 0;
	int opponentNumCnt = 0;
	if ((candidate != SP_FIAR_GAME_PLAYER_1_SYMBOL)
			&& (candidate != SP_FIAR_GAME_PLAYER_2_SYMBOL)) {
		return false;
	}
	for (; span > 0; span--) {
		if (!((r < 6) && (r >= 0) && (c < 7) && (c >= 0))) {
			return false;
		}
		if (candidate == src->gameBoard[r][c]) {
			playerNumCnt++;
		}
		if ((candidate != src->gameBoard[r][c]) && (src->gameBoard[r][c] != SP_FIAR_GAME_EMPTY_ENTRY))  {
			opponentNumCnt++;
		}
		//printf("%d %d %c %d %d\n", c + 1, r + 1, src->gameBoard[r][c], span,
		//	spanCnt);

		if (vector == 1) {
			c++;
		}
		if (vector == 2) {
			r++;
		}
		if (vector == 3) {
			c--;
			r++;
		}
		if (vector == 4) {
			c++;
			r++;
		}
	}

	if (playerNumCnt == SP_FIAR_GAME_SPAN || opponentNumCnt == SP_FIAR_GAME_SPAN) {
		//printf("candidate is: %c\n", candidate);
		return true;
	} else if ((candidate == SP_FIAR_GAME_PLAYER_1_SYMBOL)
			|| (candidate == SP_FIAR_GAME_PLAYER_2_SYMBOL)) {
		if ((playerNumCnt - opponentNumCnt) == -3) {
			sumSpanVec[0]++;
		}
		if ((playerNumCnt - opponentNumCnt) == -2) {
			sumSpanVec[1]++;
		}
		if ((playerNumCnt - opponentNumCnt) == -1) {
			sumSpanVec[2]++;
		}
		if ((playerNumCnt - opponentNumCnt) == 1) {
			sumSpanVec[3]++;
		}
		if ((playerNumCnt - opponentNumCnt) == 2) {
			sumSpanVec[4]++;
		}
		if ((playerNumCnt - opponentNumCnt) == 3) {
			sumSpanVec[5]++;
		}

	}
	return false;
}

// TODO- bug in winner!!
int gameBoardScan(SPFiarGame* src, int sumSpanVec[], char currentPlayer) {

	bool winner = false;
	int vector = 1;
	int i = 0, j = 0;

	for (; vector < 5; vector++) {
		for (i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
			for (j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
				winner = checkSpanVector(src, i, j, vector, sumSpanVec, currentPlayer);
				if (winner == true) {
					if (src->gameBoard[i][j] != currentPlayer) {
						return INT_MIN;
					} else {
						return INT_MAX;
					}
				}
			}
		}
	}

	return '\0';
}


int gameScoringFuncWinner(SPFiarGame* currentGame) {
	int scoreVector[] = { -5, -2, -1, 1, 2, 5 };
	// This is {-3...3}
	int sumSpanVec[6] = { 0 };
	int result = 0;
	// HARDCODED
	int sizeOfSpanVec = 6;
	char currentPlayer;
	if (currentGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		currentPlayer =  SP_FIAR_GAME_PLAYER_2_SYMBOL;
	}else {
		currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}
	result = gameBoardScan(currentGame, sumSpanVec, currentPlayer);

	if (result == INT_MIN || result == INT_MAX) {
		return result;
	}
	result = 0;
	for (int i = 0; i < sizeOfSpanVec; i++) {
		//printf("sum of %d is %d\n", i, sumSpanVec[i]);
		result += ((scoreVector[i]) * (sumSpanVec[i]));
		//printf("result is %d\n" ,result);

	}
	return result;

}

int gameScoringFunc(SPFiarGame* currentGame, char currentPlayer) {
	int scoreVector[] = { -5, -2, -1, 1, 2, 5 };
	// This is {-3...3}
	int sumSpanVec[6] = { 0 };
	int result = 0;
	// HARDCODED
	int sizeOfSpanVec = 6;
	result = gameBoardScan(currentGame, sumSpanVec, currentPlayer);

	if (result == INT_MIN || result == INT_MAX) {
		return result;
	}
	result = 0;
	for (int i = 0; i < sizeOfSpanVec; i++) {
		//printf("sum of %d is %d\n", i, sumSpanVec[i]);
		result += ((scoreVector[i]) * (sumSpanVec[i]));
		//printf("result is %d\n" ,result);

	}
	return result;

}

char spFiarGameGetCurrentPlayer(SPFiarGame* src) {
	if (NULL == src) {
		return SP_FIAR_GAME_EMPTY_ENTRY;
	}
	if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		return SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}
	return SP_FIAR_GAME_PLAYER_2_SYMBOL;
}

