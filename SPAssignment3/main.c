/*
 * main.cSP_QUITz
 *
 *      Author: Ariel
 */
#include <stdio.h>
#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMainAux.h"

int main() {

#define BUFFERSIZE 1024
	int difficulty = 0;
	int init = 0;
	char str[BUFFERSIZE] = "0";
	SPCommand command;
	char winner = '\0';
	SPFiarGame* game = NULL;
	//char input;

	do {
		if (init > 0) {
			printf("Error: invalid level (should be between 1 to 7\n");
		}
		printf("Please enter the difficulty level between [1-7]:\n");
		fgets(str, BUFFERSIZE, stdin);
		command = spParserPraseLine(str);
		if (command.cmd == SP_QUIT) {
			printf("quit..\n");
		}
		//printf("1: %s\n", str);
		//printf("sss: %d\n", checkValidInputNum(atoi(str)));

		init++;
	} while ((command.cmd != SP_QUIT) && !spParserIsInt(str)
			&& !checkValidInputNum(atoi(str)));

	difficulty = atoi(str);

	printf("difficulty is %d:\n", difficulty);

	game = spFiarGameCreate(20);

	while (winner == '\0') {

		spFiarGamePrintBoard(game);
		printf("Please make the next move:\n");

		fgets(str, BUFFERSIZE, stdin);
		command = spParserPraseLine(str);

		if (command.cmd == SP_QUIT) {
			printf("Exiting…\n");
			break;
		}
		if (command.cmd == SP_RESTART) {
			printf("Game restarted!\n");
		}
		if (command.cmd == SP_SUGGEST_MOVE) {
			printf("Suggested move: drop a disc to column X\n");
		}

		if (command.cmd == SP_UNDO_MOVE) {
			printf("Remove disc: remove computer’s disc at column X\n");
			printf("Remove disc: remove user’s disc at column Y\n");
		}

		if (command.cmd == SP_ADD_DISC) {
			command.cmd = atoi(strtok(NULL, " "));
			printf("Computer move: add disc to column (xxx)\n");
		}

		winner = spFiarCheckWinner(game);

	}


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

	fgets(str, BUFFERSIZE, stdin);
	command = spParserPraseLine(str);

	//////////////ADD UNDO???????//////////////
	if (command.cmd == SP_QUIT) {
		printf("Exiting…\n");
	}
	if (command.cmd == SP_RESTART) {
		printf("Game restarted!\n");
	}

	spFiarGameDestroy(game);

	return 0;
}
