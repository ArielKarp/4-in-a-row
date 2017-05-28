/*
 * main.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#include "SPFIARParser.h"

bool spParserIsInt(const char* str){

	switch(str) {
	      case '1' : //suggest_move
	         printf("Suggested move: drop a disc to column X\n");
	         break;
	      case '2' : //undo_move
	         printf("Remove disc: remove computer’s disc at column X\n");
	         printf("Remove disc: remove user’s disc at column Y\n");
	         break;
	      case '3' : //add_disc
	         printf("Computer move: add disc to column (xxx)\n");
	         break;
	      case '4' : //quit
	         printf("Exiting…\n");
	         break;
	      case '5' : //restart_game
	      default :
	         printf("Game restarted!\n");
	   }
}

SPCommand spParserPraseLine(char* str){

}
