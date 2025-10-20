// https://github.com/bean8533/C-BitBoard-Game-Engine

#ifndef BITBOARD_CHECKERS
#define BITBOARD_CHECKERS

#include <stdint.h>

// replace name of uint64_t with bitboard for readability
typedef uint64_t bitboard;

// set a bit at a position to 1
bitboard setBit(bitboard bitboard, int position);

// clear a bit at a position to 0
bitboard clearBit(bitboard bitboard, int position);

// toggle a bit at a position
bitboard toggleBit(bitboard bitboard, int position);

// get the value of a bit at a position; 1 if the bit is set and 0 if it isn't
int getBit(bitboard bitboard, int position);

// counts the number of set bits
int countBits(bitboard bitboard);

// shift bitboard left
bitboard shiftLeft(bitboard bitboard, int position);

// shift bitboard right
bitboard shiftRight(bitboard bitboard, int position);

// prints the board in hex
void printHex(bitboard bitboard);

// prints the board in binary
void printBinary(bitboard bitboard);

#endif