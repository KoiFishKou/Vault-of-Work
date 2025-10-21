#ifndef BOARDMANAGEMENT_H
#define BOARDMANAGEMENT_H

#include <stdint.h>

// Initialize the board with starting positions
void initBoard(uint64_t *whitePieces, uint64_t *blackPieces, uint64_t *kings, uint64_t *darkSquares);

// Display the board in ASCII
void printBoard(uint64_t whitePieces, uint64_t blackPieces, uint64_t kings, uint64_t darkSquares);

// Move a piece from one square to another
void movePiece(uint64_t *pieces, uint64_t *kings, int from, int to);

// Promote a piece to king
void promotePiece(uint64_t *kings, int position);

#endif
