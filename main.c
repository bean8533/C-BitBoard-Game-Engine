#include <stdio.h>

#include "checkers.h"

int main() {
    gamestate game;
    initializeGame(&game);

    printf("---Bitboards Checkers---\n");
    printf("B and R are black and red kings respectively\n");
    printf("Enter moves as 'from to' (ex: 11 18)\n");

    int running = 1;
    while (running) {
        printBoard(&game);

        const char* currentPlayer = game.isBlackTurn ? "Black ('b'/'B')" : "Red ('r'/'R')";

        printf("Player turn: %s\n", currentPlayer);
        printf("Enter your move (from to): ");

        int from;
        int to;

        // checks if input is 2 values
        if (scanf("%d %d", &from, &to) != 2) {
            printf("Invalid input: Please enter two numbers\n");
            while (getchar() != '\n'){}; // clear input buffer
            continue;
        }

        if (applyMove(&game, from, to)) {
            promoteKings(&game); // check if any pieces should be kings

            const int winner = checkWinCondition(&game); // check if either player has won

            if (winner) {
                printBoard(&game);
                printf("\n---Game Over---\n");

                if (winner == 1) printf("Black wins\n");
                else printf("Red wins\n");

                running = 0;
            } else {
                game.isBlackTurn = !game.isBlackTurn; // switch turns
            }
        } else {
            printf("\nInvalid move: Please try again\n");
        }
    }

    return 0;
}



