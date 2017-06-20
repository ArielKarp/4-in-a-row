/*
 * main.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#include "SPFIARParser.h"

bool spParserIsInt(const char* str) {
	unsigned int i = 0;
	// Check if number in str is negative
	if (str[0] == 45) {
		i = 1;
	}
	unsigned int len = 0;
	// Set size of the number (depends if string literal or null terminated)
	if(str[strlen(str)-1] == '\0'){
		len = strlen(str);
	}
	else {
		len = strlen(str) - 1;
	}
	for (; i < len ; i++) {
		//ASCII value of 0 is 48 ... 9 = 57
		//if value is outside not x is no 48<x<57 then in returns false otherwise true

		if (str[i] < 48 || str[i] > 57)
			return false;
	}

	return true;

}

SPCommand spParserPraseLine(const char* str) {
	SPCommand returnCmd;
	returnCmd.arg = -1;
	returnCmd.cmd = SP_INVALID_LINE;
	returnCmd.validArg = false;
	char* copyStr = (char*) malloc((strlen(str) + 1) * sizeof(char));
	// Catch failure in malloc
	if (NULL == copyStr){
		returnCmd.cmd = SP_EXCEPTION;
		return returnCmd;
	}
	// copy str to copyStr
	strcpy(copyStr, str);
	const char delim[8] = " \t\r\n";
	char* cmdStr = NULL;
	cmdStr = strtok(copyStr, delim);
	// Check type of command and return with returnCommand
	if (NULL == cmdStr || strcmp(cmdStr, "\0") == 0) {
		clearStrInput(copyStr);
		return returnCmd;
	}
	if (strcmp(cmdStr, "suggest_move") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SP_SUGGEST_MOVE;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}
	else if (strcmp(cmdStr, "undo_move") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SP_UNDO_MOVE;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}
	else if (strcmp(cmdStr, "add_disc") == 0) {
		returnCmd.cmd = SP_ADD_DISC;
		char* numStr = strtok(NULL, delim);
		if (NULL == numStr) {
			clearStrInput(copyStr);
			return returnCmd;
		}
		char* conStr = strtok(NULL, delim);
		if (NULL != conStr) {
			clearStrInput(copyStr);
			return returnCmd;
		}
		if ((spParserIsInt(numStr) == true)) {
			returnCmd.validArg = true;
			returnCmd.arg = atoi(numStr);
		}
	}
	else if (strcmp(cmdStr, "quit") == 0) {
		char* conStr = strtok(NULL, delim);
		if ((NULL == conStr)) {
			returnCmd.cmd = SP_QUIT;
		} else {
			returnCmd.cmd = SP_INVALID_LINE;
		}
	}
	else if (strcmp(cmdStr, "restart_game") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SP_RESTART;
			clearStrInput(copyStr);
			return returnCmd;
		} else {
			returnCmd.cmd = SP_INVALID_LINE;
		}
	}
	clearStrInput(copyStr);
	return returnCmd;
}

void clearStrInput(char* str) {
	// Free str if not null
	if (NULL != str) {
		free(str);
		str = NULL;
	}
	return;
}
