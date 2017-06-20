#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_
#include <stdbool.h>
#include <stdio.h>
#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"

#define HISTORY_SIZE 20


//put auxiliary functions and constants used by the main function here.

/**
 * check if the input number is a valid int between 1 to 7
 * @param num
 * @return
 * true if valid otherwise false
 */
int checkValidInputNum(int num);

/**
 *take the game back 2 steps before by undo from the history game and print the steps
 * @param game
 * @return
 * 1 if succeeded 0 otherwise
 */
int undoMove(SPFiarGame* game);

/**
 *get the difficulty from the input user using the parser
 * @return
 * the difficulty int if succeeded or quit or exception
 */
int difficultyLevel(SPFiarGame* game);

/**
 *prints the winner of the game and his next options
 * @param winner
 */
void winnerPrint(char winner);

/**
 *while loop for the running game of the user vs the computer, until there is a winner
 *game and difficulty required for the input
 * @param game
 * @param difficulty
 * @return
 * winner result is returned
 */
char gamePlay(SPFiarGame* game, int difficulty);

/**
 *check whi is the winner and return it to the main
 *game and difficulty required for the input
 * @param game
 * @param difficulty
 * @return
 * the winner is returned
 */
char gameProgress(SPFiarGame* game,int difficulty);

/**
 *prints the exception error and exit the game
 * @param functionType
 */
void exceptionPrintAndExit(int functionType);


int addDisc(SPFiarGame* game, SPCommand command);
void checkIfGameProgressReturnedError( SPFiarGame* game, char errorCode);
void checkIfDifficulyLevelFailed(SPFiarGame* game, int errorCode);
void checkIfFgetsFailed(SPFiarGame* game, char* returnFgets);
void checkIfGameCrateFailed(SPFiarGame* game);
char restartGame(SPFiarGame* game);

#endif
