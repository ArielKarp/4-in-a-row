/*
 * SPMainAux.c
 *
 *  Created on: 9 áéåðé 2017
 *      Author: Ron
 */
#include "SPMainAux.h"

#define BUFFERSIZE 1024
char str[BUFFERSIZE] = "0";
SPCommand command;
int strToInt;

//check if the input is valid between 1 to 7
int checkValidInputNum(int num) {
	if (num < 1 || num > 7) {
		return false;
	}
	return true;
}

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
	printf("Remove disc: remove computer’s disc at column %d\n", col1);
	printf("Remove disc: remove user’s disc at column %d\n", col2);
	return 0;
}

int difficultyLevel() {
	strToInt = 0;
	do {
		printf("Please enter the difficulty level between [1-7]:\n");
		fgets(str, BUFFERSIZE, stdin);
		command = spParserPraseLine(str);
		if (command.cmd == SP_QUIT) {
			printf("quit..\n");
			exit(EXIT_SUCCESS);
		}
		//printf("1: %s\n", str);
		//printf("sss: %d\n", checkValidInputNum(atoi(str)));

		if (spParserIsInt(str)) {
			if (checkValidInputNum(atoi(str))) {
				strToInt = atoi(str);
				printf("Error: invalid level (should be between 1 to 7\n");
			}
		}
	} while ((command.cmd != SP_QUIT) || (!spParserIsInt(str))
			|| (!checkValidInputNum(strToInt)) || (strToInt == 0));

	printf("difficulty is %d:\n", strToInt);

	return strToInt;
}

void winnerPrint(char winner) {
	if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
		printf(
				"Game over: you win\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
	}

	if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
		printf(
				"Game over: computer wins\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
	}

	if (winner == SP_FIAR_GAME_TIE_SYMBOL) {
		printf(
				"Game over: it’s a tie\nPlease enter ‘quit’ to exit or ‘restart’ to start a new game!\n");
	}
}

int addDisc(SPFiarGame* game) {

	//command.cmd = atoi(strtok(NULL, " "));
	if (checkValidInputNum(command.arg)) {
		printf("Error: column number must be in range 1-7\n");
		return 0;
	}
	SP_FIAR_GAME_MESSAGE add = spFiarGameSetMove(game, command.arg);
	if (add == SP_FIAR_GAME_INVALID_MOVE) {
		printf("Error: column %d is full\n", command.arg);
		return 0;
	}
	if (add == SP_FIAR_GAME_INVALID_ARGUMENT) {
		printf("Error: invalid command\n");
		return 0;
	}
	printf("Computer move: add disc to column (%d)\n", command.arg);
	return 1;
}

char gamePlay(SPFiarGame* game, int difficulty) {
	char winner = '\0';
	while (winner == '\0') {

		spFiarGamePrintBoard(game);
		printf("Please make the next move:\n");
		fgets(str, BUFFERSIZE, stdin);
		command = spParserPraseLine(str);

		if (command.cmd == SP_QUIT) {
			printf("Exiting…\n");
			exit(EXIT_SUCCESS);
		}
		if (command.cmd == SP_RESTART) {
			difficulty = difficultyLevel();
			game = spFiarGameCreate(20);
			printf("Game restarted!\n");
		}
		if (command.cmd == SP_SUGGEST_MOVE) {
			int suggest = spMinimaxSuggestMove(game, difficulty);
			printf("Suggested move: drop a disc to column %d\n", suggest);
		}
		if (command.cmd == SP_UNDO_MOVE) {
			undoMove(game);
		}
		if (command.cmd == SP_ADD_DISC) {
			int addAnswer = addDisc(game);
			if (addAnswer == 0) {
				continue;
			}
			if (addAnswer == 1) {
				winner = spFiarCheckWinner(game);
				if (winner == '\0') {
					spFiarGameSetMove(game,
							spMinimaxSuggestMove(game, difficulty));
					winner = spFiarCheckWinner(game);
				}
			}
			if (command.cmd == SP_INVALID_LINE) {
				//command.cmd = atoi(strtok(NULL, " "));
				printf("Error: invalid command\n");
			}

		}
	}
	return winner;
}

void gameProgress(SPFiarGame* game) {
	char winner = '\0';
	int difficulty = difficultyLevel();
	game = spFiarGameCreate(20);
	winner = gamePlay(game, difficulty);
	winnerPrint(winner);
	fgets(str, BUFFERSIZE, stdin);
	command = spParserPraseLine(str);

	return;
}

