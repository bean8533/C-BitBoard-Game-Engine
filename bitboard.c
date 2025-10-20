// https://github.com/bean8533/C-BitBoard-Game-Engine

#include <stdio.h>

#include "bitboard.h"

typedef uint64_t bitboard;

bitboard setBit(const bitboard bitboard, const int position) {
    if (position < 0 || position > 63) return bitboard;
    return bitboard | (1ULL << position);
}

bitboard clearBit(const bitboard bitboard, const int position) {
    if (position < 0 || position > 63) return bitboard;
    return bitboard & ~(1ULL << position);
}

bitboard toggleBit(const bitboard bitboard, const int position) {
    if (position < 0 || position > 63) return bitboard;
    return bitboard ^ (1ULL << position);
}

int getBit(const bitboard bitboard, const int position) {
    if (position < 0 || position > 63) return 0;
    return (bitboard >> position) & 1ULL;
}

int countBits(bitboard bitboard) {
    int count = 0;

    while (bitboard > 0) {
        bitboard &= (bitboard - 1);
        count++;
    }

    return count;
}

bitboard shiftLeft(const bitboard bitboard, const int position) {
    return bitboard << position;
}

bitboard shiftRight(const bitboard bitboard, const int position) {
    return bitboard >> position;
}

void printHex(const bitboard bitboard) {
    printf("0x%016llX\n", bitboard);
}

void printBinary(const bitboard bitboard) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", getBit(bitboard, i));
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}