/*
 * main.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */
#include <stdio.h>
#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMainAux.h"
#include "SPMiniMax.h"

#define BUFFERSIZE 1024

int main() {
	//create SPCommand and SPFiarGame
	SPCommand command;
	SPFiarGame* game = spFiarGameCreate(HISTORY_SIZE);
	//exception catch in fgets
	checkIfGameCrateFailed(game);
	//init variables
	char str[BUFFERSIZE] = "0";
	char winner = '\0';
	int difficulty = 0;

	difficulty = difficultyLevel(game);
	checkIfDifficulyLevelFailed(game, difficulty);
	winner = gameProgress(game, difficulty);
	// Commence 'Quit' if requested
	if (winner == 'f') {
		spFiarGameDestroy(game);
		exit(EXIT_SUCCESS);
	}
	// Check for memory allocation errors
	checkIfGameProgressReturnedError(game, winner);

	//restart game
	while (winner == 'r') {
		spFiarGameDestroy(game);
		game = spFiarGameCreate(HISTORY_SIZE);
		winner = restartGame(game);
		// Commence 'Quit' if requested
		if (winner == 'f') {
			spFiarGameDestroy(game);
			exit(EXIT_SUCCESS);
		}
	}
	//while loop game
	while (true) {
		//get input from the user
		char* input = fgets(str, BUFFERSIZE, stdin);
		//exception catch in fgets
		checkIfFgetsFailed(game, input);
		command = spParserPraseLine(str);
		//quit the game
		if (command.cmd == SP_QUIT) {
			printf("Exiting...\n");
			spFiarGameDestroy(game);
			exit(EXIT_SUCCESS);
		}
		//restart the game
		if (command.cmd == SP_RESTART) {
			printf("Game restarted!\n");
			spFiarGameDestroy(game);
			game = spFiarGameCreate(HISTORY_SIZE);
			restartGame(game);
			continue;
		}
		//user input is suggest move command
		if (command.cmd == SP_SUGGEST_MOVE) {
			printf("Error: the game is over\n");
			continue;
		}
		//user input is undo move command
		if (command.cmd == SP_UNDO_MOVE) {
			if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
				undoMove(game);
				winner = gameProgress(game, difficulty);
				checkIfGameProgressReturnedError(game, winner);
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
