#include "boardManagement.h"
#include "bitOperations.h"
#include <stdio.h>

void initBoard(uint64_t *whitePieces, uint64_t *blackPieces, uint64_t *kings, uint64_t *darkSquares) {
    *whitePieces = 0;
    *blackPieces = 0;
    *kings = 0;
    *darkSquares = 0; // Playable squares

    //In checkers the board is setup where the top 3 rows and bottom 3 rows are occupied by pieces with each piece being on dark square.
    //In this case:
    //Set dark squares
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int bitIndex = row * 8 + col;
            if ((row + col) % 2 == 1) { //Reflect darkzone placement
                *darkSquares = setBit(*darkSquares, bitIndex);

                // Initialize black pieces: top 3 rows
                if (row < 3) *blackPieces = setBit(*blackPieces, bitIndex);

                // Initialize white pieces: bottom 3 rows
                if (row > 4) *whitePieces = setBit(*whitePieces, bitIndex);
            }
        }
    }
}

void printBoard (uint64_t whitePieces, uint64_t blackPieces, uint64_t kings, uint64_t darkSquares){
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            char piece = '.';
            int bitIndex = row * 8 + col;
            if (getBit(darkSquares, bitIndex)) { // only dark squares are playable
                if (getBit(whitePieces, bitIndex)) piece = getBit(kings, bitIndex) ? 'W' : 'w';
                else if (getBit(blackPieces, bitIndex)) piece = getBit(kings, bitIndex) ? 'B' : 'b';
                else piece = '*'; //represent empty dark square explicitly
            }
            printf("%c ", piece);
            }
        //Create a 8x8 index to reflect moveable spaces without cluttering actual board
        printf("   "); // Spacer between board state and index of spaces
        for (int col = 0; col < 8; col++) {
            int bitIndex = row * 8 + col;
            if (getBit(darkSquares, bitIndex)) printf("%2d ", bitIndex);
            else printf(" . "); // light square
        }

        printf("\n");
    }
}

void movePiece(uint64_t *pieces, uint64_t *kings, int from, int to) {
    // Remove piece from old square
    *pieces = clearBit(*pieces, from);

    // Move king status if necessary
    if (getBit(*kings, from)) {
        *kings = clearBit(*kings, from);
        *kings = setBit(*kings, to);
    }

    // Place piece at new square
    *pieces = setBit(*pieces, to);
}


void promotePiece(uint64_t *kings, int position) {
    *kings = setBit(*kings, position);
}