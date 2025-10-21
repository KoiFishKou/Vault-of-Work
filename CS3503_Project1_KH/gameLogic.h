#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include<stdint.h>
//Define players
typedef enum {
    WHITE = 0,
    BLACK = 1
} Player;

//Check which moves are available
int validMove(uint64_t whitePieces, uint64_t blackPieces, uint64_t kings, uint64_t darkSquares, int from, int to, Player currentPlayer);
//Execute those moves
void executeMove(uint64_t *whitePieces, uint64_t *blackPieces, uint64_t *kings, int from, int to, Player currentPlayer);
//Check promotion condition
int shouldPromote(int position, Player currentPlayer);

#endif