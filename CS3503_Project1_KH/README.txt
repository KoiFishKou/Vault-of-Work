#Author
Khuong Hoang

#Description
A simple implementation 8x8 bitboard implementation of Checkers using Owl Tech's model.
Includes the following files:
-bitOperations.c
-boardManagement.c
-gameLogic.c
-main.c
- + all the associated header (.h) files

#Build Instruction
-Open the project folder or place the files into your favorite C IDE 
-Allow the IDE to generate the build system.
-Build and run the project from the IDE

#Notes:
-Initially built in Clion using C

#Rules:
On activation of the game the terminal will showcase:
. b . b . b . b     .  1  .  3  .  5  .  7
b . b . b . b .     8  . 10  . 12  . 14  .
. b . b . b . b     . 17  . 19  . 21  . 23
* . * . * . * .    24  . 26  . 28  . 30  .
. * . * . * . *     . 33  . 35  . 37  . 39
w . w . w . w .    40  . 42  . 44  . 46  .
. w . w . w . w     . 49  . 51  . 53  . 55
w . w . w . w .    56  . 58  . 60  . 62  .

The left board is the active game, with the right board being included to help guide movement.
- '.' reflect white spots
- '*' reflect dark spots / moveable areas
- On the right board index, number associated to white spots were taken out to decrease information overflow
  and reflect the squares that player can move their pieces to.
- 'w' for white pieces and 'b' for black pieces with the game being set to have white start first.
- Pieces can be promoted similar to regular chess where if a player can move their piece to the opposing members end zone
  with the letter being capitalized the piece becoming a king piece.
  'w' -> 'W'
  'b' -> 'B'
- Double capture is not implemented.
- The win condition is for player to take all the opposing player's pieces.

#Gameplay:
Click run to the start the game.
Each player takes turn with the terminal prompting "(white/black)'s turn. Enter move (from to):"
Player's must type the number of the piece they want to move to a moveable empty space, else game prompts invalid move.
Hence the game expects: "(int) (int)"
But players can also choose to insert (int) -enter- then another (int)

Example move:
starting state:
. b . b . b . b     .  1  .  3  .  5  .  7
b . b . b . b .     8  . 10  . 12  . 14  .
. b . b . b . b     . 17  . 19  . 21  . 23
* . * . * . * .    24  . 26  . 28  . 30  .
. * . * . * . *     . 33  . 35  . 37  . 39
w . w . w . w .    40  . 42  . 44  . 46  .
. w . w . w . w     . 49  . 51  . 53  . 55
w . w . w . w .    56  . 58  . 60  . 62  .

input:
White's turn. Enter move (from to): 40 33
or
White's turn. Enter move (from to): 40
33

output:
. b . b . b . b     .  1  .  3  .  5  .  7
b . b . b . b .     8  . 10  . 12  . 14  .
. b . b . b . b     . 17  . 19  . 21  . 23
* . * . * . * .    24  . 26  . 28  . 30  .
. w . * . * . *     . 33  . 35  . 37  . 39
* . w . w . w .    40  . 42  . 44  . 46  .
. w . w . w . w     . 49  . 51  . 53  . 55
w . w . w . w .    56  . 58  . 60  . 62  .
Black's turn. Enter move (from to):
