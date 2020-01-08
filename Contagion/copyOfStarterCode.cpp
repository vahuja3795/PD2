/* Prog2Contagion.cpp

   Program #2: Play the game of Contagion against another person
               This is a variation of Ataxx, a version of which can
               be played online at: http://www.classikgames.com/ataxx.html
   Class: CS 141
   Date: 1/27/2019
   Author: *** YOUR NAME HERE ***

   Grading Rubric:
     55% Passes Codio run-time tests (some cases below are split into multiple tests)
          5 Handles both upper and lower case user input
          5 Handles making adjacent move for each player
         10 Handles making jump move for each player
          5 Handles pass move 
          2 Error message and retry when source position does not belong to player
          2 Error message and retry when destination position is not empty
          6 Error message and retry when destination is not one or two squares away
            in horizontal, vertical, or diagonal line
         15 Flips opponent pieces adjacent to move destination
          5 When board is filled correctly identifies winner and exits program

     45% Programming Style:
         10 Meaningful Identifier Names.
         10 Comments, header, and meaningful variable names
         10 Functional Decomposition 
         10 Appropriate data and control structures
          5 Code Layout
*/
#include <iostream>
#include <cstdlib>   // for exit() and abs()
using namespace std;

// The 25 board position variables may be global variables, but no other variables may be global.
char  p1, p2, p3, p4, p5,
      p6, p7, p8, p9,p10,
     p11,p12,p13,p14,p15,
     p16,p17,p18,p19,p20,
     p21,p22,p23,p24,p25;


//-----------------------------------------------------------------------------------------
// Display the game instructions
void displayInstructions()
{
    cout << " \n"
         << "Welcome to the 2-player game of Contagion, where the point of the game is    \n"
         << "to capture as much of the board as possible.  On each move you must enter \n"
         << "the row and column position of one of your current pieces (e.g. a1) and   \n"
         << "the row and column of an empty destination, which must be one or two      \n"
         << "squares away.  Moves can be made horizontally, vertically, or diagonally. \n"
         << " \n"
         << "If the destination is one square away, then an additional piece for you   \n"
         << "is placed in the destination square.  If the destination is two squares   \n"
         << "away (a jump move), then the original piece is moved to that destination. \n"
         << "jumping over a single square or any player's piece.                       \n"
         << " \n"
         << "After a piece has been moved, all opponent pieces adjacent to the         \n"
         << "destination are changed to match the piece of the user making the move.   \n"
         << "Player X moves first.     \n"
         << " \n"
         << "A valid first move, for instance, could be: a1 a2  which since it is just \n"
         << "one square away, would put an additional X on square a2.  Alternatively   \n"
         << "if the first move is:  a1 c3  then since it is two squares away, the piece\n"
         << "currently at a1 would be moved to destination c3.                         \n"
         << endl;
}


//-----------------------------------------------------------------------------------------
// Display the board, using the global board variables
// For reference here are the board row, col and board variable values:
//       1  2  3  4  5
//    ----------------
//  A |  1  2  3  4  5
//  B |  6  7  8  9 10
//  C | 11 12 13 14 15
//  D | 16 17 18 19 20
//  E | 21 22 23 24 25
//
void displayBoard()
{
    cout << "    1   2   3   4   5  \n"
         << "  ---------------------\n"
         << "A | " <<  p1 << " | " <<  p2 << " | " <<  p3 << " | " <<  p4 << " | " <<  p5 << " | A \n"
         << "  |---|---|---|---|---| \n"
         << "B | " <<  p6 << " | " <<  p7 << " | " <<  p8 << " | " <<  p9 << " | " << p10 << " | B \n"
         << "  |---|---|---|---|---| \n"
         << "C | " << p11 << " | " << p12 << " | " << p13 << " | " << p14 << " | " << p15 << " | C \n"
         << "  |---|---|---|---|---| \n"
         << "D | " << p16 << " | " << p17 << " | " << p18 << " | " << p19 << " | " << p20 << " | D \n"
         << "  |---|---|---|---|---| \n"
         << "E | " << p21 << " | " << p22 << " | " << p23 << " | " << p24 << " | " << p25 << " | E \n"
         << "  ---------------------\n"
         << "    1   2   3   4   5  \n"
         << endl;
}


//-----------------------------------------------------------------------------------------
int main() {
    // Set initial values for the global board variables to all be blank
    p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16=p17=p18=p19=p20=p21=p22=p23=p24=p25= ' ';
    // Set corner starting positions
    p1=p25= 'X';
    p5=p21= 'O';
    
    // Variables to store user input for current row and column, and destination row and column
    char currentRow;
    // ...
    
    cout << "Welcome to the 2-player game of Contagion. \n"
         << endl;

    // Main loop to play game
    while( true) {
    
        // Display board and handle first character of user input
        displayBoard();
        cout << "Enter 'i' for instructions, 'x' to exit, or your move: ";
        cin >> currentRow;
        
        // Check to see if user input was 'i' for instructions or 'x' to exit
        if( currentRow == 'I') {
            displayInstructions();
            continue;       // Loop back up to retry move
        }
        else if( currentRow == 'X') {
            cout << "Exiting program... \n"
                 << endl;
            break;  // Break out of enclosing loop, to exit the game.
        }
        else {
            // User input was not 'i' for instructions or 'x' to exit, so a move is being made
            // ...
        }
    } //end while( true)

    return 0;
} // end main()
