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
	SPFiarGame* game = NULL;

	gameProgress(game);

	if (command.cmd == SP_QUIT) {
		printf("Exiting…\n");
		spFiarGameDestroy(game);
		exit(EXIT_SUCCESS);
	}
	if (command.cmd == SP_RESTART) {
		printf("Game restarted!\n");
		gameProgress(game);
	}
	if (command.cmd == SP_SUGGEST_MOVE) {
		printf("Error: the game is over\n");
	}
	if (command.cmd == SP_UNDO_MOVE) {
		if (game->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			undoMove(game);
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

	return 0;
}
