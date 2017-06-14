#include "unit_test_util.h"
#include "SPFIARGame.h"


#define HISTORY_SIZE 20

static bool spFiarGameValidMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = SP_FIAR_GAME_N_ROWS;
	while (repeat-- > 0) {
		ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);

	}
	ASSERT_FALSE(spFiarGameIsValidMove(res, 2));
	ASSERT_TRUE(spFiarGameSetMove(res,2)==SP_FIAR_GAME_INVALID_MOVE);
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFiarGameUndoMoveTest2() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 3;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}
	repeat = 20;
	while (repeat-- > 0) {
		ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
	}
	ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_NO_HISTORY);
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}
static bool spFiarGameUndoMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}
	repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameUndoPrevMove(res) == SP_FIAR_GAME_SUCCESS);
		}
	}
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFiarGameSetMoveTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	int repeat = 2;
	while (repeat-- > 0) {
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
		}
	}
	spFiarGamePrintBoard(res);
	spFiarGameDestroy(res);
	return true;
}

static bool spFIARGameBasicTest() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	spFiarGameDestroy(res);
	return true;
}

static bool spFIARGameWinnerTest() {
	char winner;
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 1);
	}
	spFiarGameSetMove(res, 0);
	spFiarGamePrintBoard(res);
	winner = spFiarCheckWinner(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 5);
		spFiarGameSetMove(res, 6);
	}
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 0);

	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 6);
	}
	spFiarGameSetMove(res, 0);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 0);
	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 6);
	}
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, i);
		spFiarGameSetMove(res, i);
	}
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<3;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 3+i);
		spFiarGameSetMove(res, 3+i);
	}
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<2;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 1);
		spFiarGameSetMove(res, 3);

		spFiarGameSetMove(res, 2);
		spFiarGameSetMove(res, 0);
		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 1);
	}
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 3);

	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int i=0;i<2;i++)
	{
		winner = spFiarCheckWinner(res);
		ASSERT_TRUE(winner == '\0');

		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 5);
		spFiarGameSetMove(res, 4);
		spFiarGameSetMove(res, 6);

		spFiarGameSetMove(res, 5);
		spFiarGameSetMove(res, 3);
		spFiarGameSetMove(res, 6);
		spFiarGameSetMove(res, 4);
	}
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 6);

	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);

	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);


	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 4);

	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 6);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 0);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);

	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 0);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_1_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 0);

	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 5);

	spFiarGameSetMove(res, 0);

	spFiarGameSetMove(res, 6);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 5);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 4);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 3);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 3);

	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_PLAYER_2_SYMBOL);
	spFiarGameDestroy(res);

	res = spFiarGameCreate(HISTORY_SIZE);
	for(int j=0;j<3;j++)
	{
		spFiarGameSetMove(res, 0+j*2);
		spFiarGameSetMove(res, 1+j*2);
		spFiarGameSetMove(res, 0+j*2);
		spFiarGameSetMove(res, 1+j*2);
	}
	for(int j=0;j<3;j++)
	{
		spFiarGameSetMove(res, 1+j*2);
		spFiarGameSetMove(res, 0+j*2);
		spFiarGameSetMove(res, 1+j*2);
		spFiarGameSetMove(res, 0+j*2);
	}
	for(int j=0;j<3;j++)
	{
		spFiarGameSetMove(res, 0+j*2);
		spFiarGameSetMove(res, 1+j*2);
		spFiarGameSetMove(res, 0+j*2);
		spFiarGameSetMove(res, 1+j*2);
	}
	for(int j=0;j<6;j++)
		spFiarGameSetMove(res, 6);




	winner = spFiarCheckWinner(res);
	spFiarGamePrintBoard(res);
	ASSERT_TRUE(winner == SP_FIAR_GAME_TIE_SYMBOL);
	spFiarGameDestroy(res);

	return true;
}

static bool spFIARGameWinnerTest2() {
	SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
	ASSERT_TRUE(res!=NULL);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 0);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 1);
	spFiarGameSetMove(res, 2);
	spFiarGameSetMove(res, 2);
	printf("%d", gameScoringFunc(res, 'O'));
	spFiarGameDestroy(res);
	return true;
}

int main() {
	RUN_TEST(spFIARGameBasicTest);
	RUN_TEST(spFiarGameSetMoveTest);
	RUN_TEST(spFiarGameUndoMoveTest);
	RUN_TEST(spFiarGameUndoMoveTest2);
	RUN_TEST(spFiarGameValidMoveTest);
	RUN_TEST(spFIARGameWinnerTest);
	RUN_TEST(spFIARGameWinnerTest2);
	return 0;
}
