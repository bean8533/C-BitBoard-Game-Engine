// https://github.com/bean8533/C-BitBoard-Game-Engine

#ifndef BITBOARD_CHECKERS
#define BITBOARD_CHECKERS

#include <stdint.h>

#include "bitboard.h"

// replace name of uint64_t with bitboard for readability
typedef uint64_t bitboard;

// holds game information
typedef struct {
    bitboard blackPieces;
    bitboard redPieces;
    bitboard kings;
    int isBlackTurn;
} gamestate;

// starts game with pieces in starting positions
void initializeGame(gamestate* gameState);

// prints the board formatted
void printBoard(const gamestate* gameState);

// applies move if it's valid
int applyMove(gamestate* gameState, int from, int to);

// checks for pieces that reach the end and promotes them
void promoteKings(gamestate* gameState);

// checks if either player has won
int checkWinCondition(const gamestate* gameState);

#endif