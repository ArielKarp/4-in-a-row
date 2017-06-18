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
	//create SPCommand and SPFiarGame
	SPCommand command;
	SPFiarGame* game = spFiarGameCreate(HISTORY_SIZE);
	//exception catch in fgets
	if (NULL == game) {
		exceptionPrintAndExit(-2);
	}
	//init variables
	char str[BUFFERSIZE] = "0";
	char winner = '\0';
	int difficulty = 0;
	difficulty = difficultyLevel();
	//exception catch in fgets or malloc
	if ((difficulty == -2) || (difficulty == -3)) {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(difficulty);
	}
	winner = gameProgress(game, difficulty);
	//exception catch in fgets
	if (winner == 'e') {
		spFiarGameDestroy(game);
		exceptionPrintAndExit(-3);
	}
	//restart game
	if (winner == 'r') {
		spFiarGameDestroy(game);
		game = spFiarGameCreate(HISTORY_SIZE);
		//exception catch in malloc
		if (NULL == game) {
			exceptionPrintAndExit(-2);
		}
		difficulty = difficultyLevel();
		//exception catch in fgets or malloc
		if ((difficulty == -2) || (difficulty == -3)) {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(difficulty);
		}
		winner = gameProgress(game, difficulty);
		//exception catch in fgets
		if (winner == 'e') {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(-3);
		}
	}
	//while loop game
	while (true) {
		//get input from the user
		char* input = fgets(str, BUFFERSIZE, stdin);
		//exception catch in fgets
		if (NULL == input) {
			spFiarGameDestroy(game);
			exceptionPrintAndExit(-3);
		}
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
			if (NULL == game) {
				spFiarGameDestroy(game);
				exceptionPrintAndExit(-2);
			}
			difficulty = difficultyLevel();
			//exception catch in fgets or malloc
			if ((difficulty == -2) || (difficulty == -3)) {
				spFiarGameDestroy(game);
				exceptionPrintAndExit(difficulty);
			}
			//game progress user vs computer
			winner = gameProgress(game, difficulty);
			//exception catch in malloc
			if (winner == 'e') {
				spFiarGameDestroy(game);
				exceptionPrintAndExit(-3);
			}
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
				//exception catch in malloc
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
