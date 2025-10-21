#include <stdio.h>
#include "bitOperations.h" //Part of testing left for testing
#include "gameLogic.h"
#include "boardManagement.h"

int main(void) {
    //Set-up
    uint64_t whitePieces = 0;
    uint64_t blackPieces = 0;
    uint64_t kings = 0;
    uint64_t darkSquares = 0;

    Player currentPlayer = WHITE;
    int from, to;

    //Initialization of game
    initBoard(&whitePieces, &blackPieces, &kings, &darkSquares);

    while (1) {
        printBoard(whitePieces, blackPieces, kings, darkSquares);

        //Pieces Check & win check
        if ((currentPlayer == WHITE && whitePieces == 0) ||
            (currentPlayer == BLACK && blackPieces == 0)) {
            printf("%s has no pieces left! %s wins!\n",
                   currentPlayer == WHITE ? "White" : "Black",
                   currentPlayer == WHITE ? "Black" : "White");
            break;
            }

        printf("%s's turn. Enter move (from to): ", currentPlayer == WHITE ? "White" : "Black");
        scanf("%d %d", &from, &to);

        if (!validMove(whitePieces, blackPieces, kings, darkSquares, from, to, currentPlayer)) {
            printf("Invalid move, try again.\n");
            continue;
        }
        executeMove(&whitePieces, &blackPieces, &kings, from, to, currentPlayer);

        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
    }
    return 0;
}
