// https://github.com/bean8533/C-BitBoard-Game-Engine

#include <stdio.h>
#include <stdlib.h>

#include "bitboard.h"

typedef struct {
    bitboard blackPieces;
    bitboard redPieces;
    bitboard kings;
    int isBlackTurn;
} gamestate;

// masks to stop pieces from wrapping around the board
const bitboard leftColumnMask = 0xfefefefefefefefeULL;
const bitboard rightColumnMask = 0x7f7f7f7f7f7f7f7fULL;

// masks for promotion rows
const bitboard redPromotionRowMask = 0xFF00000000000000ULL;   // top row
const bitboard blackPromotionRowMask = 0x00000000000000FFULL; // bottom row

void initializeGame(gamestate* gameState) {
    gameState->blackPieces = 0x000000000055AA55ULL;
    gameState->redPieces = 0xAA55AA0000000000ULL;
    gameState->kings = 0x0000000000000000ULL;
    gameState->isBlackTurn = 1;
}

void printBoard(const gamestate* gameState) {
    printf("\n   --------------------------\n");

    for (int row = 7; row >= 0; row--) {
        printf(" %d |", row);

        for (int column = 0; column < 8; column++) {
            const int position = row * 8 + column;
            char piece = ' ';

            if (getBit(gameState->blackPieces, position)) {
                piece = getBit(gameState->kings, position) ? 'B' : 'b';
            } else if (getBit(gameState->redPieces, position)) {
                piece = getBit(gameState->kings, position) ? 'R' : 'r';
            }

            if ((row + column) % 2 == 0) {
                 printf(" %c ", piece);
            } else {
                 printf(" * ");
            }
        }

        printf("|\n");
    }

    printf("   --------------------------\n");
    printf("     0  1  2  3  4  5  6  7\n\n");
}

int applyMove(gamestate* gameState, const int from, const int to) {
    const bitboard occupied = gameState->blackPieces | gameState->redPieces; // board of all occupied spaces

    if (from < 0 || from > 63 || to < 0 || to > 63) return 0; // check if destination is in range
    if (getBit(occupied, to)) return 0; // check if destination is empty

    bitboard* playerPieces = gameState->isBlackTurn ? &gameState->blackPieces : &gameState->redPieces;
    bitboard* opponentPieces = gameState->isBlackTurn ? &gameState->redPieces : &gameState->blackPieces;

    if (!getBit(*playerPieces, from)) return 0; // checks if the player owns the piece at the from position

    const int isKing = getBit(gameState->kings, from);
    const int difference = to - from;

    // normal moves
    if (abs(difference) == 7 || abs(difference) == 9) {
        int isValidDirection = 0;

        // black pieces and kings move up
        if (gameState->isBlackTurn || isKing) {
            if ( (difference == 7 && getBit(leftColumnMask, from)) || (difference == 9 && getBit(rightColumnMask, from)) ) {
                isValidDirection = 1;
            }
        }

        // red pieces and kings move down
        if (!gameState->isBlackTurn || isKing) {
            if ( (difference == -7 && getBit(rightColumnMask, from)) || (difference == -9 && getBit(leftColumnMask, from)) ) {
                 isValidDirection = 1;
            }
        }

        // moves piece if the move is valid
        if (isValidDirection) {
            *playerPieces = clearBit(*playerPieces, from);
            *playerPieces = setBit(*playerPieces, to);

            // updates kings bitboard if moved piece was a king
            if(isKing) {
                gameState->kings = clearBit(gameState->kings, from);
                gameState->kings = setBit(gameState->kings, to);
            }

            return 1;
        }
    }

    // jumps/captures
    if (abs(difference) == 14 || abs(difference) == 18) {
        const int jumpedPosition = from + difference / 2;

        if (!getBit(*opponentPieces, jumpedPosition)) return 0; // checks if there's an opponent piece to jump over

        int isValidDirection = 0;

        // black pieces and kings move up
        if (gameState->isBlackTurn || isKing) {
             if ( (difference == 14 && getBit(leftColumnMask, from)) || (difference == 18 && getBit(rightColumnMask, from)) ) {
                isValidDirection = 1;
            }
        }

        // red pieces and kings move down
        if (!gameState->isBlackTurn || isKing) {
             if ( (difference == -14 && getBit(rightColumnMask, from)) || (difference == -18 && getBit(leftColumnMask, from)) ) {
                isValidDirection = 1;
            }
        }

        // moves piece if the move is valid
        if (isValidDirection) {
            *playerPieces = clearBit(*playerPieces, from);
            *playerPieces = setBit(*playerPieces, to);

            // updates kings bitboard if moved piece was a king
            if(isKing) {
                gameState->kings = clearBit(gameState->kings, from);
                gameState->kings = setBit(gameState->kings, to);
            }

            *opponentPieces = clearBit(*opponentPieces, jumpedPosition); // removes captured piece

            // removes captured piece from kings bitboard if it was a king
            if (getBit(gameState->kings, jumpedPosition)) {
                 gameState->kings = clearBit(gameState->kings, jumpedPosition);
            }

            return 1;
        }
    }

    return 0; // invalid move
}

void promoteKings(gamestate* gameState) {
    const bitboard blackPromotions = gameState->blackPieces & redPromotionRowMask;
    const bitboard redPromotions = gameState->redPieces & blackPromotionRowMask;
    gameState->kings |= blackPromotions;
    gameState->kings |= redPromotions;
}

int checkWinCondition(const gamestate* gameState) {
    if (gameState->redPieces == 0) return 1;
    if (gameState->blackPieces == 0) return 2;
    return 0;
}