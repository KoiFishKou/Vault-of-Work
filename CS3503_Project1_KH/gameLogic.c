#include "gameLogic.h"
#include "bitOperations.h"
#include "boardManagement.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//Check player to opponent
static uint64_t opponentPieces(uint64_t whitePieces, uint64_t blackPieces, Player currentPlayer) {
    return (currentPlayer == WHITE) ? blackPieces : whitePieces;
}

//Check if dark square is empty
static int isEmptySquare(uint64_t whitePieces, uint64_t blackPieces, uint64_t darkSquares, int to) {
    return getBit(darkSquares, to) && !getBit(whitePieces, to) && !getBit(blackPieces, to);
}

//Check player condition for piece promotion
int shouldPromote(int position, Player currentPlayer) {
    int row = position / 8;
    if (currentPlayer == WHITE) return row == 0; //White's condition
    else return row == 7; //Black's condition
}

//Check if move is valid
int validMove(uint64_t whitePieces, uint64_t blackPieces, uint64_t kings,
              uint64_t darkSquares, int from, int to, Player currentPlayer) {

    //Must move your own piece
    uint64_t myPieces = (currentPlayer == WHITE) ? whitePieces : blackPieces;
    if (!getBit(myPieces, from)) return 0;

    //Destination must be empty dark square
    if (!isEmptySquare(whitePieces, blackPieces, darkSquares, to)) return 0;

    int rowFrom = from / 8;
    int colFrom = from % 8;
    int rowTo = to / 8;
    int colTo = to % 8;

    int dRow = rowTo - rowFrom;
    int dCol = colTo - colFrom;

    //Diagonal move must be one step for normal, two for capture
    if (abs(dRow) == 1 && abs(dCol) == 1) {
        //normal move
        if (!getBit(kings, from)) {
            if (currentPlayer == WHITE && dRow != -1) return 0;
            if (currentPlayer == BLACK && dRow != 1) return 0;
        }
        return 1;
    } else if (abs(dRow) == 2 && abs(dCol) == 2) {
        //capture move
        int midRow = (rowFrom + rowTo) / 2;
        int midCol = (colFrom + colTo) / 2;
        int midIndex = midRow * 8 + midCol;
        if (getBit(opponentPieces(whitePieces, blackPieces, currentPlayer), midIndex))
            return 1; //capture is valid
    }

    return 0; //invalid move
}

//Execute move (move + capture + promotion)
void executeMove(uint64_t *whitePieces, uint64_t *blackPieces, uint64_t *kings, int from, int to, Player currentPlayer) {

    uint64_t *myPieces = (currentPlayer == WHITE) ? whitePieces : blackPieces;
    uint64_t *opponent = (currentPlayer == WHITE) ? blackPieces : whitePieces;

    //Check if move is capture
    if (abs(to - from) == 14 || abs(to - from) == 18) { // diagonal 2-step
        int midRow = (from / 8 + to / 8) / 2;
        int midCol = (from % 8 + to % 8) / 2;
        int midIndex = midRow * 8 + midCol;
        *opponent = clearBit(*opponent, midIndex); // remove captured piece
        *kings = clearBit(*kings, midIndex); // clear king if captured
    }

    //Move the piece
    movePiece(myPieces, kings, from, to);

    //Promote if needed
    if (shouldPromote(to, currentPlayer)) {
        promotePiece(kings, to);
    }
}