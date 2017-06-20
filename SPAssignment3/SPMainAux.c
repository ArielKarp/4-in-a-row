/*
 * SPMainAux.c
 *
 *  Created on: 9 ����� 2017
 *      Author: Ron
 */
#include "SPMainAux.h"

#define BUFFERSIZE 1024

//check if the input is valid between 1 to 7
int checkValidInputNum(int num) {
	if (num < 1 || num > 7) {
		return false;
	}
	return true;
}

//execute undo move function
int undoMove(SPFiarGame* game) {
	int col1 = 0;
	int col2 = 0;
	SP_FIAR_GAME_MESSAGE undo1;
	SP_FIAR_GAME_MESSAGE undo2;
	undo1 = spFiarGameUndoWithMove(game, &col1);
	if (undo1 != SP_FIAR_GAME_SUCCESS) {
		printf("Error: cannot undo previous move!\n");
		return 0;
	}
	undo2 = spFiarGameUndoWithMove(game, &col2);
	if (undo2 != SP_FIAR_GAME_SUCCESS) {
		printf("Error: cannot undo previous move!\n");
		return 0;
	}
	printf("Remove disc: remove computer's disc at column %d\n", col1 + 1);
	printf("Remove disc: remove user's disc at column %d\n", col2 + 1);
	return 1;
}

int difficultyLevel(SPFiarGame* game) {
	SPCommand command;
	char str[BUFFERSIZE] = "0";
	int strToInt = 0;
	do {
		strToInt = 0;
		printf("Please enter the difficulty level between [1-7]:\n");
		char* input = fgets(str, BUFFERSIZE, stdin);
		//exception catch in fgets
		if (NULL == input) {
			return -3;
		}
		command = spParserPraseLine(str);
		//exception catch in malloc
		if (command.cmd == SP_EXCEPTION) {
			return -2;
		}
		if (command.cmd == SP_QUIT) {
			printf("Exiting...\n");
			spFiarGameDestroy(game);
			exit(EXIT_SUCCESS);
		}
		if (spParserIsInt(str)) {
			strToInt = atoi(str);
			if (!checkValidInputNum(strToInt)) {
				printf("Error: invalid level (should be between 1 to 7)\n");

				strToInt = 0;
				continue;
			}

			else {
				break;
			}
		}
		else {
			printf("Error: invalid level (should be between 1 to 7)\n");
			strToInt = 0;
			continue;
		}
	} while ((command.cmd == SP_QUIT) || (strToInt == 0));

	return strToInt;
}

//prints the wineer
void winnerPrint(char winner) {
	if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		printf(
				"Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
	}
	if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
		printf(
				"Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
	}
	if (winner == SP_FIAR_GAME_TIE_SYMBOL) {
		printf(
				"Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
	}
}

//add disc to game board
int addDisc(SPFiarGame* game, SPCommand command) {
	if ((!(checkValidInputNum(command.arg))) || command.validArg == false) {
		printf("Error: column number must be in range 1-7\n");
		return 0;
	}
	SP_FIAR_GAME_MESSAGE add = spFiarGameSetMove(game, command.arg - 1);
	if (add == SP_FIAR_GAME_INVALID_MOVE) {
		printf("Error: column %d is full\n", command.arg);
		return 0;
	}
	if (add == SP_FIAR_GAME_INVALID_ARGUMENT) {
		printf("Error: invalid command\n");
		return 0;
	}
	return 1;
}

//while loop for the user vs computer game
char gamePlay(SPFiarGame* game, int difficulty) {
	SPCommand command;
	char str[BUFFERSIZE] = "0";
	char winner = '\0';
	int valid = 1;
	while (winner == '\0') {
		if (valid == 1) {
			spFiarGamePrintBoard(game);
			printf("Please make the next move:\n");
		}
		valid = 1;
		char* input = fgets(str, BUFFERSIZE, stdin);
		//exception catch in fgets
		if (NULL == input) {
			return 'e';
		}
		command = spParserPraseLine(str);
		if (command.cmd == SP_INVALID_LINE) {
			valid = 0;
			printf("Error: invalid command\n");
			continue;
		}
		if (command.cmd == SP_QUIT) {
			printf("Exiting...\n");
			return 'f';
		}
		if (command.cmd == SP_RESTART) {
			printf("Game restarted!\n");
			return 'r';
		}
		if (command.cmd == SP_SUGGEST_MOVE) {
			int suggest = spMinimaxSuggestMove(game, difficulty);
			valid = 0;
			printf("Suggested move: drop a disc to column %d\n", suggest + 1);
			continue;
		}
		if (command.cmd == SP_UNDO_MOVE) {
			valid = undoMove(game);
			continue;
		}
		//add disc to game board, if it is computer turn it uses suggestMove function to chose where to add disc
		//continue until there is a winner
		if (command.cmd == SP_ADD_DISC) {
			int addAnswer = addDisc(game, command);
			if (addAnswer == 0) {
				valid = 0;
				continue;
			}
			if (addAnswer == 1) {
				winner = spFiarCheckWinner(game);
				if (winner == '\0') {
					int suggest = spMinimaxSuggestMove(game, difficulty);
					spFiarGameSetMove(game, suggest);
					printf("Computer move: add disc to column %d\n",
							suggest + 1);
					winner = spFiarCheckWinner(game);
					if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
						spFiarGamePrintBoard(game);
					}
				}
			}

		}
	}
	return winner;
}

//return winner to main function
// r- restart, e- error, f- quit
char gameProgress(SPFiarGame* game, int difficulty) {
	char winner = '\0';
	winner = gamePlay(game, difficulty);
	if (winner == 'r') {
		return winner;
	}
	if (winner == 'e') {
		return 'e';
	}
	if (winner == 'f') {
		return winner;
	}
	winnerPrint(winner);

	return winner;
}

//print exception and exit the game
void exceptionPrintAndExit(int functionType) {
	char* exceptionName = NULL;
	if (functionType == -2) {
		exceptionName = "malloc";
	} else if (functionType == -3) {
		exceptionName = "fgets";
	}
	printf("Error: %s has failed", exceptionName);
	printf("Exiting...\n");
	exit(EXIT_SUCCESS);
}

void checkIfGameProgressReturnedError(SPFiarGame* game, char errorCode) {
	// Check for error code
	if (errorCode == 'e') {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(-3);
	}
}

void checkIfDifficulyLevelFailed(SPFiarGame* game, int errorCode) {
	if ((errorCode == -2) || (errorCode == -3)) {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(errorCode);
	}
	return;
}


void checkIfFgetsFailed(SPFiarGame* game, char* returnFgets) {
	// Check if fgets failed
	if (NULL == returnFgets) {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(-3);
	}
	return;
}

void checkIfGameCrateFailed(SPFiarGame* game) {
	// Check if create game failed
	if (NULL == game) {
		exceptionPrintAndExit(-2);
	}
	return;
}

char restartGame(SPFiarGame* game) {
	int difficulty = 0;
	char winner = '\0';
	checkIfGameCrateFailed(game);
	difficulty = difficultyLevel(game);
	checkIfDifficulyLevelFailed(game, difficulty);
	winner = gameProgress(game, difficulty);
	checkIfGameProgressReturnedError(game, winner);
	return winner;
}
