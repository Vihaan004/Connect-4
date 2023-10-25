#include <stdio.h>

void setupGame();
char gameSequence();
int insertCoin(int column);
int checkConnect();
int checkFull();
void displayBoard();

char player1[50];
char player2[50];
int mode;
char currCoin;
char board[6][7];

void setupGame() {
	
	while (1)
	{
		printf("Choose game mode: (2, 3 or 4) : ");
		scanf("%d", &mode);
		if (mode >= 2 && mode <= 4)
			break;
		printf("Not a valid mode!\n");
	}
	
	printf("Player 1 (R): ");
	scanf("%s", player1);
	printf("Player 2 (Y): ");
	scanf("%s", player2);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			board[i][j] = ' ';
	displayBoard();
}

char gameSequence() {
	int c = 0;
	int full = 0;
	int column = 0;

	while (full == 0) {
		
		if (c % 2 == 0) {
			printf("%s to play. Pick a column (1-7): ", player1);
			currCoin = 'R';
		}
		else {
			printf("%s to play. Pick a column (1-7): ", player2);
			currCoin = 'Y';
		}

		int insert = 0;
		while(insert == 0) {
			scanf("%d", &column);
			if (column > 0 && column < 8) {
				if (insertCoin(column - 1) == 1)
					insert = 1;
				else
					printf("Column full! Pick again: ");
			}
			else
				printf("Out of range! Pick again: ");
			
		}

		displayBoard();

		if (checkConnect() == 1) {
			return currCoin;
		}

		full = checkFull();
		c++;
	}

	return 'D';
}

int insertCoin(int column) {
	for (int i = 5; i >= 0; i--) {
		if (board[i][column] == ' ') {
			board[i][column] = currCoin;
			return 1;
		}
	}
	return 0;
}

int checkConnect() {
	int match = 0;

	//check for horizontal wins
	for (int i = 0; i < 6; i++) {
		for (int j = 1; j < 7; j++) {
			if (board[i][j] == board[i][j - 1] && board[i][j] != ' ') {
				match++;
				if (match == mode - 1)
					return 1;
			}
			else
				match = 0;
		}
	}

	//check for vertical wins
	for (int i = 0; i < 7; i++) {
		for (int j = 1; j < 6; j++) {
			if (board[j][i] == board[j - 1][i] && board[j][i] != ' ') {
				match++;
				if (match == mode - 1)
					return 1;
			}
			else
				match = 0;
		}
	}

	//check for diagonal wins
	for (int i = mode - 1; i < 6; i++) {
		for (int j = 0; j < 8 - mode; j++) {
			
			char base = board[i][j];
			for (int k = 1; k < mode; k++) {
				if (base == board[i - k][j + k] && base != ' ')
					match++;
			}
			if (match == mode - 1)
				return 1;
			else
				match = 0;
		}
	}

	for (int i = 0; i < 7 - mode; i++) {
		for (int j = 0; j < 8 - mode; j++) {

			char base = board[i][j];
			for (int k = 1; k < mode; k++) {
				if (base == board[i + k][j + k] && base != ' ')
					match++;
			}
			if (match == mode - 1)
				return 1;
			else
				match = 0;
		}
	}
	return 0;
}

int checkFull() {
	for (int i = 0; i < 7; i++) {
		if (board[0][i] == ' ')
			return 0;
	}
	return 1;
}

void displayBoard() {
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
			printf("| %c", board[i][j]);
		printf("|\n");
	}
	for (int i = 0; i < 22; i++)
		printf("-");
	printf("\n");
}

int main() {
	printf("Welcome to connect four!\n");
	int quit = 1;
	while (quit != 0) {
		setupGame();
		char result = gameSequence();
		if (result == 'R')
			printf("%s won the game!", player1);
		else if (result == 'Y')
			printf("%s won the game!", player2);
		else
			printf("The board is full...It's a draw!");
		printf("\nPress any key to replay or 0 to quit: ");
		scanf("%d", &quit);
		while(getchar() != '\n'); // clear buffer
	}
}