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
	char str[BUFFERSIZE] = "0";
	char winner = '\0';
	int difficulty = 0;

	difficulty = difficultyLevel();
	winner = gameProgress(game, difficulty);

	if (winner == 'r'){
		spFiarGameDestroy(game);
		game = spFiarGameCreate(HISTORY_SIZE);
		difficulty = difficultyLevel();
		winner = gameProgress(game, difficulty);
	}

	while (true) {
		fgets(str, BUFFERSIZE, stdin);
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
			difficulty = difficultyLevel();
			winner = gameProgress(game, difficulty);
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
			} else {
				printf("Error: the game is over\n");
			}
		}
		if (command.cmd == SP_ADD_DISC) {
			printf("Error: the game is over\n");
		}
		if (command.cmd == SP_INVALID_LINE) {
			//command.cmd = atoi(strtok(NULL, " "));
			printf("Error: invalid command\n");
		}
	}
}
