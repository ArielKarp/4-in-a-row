/*
 * SPMainAux.c
 *
 *  Created on: 9 αιεπι 2017
 *      Author: Ron
 */
#include "SPMainAux.h"

#define BUFFERSIZE 1024
char str[BUFFERSIZE] = "0";
SPCommand command;
int strToInt = 0;

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

int difficultyLevel() {
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
int addDisc(SPFiarGame* game) {

	//command.cmd = atoi(strtok(NULL, " "));
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
			exit(EXIT_SUCCESS);
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
		//add disc to game board, if it is computer turn it usses suggestMove function to chose where to add disc
		//continue until there is a winner
		if (command.cmd == SP_ADD_DISC) {
			int addAnswer = addDisc(game);
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
char gameProgress(SPFiarGame* game, int difficulty) {
	char winner = '\0';
	winner = gamePlay(game, difficulty);
	if (winner == 'r') {
		return winner;
	}
	if (winner == 'e') {
		return 'e';
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
