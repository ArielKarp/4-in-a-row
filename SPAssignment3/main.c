/*
 * main.cSP_QUITz
 *
 *      Author: Ariel
 */
#include <stdio.h>
#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMainAux.h"
#include "SPMiniMax.h"

#define BUFFERSIZE 1024

int main() {
	SPCommand command;
	SPFiarGame* game = spFiarGameCreate(HISTORY_SIZE);
	if (NULL == game) {
		exceptionPrintAndExit(-2);
	}

	char str[BUFFERSIZE] = "0";
	char winner = '\0';
	int difficulty = 0;

	difficulty = difficultyLevel();
	if ((difficulty == -2) || (difficulty == -3)) {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(difficulty);
	}
	winner = gameProgress(game, difficulty);
	if (winner == 'e') {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(-3);
	}
	if (winner == 'r') {
		spFiarGameDestroy(game);
		game = spFiarGameCreate(HISTORY_SIZE);
		if (NULL == game) {
			exceptionPrintAndExit(-2);
		}
		difficulty = difficultyLevel();
		if ((difficulty == -2) || (difficulty == -3)) {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(difficulty);
		}
		winner = gameProgress(game, difficulty);
		if (winner == 'e') {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(-3);
		}
	}
	while (true) {
		char* input = fgets(str, BUFFERSIZE, stdin);
		if (NULL == input) {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(-3);
		}
		command = spParserPraseLine(str);
		if (command.cmd == SP_QUIT) {
			printf("Exiting...\n");
			spFiarGameDestroy(game);
			exit(EXIT_SUCCESS);
		}
		if (command.cmd == SP_RESTART) {
			printf("Game restarted!\n");
			spFiarGameDestroy(game);
			game = spFiarGameCreate(HISTORY_SIZE);
			if (NULL == game) {
				exceptionPrintAndExit(-2);
			}
			difficulty = difficultyLevel();
			if ((difficulty == -2) || (difficulty == -3)) {
				spFiarGameDestroy(game);
				exceptionPrintAndExit(difficulty);
			}
			winner = gameProgress(game, difficulty);
			if (winner == 'e') {
				spFiarGameDestroy(game);
				exceptionPrintAndExit(-3);
			}
			continue;
		}
		if (command.cmd == SP_SUGGEST_MOVE) {
			printf("Error: the game is over\n");
			continue;
		}
		if (command.cmd == SP_UNDO_MOVE) {
			if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
				undoMove(game);
				winner = gameProgress(game, difficulty);
				if (winner == 'e') {
					spFiarGameDestroy(game);
					exceptionPrintAndExit(-3);
				}
			} else {
				printf("Error: the game is over\n");
			}
		}
		if (command.cmd == SP_ADD_DISC) {
			printf("Error: the game is over\n");
		}
		if (command.cmd == SP_INVALID_LINE) {
			printf("Error: invalid command\n");
		}
	}
}
