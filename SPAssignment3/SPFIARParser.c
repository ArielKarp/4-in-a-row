/*
 * main.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#include "SPFIARParser.h"

bool spParserIsInt(const char* str) {
	unsigned i = 0;
	if (str[0] == 45){
		i = 1;
	}
	for (; i < strlen(str); i++) {
		//ASCII value of 0 is 48 ... 9 = 57
		//if value is outside not x is no 48<x<57 then in returns false otherwise true

		if (str[i] < 48 || str[i] > 57)
			return false;
	}

	return true;

}

SPCommand spParserPraseLine(const char* str) {

	char* copyStr = (char*) malloc((strlen(str) + 1) * sizeof(char));
	strcpy(copyStr, str);
	const char delim[8] = " \t\r\n";
	//printf("%s\n", copyStr);
	SPCommand returnCmd;

	returnCmd.arg = -1;
	returnCmd.cmd = SP_INVALID_LINE;
	returnCmd.validArg = false;

	char* cmdStr;
	cmdStr = strtok(copyStr, delim);
	//printf("%s\n",cmdStr);
	if (cmdStr == NULL) {
		return returnCmd;
	}

	if (strcmp(cmdStr,"suggest_move") == 0) {
		returnCmd.cmd = SP_SUGGEST_MOVE;
	}

	else if (strcmp(cmdStr,"undo_move") == 0) {
		returnCmd.cmd = SP_UNDO_MOVE;
	}

	else if (strcmp(cmdStr,"add_disc") == 0) {

		char* numStr = strtok(NULL, delim);
		if (numStr == NULL) {
			return returnCmd;
		}
		returnCmd.arg = atoi(numStr);
		returnCmd.cmd = SP_ADD_DISC;
		//printf("%d\n", 	returnCmd.arg);
		if (spParserIsInt(numStr) == true) {
			returnCmd.validArg = true;
			//printf("%d\n", 	returnCmd.arg);
		}
	}

	else if (strcmp(cmdStr,"quit") == 0) {
		returnCmd.cmd = SP_QUIT;
	}

	else if (strcmp(cmdStr,"restart_game") == 0) {
		returnCmd.cmd = SP_RESTART;
	}

	return returnCmd;
}

//switch(cmdStr) {
//	      case 'SP_SUGGEST_MOVE' : //suggest_move
//	    	 returnCmd -> cmd = SP_SUGGEST_MOVE;
//	         printf("Suggested move: drop a disc to column X\n");
//	         break;
//	      case 'SP_UNDO_MOVE' : //undo_move
//	    	 returnCmd -> cmd = SP_UNDO_MOVE;
//	         printf("Remove disc: remove computer’s disc at column X\n");
//	         printf("Remove disc: remove user’s disc at column Y\n");
//	         break;
//	      case 'SP_ADD_DISC' : //add_disc
//	    	 returnCmd -> cmd = SP_ADD_DISC;
//	    	 returnCmd -> arg = atoi(strtok(NULL, " "));
//	         printf("Computer move: add disc to column (xxx)\n");
//	         break;
//	      case 'SP_QUIT' : //quit
//	    	 returnCmd -> cmd = SP_QUIT;
//	         printf("Exiting…\n");
//	         break;
//	      case 'SP_RESTART' : //restart_game
//	    	 returnCmd -> cmd = SP_RESTART;
//		     printf("Game restarted!\n");
//	         break;
//	   }
