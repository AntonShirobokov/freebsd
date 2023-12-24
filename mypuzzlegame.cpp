#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
using namespace std;

const int SIZE = 4;
int xZero = 0;
int yZero = 0;


int board[SIZE][SIZE] = { {1,2,3,4},
                        {5,6,7,8},
                        {9,10,11,12},
                        {13,14,15,0} };
int rightBoard[SIZE][SIZE] = { {1,2,3,4},
                             {5,6,7,8},
                             {9,10,11,12},
                             {13,14,15,0} };

bool checkWin(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (board[i][j] != rightBoard[i][j]){
                return false;
            }
        }
    }
    return true;
}


void shuffleBoard() {
	for (int i = 0; i < 100; i++) {
		int a1 = rand() % SIZE;
		int a2 = rand() % SIZE;
		int b1 = rand() % SIZE;
		int b2 = rand() % SIZE;

		int freeVariable = board[a1][a2];
		board[a1][a2] = board[b1][b2];
		board[b1][b2] = freeVariable;
	}
}

void printBoard() {
	int x = 7;
	int y = 5;
	mvprintw(4, 10,"Game 15\n");
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] != 0) {
				mvprintw(y, x, "%2d", board[i][j]);
				x = x + 3;
			}
			else {
				mvprintw(y, x, "  ");
				x = x + 3;
			}
		}
		printw("\n");
		x = 7;
		y = y + 1;
	}
	mvprintw(9, 5,"Press ESC to exit");
}

void findZero() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 0) {
				xZero = j;
				yZero = i;
				return;
			}
		}
	}

}
int main()
{
	srand(time(NULL));

	int ch;

	initscr();

	keypad(stdscr, 1);
	noecho();
	curs_set(0);


	shuffleBoard();
	findZero();
	printBoard();



	do {
		if (ch == KEY_UP) {
			if (yZero == 3){
			    continue;
			}
			board[yZero][xZero] = board[yZero+1][xZero];
			yZero++;
			board[yZero][xZero] = 0;
			printBoard();
		}
		else if (ch == KEY_DOWN) {
			if (yZero == 0){
			    continue;
			}
			board[yZero][xZero] = board[yZero-1][xZero];
			yZero--;
			board[yZero][xZero] = 0;
			printBoard();
		}
		else if (ch == KEY_LEFT) {
			if (xZero == 3){
			    continue;
			}
			board[yZero][xZero] = board[yZero][xZero+1];
			xZero++;
			board[yZero][xZero] = 0;
			printBoard();
		}
		else if (ch == KEY_RIGHT) {
			if (xZero == 0){
			    continue;
			}
			board[yZero][xZero] = board[yZero][xZero-1];
			xZero--;
			board[yZero][xZero] = 0;
			printBoard();
		}
		if (checkWin()){
		    clear();
		    break;
		}
	}while ((ch = getch()) != 27);
    mvprintw(4, 10,"You win\n");
    mvprintw(5, 5,"Press ESC to exit");
    getch();
	endwin();
}