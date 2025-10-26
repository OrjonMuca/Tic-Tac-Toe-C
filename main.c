#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

const char PLAYER = 'X';
const char COMPUTER = 'O';
char board[3][3];

int main()
{
    char winner = ' ';
    char response;

    do {
        winner = ' ';
        response = ' ';
        resetBoard();

        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
                break;

            computerMove();
            winner = checkWinner();
        }

        printBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);

    } while (response == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2)
            printf("\n---|---|---\n");
    }
    printf("\n");
}

int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ')
                freeSpaces--;
        }
    }
    return freeSpaces;
}

void playerMove() {
    int x, y;
    do {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        x--; y--;
        if (board[x][y] != ' ') {
            printf("Invalid move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove() {
    srand(time(0));
    int x, y;
    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = COMPUTER;
    } else {
        printWinner(' ');
    }
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER)
        printf("YOU WIN!\n");
    else if (winner == COMPUTER)
        printf("YOU LOSE!\n");
    else
        printf("It's a TIE!\n");
}
