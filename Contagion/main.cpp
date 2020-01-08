/* Prog2Contagion.cpp

   Program #2: Play the game of Contagion against another person
               This is a variation of Ataxx, a version of which can
               be played online at: http://www.classikgames.com/ataxx.html
   Class: CS 141
   Date: 1/27/2019
   Author: Varun Ahuja

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
    cout << "    1   2   3   4   5\n"
         << "  ---------------------\n"
         << "A | " <<  p1 << " | " <<  p2 << " | " <<  p3 << " | " <<  p4 << " | " <<  p5 << " | A\n"
         << "  |---|---|---|---|---|\n"
         << "B | " <<  p6 << " | " <<  p7 << " | " <<  p8 << " | " <<  p9 << " | " << p10 << " | B\n"
         << "  |---|---|---|---|---|\n"
         << "C | " << p11 << " | " << p12 << " | " << p13 << " | " << p14 << " | " << p15 << " | C\n"
         << "  |---|---|---|---|---|\n"
         << "D | " << p16 << " | " << p17 << " | " << p18 << " | " << p19 << " | " << p20 << " | D\n"
         << "  |---|---|---|---|---|\n"
         << "E | " << p21 << " | " << p22 << " | " << p23 << " | " << p24 << " | " << p25 << " | E\n"
         << "  ---------------------\n"
         << "    1   2   3   4   5\n"
         << endl;
}

//Checks to see if the board is full or not
bool notComplete(int numberOfXPieces, int numberOfOPieces)
{
  return numberOfXPieces + numberOfOPieces <= 24 && numberOfXPieces > 0 && numberOfOPieces > 0;
}

// Converts row and column to a number so its easier to assign each piece
int RowColToNumber(char row, char col)
{
  return col - '0' + 5 * (row - 'A');
}

// Converts the index to a char so its easier to which row and col is being referred to
void IndexToRowCol(int pieceIndex, char *const row, char *const col)
{
  *row = (char)(pieceIndex - 1) / 5 + 65;
  *col = (pieceIndex - 1) % 5 + 49;
}

// This function gets the piece at the row and col, either it will be a X or an O. It uses swtich cases for each global variable
char getPieceAt(char row, char col)
{
  char result;
  char valueAtPiece;
  int pieceIndex;

  pieceIndex = RowColToNumber(row, col);
  switch ( pieceIndex )
  {
    case 1:
      valueAtPiece = p1;
      break;
    case 2:
      valueAtPiece = p2;
      break;
    case 3:
      valueAtPiece = p3;
      break;
    case 4:
      valueAtPiece = p4;
      break;
    case 5:
      valueAtPiece = p5;
      break;
    case 6:
      valueAtPiece = p6;
      break;
    case 7:
      valueAtPiece = p7;
      break;
    case 8:
      valueAtPiece = p8;
      break;
    case 9:
      valueAtPiece = p9;
      break;
    case 10:
      valueAtPiece = p10;
      break;
    case 11:
      valueAtPiece = p11;
      break;
    case 12:
      valueAtPiece = p12;
      break;
    case 13:
      valueAtPiece = p13;
      break;
    case 14:
      valueAtPiece = p14;
      break;
    case 15:
      valueAtPiece = p15;
      break;
    case 16:
      valueAtPiece = p16;
      break;
    case 17:
      valueAtPiece = p17;
      break;
    case 18:
      valueAtPiece = p18;
      break;
    case 19:
      valueAtPiece = p19;
      break;
    case 20:
      valueAtPiece = p20;
      break;
    case 21:
      valueAtPiece = p21;
      break;
    case 22:
      valueAtPiece = p22;
      break;
    case 23:
      valueAtPiece = p23;
      break;
    case 24:
      valueAtPiece = p24;
      break;
    case 25:
      valueAtPiece = p25;
      break;
    default:
      cout << "Invalid value ";
      cout << pieceIndex;
      cout << " sent to function getPieceAt().  Exiting program..." << endl;
      exit(-1);
      return result;
  }
  return valueAtPiece;
}

// This function sets the empty piece with the newValue that was chosen on the specific turn in the game. It uses switch cases for each global variable.
void setPieceAt(char row, char col, char newValue)
{
  char newValue1;
  int pieceIndex;

  newValue1 = newValue;
  pieceIndex = RowColToNumber(row, col);
  switch ( pieceIndex )
  {
    case 1:
      p1 = newValue1;
      break;
    case 2:
      p2 = newValue1;
      break;
    case 3:
      p3 = newValue1;
      break;
    case 4:
      p4 = newValue1;
      break;
    case 5:
      p5 = newValue1;
      break;
    case 6:
      p6 = newValue1;
      break;
    case 7:
      p7 = newValue1;
      break;
    case 8:
      p8 = newValue1;
      break;
    case 9:
      p9 = newValue1;
      break;
    case 10:
      p10 = newValue1;
      break;
    case 11:
      p11 = newValue1;
      break;
    case 12:
      p12 = newValue1;
      break;
    case 13:
      p13 = newValue1;
      break;
    case 14:
      p14 = newValue1;
      break;
    case 15:
      p15 = newValue1;
      break;
    case 16:
      p16 = newValue1;
      break;
    case 17:
      p17 = newValue1;
      break;
    case 18:
      p18 = newValue1;
      break;
    case 19:
      p19 = newValue1;
      break;
    case 20:
      p20 = newValue1;
      break;
    case 21:
      p21 = newValue1;
      break;
    case 22:
      p22 = newValue1;
      break;
    case 23:
      p23 = newValue1;
      break;
    case 24:
      p24 = newValue1;
      break;
    case 25:
      p25 = newValue1;
      break;
    default:
      cout << "Invalid value";
      cout << pieceIndex;
      cout << " sent to function setPieceAt().  Exiting program..." << endl;
      exit(-1);
      return;
  }
}

// This determines what type of move will take place an adjacentMove or and jumpMove.
int TypeOfMove(char currentRow, char currentCol, char destinationRow, char destinationCol)
{
  int moveType;
  int rowDifference;
  int colDifference;
  int AdjacentMove = 1;
  int JumpMove = 2;

  moveType = -1;
  rowDifference = abs(currentRow - destinationRow);
  colDifference = abs(currentCol - destinationCol);
  if ( rowDifference == 1 && !colDifference
    || !rowDifference && colDifference == 1
    || rowDifference == 1 && colDifference == 1 )
  {
    moveType = AdjacentMove;
  }
  if ( rowDifference == 2 && !colDifference
    || !rowDifference && colDifference == 2
    || rowDifference == 2 && colDifference == 2 )
  {
    moveType = JumpMove;
  }
  return moveType;
}

// This function checks if the piece can be placed there or not
char getOpponent(char playerToMove)
{
  if ( playerToMove == 79 )
    return 88;
  if ( playerToMove != 88 )
  {
    cout << "*** Invalid move.  A move must be one or two squares away. Please retry." << endl;
  }
  return 79;
}

// This function is there to see if anything on the board needs to be replaced or not
void CheckAndReset(int playerPosition, int neighborOffset, char playerToMove)
{
  char v3;
  char playerToMovea;
  char row;
  char col;
  char opponent;

  playerToMovea = playerToMove;
  if ( (playerPosition > 5 || neighborOffset != -6 && neighborOffset != -5 && neighborOffset != -4)
    && ((playerPosition - 1) % 5 || neighborOffset != -6 && neighborOffset != -1 && neighborOffset != 4)
    && (playerPosition % 5 || neighborOffset != -4 && neighborOffset != 1 && neighborOffset != 6)
    && (playerPosition <= 20 || neighborOffset <= 3) )
  {
    IndexToRowCol(playerPosition + neighborOffset, &row, &col);
    opponent = getOpponent(playerToMovea);
    v3 = getPieceAt(row, col);
    if ( v3 == opponent )
      setPieceAt(row, col, playerToMovea);
  }
}

//This function changes the pieces to match the piece that the player is moving
void changeDestinationNeighborsToPiecePlayed(char destinationRow, char destinationCol, char playerToMove)
{
  char v3;
  int playerPosition;

  v3 = playerToMove;
  playerPosition = RowColToNumber(destinationRow, destinationCol);
  CheckAndReset(playerPosition, -6, v3);
  CheckAndReset(playerPosition, -5, v3);
  CheckAndReset(playerPosition, -4, v3);
  CheckAndReset(playerPosition, 1, v3);
  CheckAndReset(playerPosition, 6, v3);
  CheckAndReset(playerPosition, 5, v3);
  CheckAndReset(playerPosition, 4, v3);
  CheckAndReset(playerPosition, -1, v3);
}

// This function checks for each number of piece so it returns the number of X's or the number of O's
void NumberOfEachPiece(int *const numberOfPieces, char playerPiece)
{
  char row;
  char col;
  int i;

  *numberOfPieces = 0;
  for ( i = 1; i <= 25; ++i )
  {
    IndexToRowCol(i, &row, &col);
    if ( getPieceAt(row, col) == playerPiece )
      ++*numberOfPieces;
  }
}

// Creating the main function where the gameplay occurs
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
    // All of these variables are needed for the gameplay to run smoothly
    char currentCol;
    char destinationRow;
    char destinationCol;
    char playerToMove;
    int numberOfXPieces;
    int numberOfOPieces;
    int moveNumber = 1;
    int moveType;
    char piece;
    playerToMove = 'X';
    numberOfXPieces = 2;
    numberOfOPieces = 2;
    int AdjacentMove = 1;
    int JumpMove = 2;
    int InvalidMove = 0;

    cout << "Welcome to the 2-player game of Contagion. \n"
         << endl;

    // Loop begins here with the condition being check if the board is full or not
    while (notComplete(numberOfXPieces, numberOfOPieces))
    {
    displayBoard();
    cout << moveNumber;
    cout << ". Enter 'i' for instructions, 'x' to exit, or move for " << playerToMove << ": ";
    cin >> currentRow;
    currentRow = toupper(currentRow);
    if (currentRow == 'I') {
        displayInstructions();
        continue;
    } else if (currentRow == 'X') {
        break;  // Break out of enclosing loop, to exit the game.
    } else if (currentRow == 'P') {
        NumberOfEachPiece(&numberOfXPieces, 'X');
        NumberOfEachPiece(&numberOfOPieces, 'O');
        ++moveNumber;
        playerToMove = getOpponent(playerToMove);
        continue;
    } else {
        cin >> currentCol >> destinationRow >> destinationCol;
        cout << endl;
        destinationRow = toupper(destinationRow);
        piece = getPieceAt(currentRow, currentCol);
        // These statements are checking where to insert the new piece and also outputs error messages if it is an invalid input
        if ( piece == playerToMove )
        {
          if ( getPieceAt(destinationRow, destinationCol) == ' ' )
          {
            moveType = TypeOfMove(currentRow, currentCol, destinationRow, destinationCol);
            if ( moveType != InvalidMove )
            {
              if ( moveType == AdjacentMove )
              {
                setPieceAt(destinationRow, destinationCol, playerToMove);
              }
              else
              {
                if ( moveType != JumpMove )
                {
                  cout << "*** Invalid move.  A move must be one or two squares away. Please retry." << endl;
                  continue;
                }
                setPieceAt(currentRow, currentCol, ' ');
                setPieceAt(destinationRow, destinationCol, playerToMove);
              }
              changeDestinationNeighborsToPiecePlayed(destinationRow, destinationCol, playerToMove);
              NumberOfEachPiece(&numberOfXPieces, 'X');
              NumberOfEachPiece(&numberOfOPieces, 'O');
              ++moveNumber;
              playerToMove = getOpponent(playerToMove);
              continue;
            }
            cout << "*** Invalid move.  Current piece must belong to you. Please retry.\n";
          }
          else
          {
           cout << "*** Invalid move.  Destination must be empty. Please retry.\n";
          }
        }
        else
        {
          cout << "*** Invalid move.  Current piece must belong to you. Please retry." << endl;
        }
        continue;
    }
   }//end while( true)

   // Here the winning statement is outputted
   displayBoard();
   if ( numberOfXPieces <= numberOfOPieces )
   {
    if ( numberOfOPieces <= numberOfXPieces )
        cout << "Tie game." << endl;
    else
          cout << "O Wins!" << endl;
    }
  else
  {
    cout << "X Wins!" << endl;
  }
  cout << endl;
  cout << "Exiting program..." << endl;

  return 0;
} // end main()
// END OF PROGRAM
