// libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// const definitions
#define ROWS 6
#define COLUMNS 7
#define EMPTY '+'
#define PLAYER1 'D'
#define PLAYER2 'H'
#define WINTHRESH 4

// struct definitions
typedef struct Move {
	int row;
	int col;
} Move;

// globals
char field[ROWS][COLUMNS];

// function declarations
void initField();
void printField();
Move getHumanMove(int player);
Move getCompMove();
void makeMove(int player, Move move);
bool checkWinner(int player, Move move);
int  getColIdx(char colName);
int  getRowIdx(int colIdx);
int  alternatePlayer(bool *alt);
bool checkHoriz(char *search, int row);
bool checkVert(char *search, int col);
bool checkFwdDiag(char *search, int row, int col);
bool checkBwdDiag(char *search, int row, int col);
Move *getOptions();
Move selectOption(Move options[]);
int  scoreOption(Move option);
int  scoreDefense(Move option);
int  scoreOffense(Move option);

// main
int main(void) {
	// game initialization
	printf("\nLet's play Connect %d!\n", WINTHRESH);
	initField();
	printField();
	bool alternator = true;
	bool gameActive = true;
	bool humanGame  = false;
	int player = 1;
	int availTurns = ROWS * COLUMNS;
	int turns = 0;
	Move move;
	
	// continuous loop of turns
	while (gameActive) {
		// get move from user
		if (humanGame || player == 1) {
			move = getHumanMove(player);
		}
		else {
			move = getCompMove();
		}

		// execute move
		makeMove(player, move);

		// check for win
		if (checkWinner(player, move)) {
			printf("\nPlayer %d wins!\n\n", player);
			gameActive = false;
		}

		// end turn
		turns++;
		if (turns == availTurns) {
			printf("\nIt's a tie!\n\n");
			gameActive = false;
		}
		player = alternatePlayer(&alternator);
	}

	// game conclusion
}

// initialize empty field
void initField() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j <	COLUMNS; j++) {
			field[i][j] = EMPTY;
		}
	}
}

// print field for user display
void printField() {
	printf("\n");
	for (int i = 0; i < ROWS + 1; i++) {
		// label first row A - G
		if (i == 0) {
			for (int j = 65; j < 65 + COLUMNS; j++) {
				printf("%c", (char) j);
				printf(" ");
			}
		}

		// print field
		else {
			for (int j = 0; j < COLUMNS; j++) {
				printf("%c", field[i-1][j]);
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

// get move from human player
Move getHumanMove(int player) {
	int col = -1;
	int row = -1;
	char mv[50];

	// prompt user for move
	while (col == -1 || row == -1) {
		printf("Player %d | Please select a valid column: ", player);
		scanf("%s", mv);
		col = getColIdx(mv[0]);
		if (col != -1) {
			row = getRowIdx(col);	
		}
	}
	// return valid move
	Move move;
	move.col = col;
	move.row = row;
	return move;
}

// get move from computer player
Move getCompMove() {
	Move chosen = selectOption(getOptions());
	Move move;
	move.col = chosen.col;
	move.row = chosen.row;
	return move;
}

// get index of row based on index of column if column valid
int getRowIdx(int colIdx) {
	if (colIdx == -1) {
		return -1;
	}
	
	// check column
	for (int i = ROWS - 1; i >= 0; i--) {
		if (field[i][colIdx] == EMPTY) {
			return i;
		}
	}
	return -1;
}

// execute move on field if the move is valid based on selected player
void makeMove(int player, Move move) {
	if (move.row != -1 && move.col != -1) {
		if (player == 1) {
			field[move.row][move.col] = PLAYER1;
		}
		else {
			field[move.row][move.col] = PLAYER2;
		}
	}

	printField();
}

// determine index of column based on column char name
int getColIdx(char colName) {
	// convert to idx
	int colIdx = ((int) tolower(colName)) - 97;

	// return -1 if invalid
	if (colIdx < 0 || colIdx >= COLUMNS) {
		return -1;
	}
	return colIdx;
}

// switch between players
int alternatePlayer(bool *alt) {
	*alt = !(*alt);
	if (*alt) {
		return 1;
	}
	return 2;
}

// search for winner
bool checkWinner(int player, Move move) {
	char search[WINTHRESH];
	if (player == 1) {
		for (int i = 0; i < WINTHRESH; i++) {
			search[i] = PLAYER1;
		}
	}
	else {
		for (int i = 0; i < WINTHRESH; i++) {
			search[i] = PLAYER2;
		}
	}

	if (checkHoriz(search, move.row)) {
		return true;
	}
	else if (checkVert(search, move.col)) {
		return true;
	}
	else if (checkFwdDiag(search, move.row, move.col)) {
		return true;
	}
	else if (checkBwdDiag(search, move.row, move.col)) {
		return true;
	}
	return false;
}

// check for win along horizontal
bool checkHoriz(char *search, int row) {
	char rowStr[COLUMNS];
	for (int i = 0; i < COLUMNS; i++) {
		rowStr[i] = field[row][i];
	}
	if (strstr(rowStr, search) == NULL) {
		return false;
	};
	return true;	
}

// check for win along vertical
bool checkVert(char *search, int col) {
	char colStr[ROWS];
	for (int i = 0; i < ROWS; i++) {
		colStr[i] = field[i][col];
	}
	if (strstr(colStr, search) == NULL) {
		return false;
	};
	return true;
}

// check for win along forward diagonal
bool checkFwdDiag(char *search, int row, int col) {
	int maxDiagSize;
	if (ROWS < COLUMNS) {
		maxDiagSize = ROWS;
	}
	else {
		maxDiagSize = COLUMNS;
	}
	char fwdDiag[maxDiagSize];

	int fwdDiagRowIdx;
	int fwdDiagColIdx;

	if (((ROWS - 1) - row) < col) {
		fwdDiagColIdx = col - (ROWS - 1 - row);
		fwdDiagRowIdx = ROWS - 1;
	}
	else {
		fwdDiagColIdx = 0;
		fwdDiagRowIdx = row + col;
	}
	int idx = 0;
	while (fwdDiagColIdx < COLUMNS && fwdDiagRowIdx >= 0) {
		fwdDiag[idx] = field[fwdDiagRowIdx][fwdDiagColIdx];

		idx++;
		fwdDiagColIdx++;
		fwdDiagRowIdx--;
	}
	if (strstr(fwdDiag, search) != NULL) {
		return true;
	}
	return false;	
}

// check for win along backward diagonal
bool checkBwdDiag(char *search, int row, int col) {
	int maxDiagSize;
	if (ROWS < COLUMNS) {
		maxDiagSize = ROWS;
	}
	else {
		maxDiagSize = COLUMNS;
	}
	char bwdDiag[maxDiagSize];

	int bwdDiagRowIdx;
	int bwdDiagColIdx;
	if (row < col) {
		bwdDiagColIdx = col - row;
		bwdDiagRowIdx = 0;
	}
	else {
		bwdDiagColIdx = 0;
		bwdDiagRowIdx = row - col;
	}

	int	idx = 0;
	while (bwdDiagColIdx < COLUMNS && bwdDiagRowIdx < ROWS) {
		bwdDiag[idx] = field[bwdDiagRowIdx][bwdDiagColIdx];

		idx++;
		bwdDiagColIdx++;
		bwdDiagRowIdx++;
	}
	if (strstr(bwdDiag, search) != NULL) {
		return true;
	}
	return false;	
}

// determine available moves
Move *getOptions() {
	static Move options[COLUMNS];
	for (int i = 0; i < COLUMNS; i++) {
		options[i].col = -1;
		options[i].row = -1;

		// iterate through column to find empty slot
		for (int j = ROWS - 1; j >= 0; j--) {
			if (field[j][i] == EMPTY ) {
				options[i].col = i;
				options[i].row = j;
				break;
			}
		}
	}
	return options;
}

// select best possible move to make
Move selectOption(Move options[]) {
	int bestScore = -1;
	int bestOption = 0;
	for (int i = 0; i < COLUMNS; i++) {
		// printf("Option: %d\n", i);
		// printf("\tRow: %d\n", options[i].row);
		// printf("\tCol: %d\n", options[i].col);
		// only score valid options
		if (options[i].row != -1 && options[i].col != -1) {
			int optionScore = scoreOption(options[i]);
			if (optionScore > bestScore) {
				bestScore = optionScore;
				bestOption = i;
			}
		}
	}
	return options[bestOption];
}

// score the value of the option
int scoreOption(Move option) {
	return 3*scoreDefense(option) + scoreOffense(option);
}

// score the defensive value
int scoreDefense(Move option) {
	field[option.row][option.col] = PLAYER1;
	int score = 0;
	for (int i = WINTHRESH; i > 0; i--) {
		char search[i];
		for (int j = 0; j < i; j++) {
			search[j] = PLAYER1;
		}
		if (checkHoriz(search, option.row)) {
			score += i*i;
		}
		if (checkVert(search, option.col)) {
			score += i*i;
		}
		if (checkFwdDiag(search, option.row, option.col)) {
			score += i*i;
		}
		if (checkBwdDiag(search, option.row, option.col)) {
			score += i*i;
		}
	}
	field[option.row][option.col] = EMPTY;
	return score;
}

// score the offensive value
int scoreOffense(Move option) {
	field[option.row][option.col] = PLAYER2;
	int score = 0;
	int middle = (COLUMNS) / 2;
	score += middle - abs(option.col - middle);
	for (int i = WINTHRESH; i > 0; i--) {
		char search[i];
		for (int j = 0; j < i; j++) {
			search[j] = PLAYER2;
		}
		if (checkHoriz(search, option.row)) {
			score += i*i;
		}
		if (checkVert(search, option.col)) {
			score += i*i;
		}
		if (checkFwdDiag(search, option.row, option.col)) {
			score += i*i;
		}
		if (checkBwdDiag(search, option.row, option.col)) {
			score += i*i;
		}
	}

	field[option.row][option.col] = EMPTY;
	return score;
}