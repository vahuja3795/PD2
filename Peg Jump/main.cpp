/* pegJump.cpp

   Author: Varun Ahuja
   Program: #3, Peg Jump
   CS 141, Spring 2019
 
   Description:
          This program represents a peg jumping puzzle  A
        move is made by a peg jumping over another peg into an empty
        spot, where the jumped peg is then removed from the board. The
        game ends when there are no more valid moves to make. The object
        is to eliminate as many pegs as possible.
				
		Sample output:
		
			Welcome to the peg jump puzzle! 
			Enter '-' to exit, or '+' for instructions. 

							A B C         
							D E F         
					G H I J K L M     
					N O P * Q R S     
					T U V W X Y Z     
							1 2 3         
							4 5 6         

			1. Enter the peg to move: +

			Welcome to the peg jump puzzle. The board starts out with a 
			single blank position, represented by the '*'.  To make a 
			move, select the letter of a peg.  A peg must be able to 
			jump over an adjacent peg into a blank position for a move 
			to be valid.  The jumped peg is then removed from the board. 
			The game is over when there are no valid moves left. At any 
			point enter '-' to exit, or '+' for instructions. 

			1. Enter the peg to move: E

							A B C         
							D * F         
					G H I * K L M     
					N O P E Q R S     
					T U V W X Y Z     
							1 2 3         
							4 5 6         

			2. Enter the peg to move: w

							A B C         
							D * F         
					G H I W K L M     
					N O P * Q R S     
					T U V * X Y Z     
							1 2 3         
							4 5 6         

			3. Enter the peg to move: 5

							A B C         
							D * F         
					G H I W K L M     
					N O P * Q R S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			4. Enter the peg to move: 2
			*** Invalid move, please retry. *** 
			4. Enter the peg to move: r

							A B C         
							D * F         
					G H I W K L M     
					N O P R * * S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			5. Enter the peg to move: R

							* * *         
							* 1 *         
					* * * * * * *     
					* * * + * * *     
					* * * * * * *     
							* 2 *         
							* * *         

			There is more than one possible move.  Which move do you want? 1

							A B C         
							D R F         
					G H I * K L M     
					N O P * * * S     
					T U V 5 X Y Z     
							1 * 3         
							4 * 6         

			6. Enter the peg to move: -

			Exiting...

			27 pieces remaining. Ouch!
 */

/***
 * Mallavarapu:
 * 1) Comments at the functions should explain the parameters and the return types
 * ***/

#include <iostream>
#include <cctype>     // For toupper()
using namespace std;

// Displaying instructions
//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << endl
         << "Welcome to the peg jump puzzle. The board starts out with a \n"
         << "single blank position, represented by the '*'.  To make a \n"
         << "move, select the letter of a peg.  A peg must be able to \n"
         << "jump over an adjacent peg into a blank position for a move \n"
         << "to be valid.  The jumped peg is then removed from the board. \n"
         << "The game is over when there are no valid moves left. At any \n"
         << "point enter '-' to exit, or '+' for instructions. \n"
         << endl;
}

// Displaying the board
//-------------------------------------------------------------------------------------
void displayBoard(char *pboard){
  for (int i = 11; i <= 109; ++i)
  {
    if (pboard[i] == 35){
      cout << "  ";
    }
    else{
      cout << pboard[i];
      cout << " ";
    }
    if (!((i + 1) % 11)) {
      cout << endl;
    }
  }
}

// Creating function to look for position wher the input was called on the board
int findPosition(char pboard1, char *pboard){
  for (int i = 0; i <= 120; ++i){
    if (pboard[i] == pboard1){
      return i;
    }
  }
  return -1;
}

// Creating function to look for moves that are possible from the userinput
void lookAround(char *board, int pos, int possibleDest[4], int &possibleCount){
	possibleCount = 0;
	// Found all possible
	if (board[pos - 22] == 42 && board[pos - 11] != 42) {
		possibleDest[possibleCount] = pos - 22; //Possible Index
		possibleCount++;
  }
	if (board[pos - 2] == 42 && board[pos - 1] != 42) {
		possibleDest[possibleCount] = pos - 2; //Possible Index
		possibleCount++;
  }
	if (board[pos + 2] == 42 && board[pos + 1] != 42) {
		possibleDest[possibleCount] = pos + 2; //Possible Index
		possibleCount++;
  }
	if (board[pos + 22] == 42 && board[pos + 11] != 42) {
		possibleDest[possibleCount] = pos + 22; //Possible Index
		possibleCount++;
  }
}

// Function displays board and asks for the user's choice when there is more than one possible choice
int displayTheBoardandAsk(char *pboard, int x, int possibleDest[4]){
  int input3;
  
  for (int i = 11; i <= 109; ++i)
  {
    if (pboard[i] == 35){
      cout << "  ";
    }
    else if (i == possibleDest[0]){
      cout << '1';
      cout << " ";
    } else if (i == possibleDest[1]) {
      cout << '2';
      cout << " ";
    } else if (i == possibleDest[2]) {
      cout << '3';
      cout << " ";
    } else if (i == possibleDest[3]) {
      cout << '4';
      cout << " ";
    } else if (i == x) {
      cout << '+';
      cout << " ";
    } else {
      cout << '*';
      cout << " ";
    }
    if (!((i + 1) % 11)) {
      cout << endl;
    }
  }
  
  cout << "There is more than one possible move.  Which move do you want? ";
  cin >> input3;
  cout << endl;
  
  return input3;
}

// Creating function that will make the move
int makeMove(char x, char *board){
	int possibleDest[4];
	int possibleCount;
  int input;
  int input2;
  input = findPosition(x,board);
	lookAround(board, input, possibleDest, possibleCount);
	if (possibleCount == 0){
		return 0;
	}
  
  // Creating if-else statements to check where the move will occur or will it not occur
	if (possibleCount==1){
		//move
		if (possibleDest[possibleCount - 1] == input - 22 && board[input - 11] != 42) {
      board[input] = 42;
      board[input - 11] = 42;
      board[input - 22] = x;
    } else if (possibleDest[possibleCount - 1] == input - 2 && board[input - 1] != 42) {
      board[input] = 42;
      board[input - 1] = 42;
      board[input - 2] = x;
    } else if (possibleDest[possibleCount - 1] == input + 2 && board[input + 1] != 42) {
      board[input] = 42;
      board[input + 1] = 42;
      board[input + 2] = x;
    } else if (possibleDest[possibleCount - 1] == input + 22 && board[input + 11] != 42) {
      board[input] = 42;
      board[input + 11] = 42;
      board[input + 22] = x;
    } else if (board[input + 2] != 42) {
      return 0;
    } else if (board[input - 2] != 42) {
      return 0;
    } else if (board[input + 1] == 42) {
      return 0;
    } else if (board[input - 1] == 42) {
      return 0;
    }
	}
  
  // Here it is checking to see what the user's choice was to move and then it will update the board accordingly
	if (possibleCount>1){
		//ask
		input2 = displayTheBoardandAsk(board,input,possibleDest);
		//move
    if (input2 == 1) {
      if (possibleDest[0] == input - 22 && board[input - 11] != 42) {
        board[input] = 42;
        board[input - 11] = 42;
        board[input - 22] = x;
      } else if (possibleDest[0] == input - 2 && board[input - 1] != 42) {
        board[input] = 42;
        board[input - 1] = 42;
        board[input - 2] = x;
      } else if (possibleDest[0] == input + 2 && board[input + 1] != 42) {
        board[input] = 42;
        board[input + 1] = 42;
        board[input + 2] = x;
      } else if (possibleDest[0] == input + 22 && board[input + 11] != 42) {
        board[input] = 42;
        board[input + 11] = 42;
        board[input + 22] = x;
      }
    } else if (input2 == 2) {
      if (possibleDest[1] == input - 2 && board[input - 1] != 42) {
        board[input] = 42;
        board[input - 1] = 42;
        board[input - 2] = x;
      } else if (possibleDest[1] == input + 2 && board[input + 1] != 42) {
        board[input] = 42;
        board[input + 1] = 42;
        board[input + 2] = x;
      } else if (possibleDest[1] == input + 22 && board[input + 11] != 42) {
        board[input] = 42;
        board[input + 11] = 42;
        board[input + 22] = x;
      }
    } else if (input2 == 3) {
      if (possibleDest[2] == input + 2 && board[input + 1] != 42) {
        board[input] = 42;
        board[input + 1] = 42;
        board[input + 2] = x;
      } else if (possibleDest[2] == input + 22 && board[input + 11] != 42) {
        board[input] = 42;
        board[input + 11] = 42;
        board[input + 22] = x;
      }
    } else if (input2 == 4) {
      if (possibleDest[3] == input + 22 && board[input + 11] != 42) {
        board[input] = 42;
        board[input + 11] = 42;
        board[input + 22] = x;
      }
    } 
	}
}

// Creating function that will return the value for possible moves 
int lookAround2(char *board, int pos){
	int possibleCount = 0;
	// Found all possible
	if (board[pos - 22] == 42 && board[pos - 11] != 42) {
		possibleCount++;
  }
	if (board[pos - 2] == 42 && board[pos - 1] != 42) {
		possibleCount++;
  }
	if (board[pos + 2] == 42 && board[pos + 1] != 42) {
		possibleCount++;
  }
	if (board[pos + 22] == 42 && board[pos + 11] != 42) {
		possibleCount++;
  }
  return possibleCount;
}

// Creating function that will count the remaining pegs on the board
int countRemainingPegs(char *x) {
  int pb2 = 0;
  
  for (int i = 11; i <= 109; ++i) {
    if (x[i] != 35 && x[i] != 42) {
      ++pb2;
    }
  }
  return pb2;
}

// Creating the function that will check if any more moves are possible on the board or not
int notDone(char *x) {
  int pb3;
  int pb5;
  int pb4 = 0;
  for (int i = 11; i <= 109; ++i) {
    if (x[i] != 35 && x[i] != 42) {
      pb3 = lookAround2(x,i);
      if (pb3 == 0) {
        pb4++;
      }
    }
  }
  pb5 = countRemainingPegs(x);
  if (pb4 == pb5) {
    return 0;
  } else {
    return 1;
  }
}

// Creating function to display messages according to how many pegs are remaining
int displayMessages(int x) {
  cout << x << "  pieces remaining. ";
  if (x == 2) {
    cout << "Good! " << endl;
  } else if ( x > 2) {
    if (x == 3) {
      cout << "OK. " << endl;
    } else {
      if (x != 4) {
        cout << "Ouch! " << endl;
      }
      if (x == 4) {
        cout << "Needs Improvement. " << endl;
      }
    }
  } else {
    if (x != 1) {
      return 0;
    }
    cout << "Excellent! " << endl;
  }
  return 0;
}

// Creating the function main
int main()
{
    //Variable declarations
    char board[] = {
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','A','B','C','#','#','#','#',
            '#','#','#','#','D','E','F','#','#','#','#',
            '#','#','G','H','I','J','K','L','M','#','#',
            '#','#','N','O','P','*','Q','R','S','#','#',
            '#','#','T','U','V','W','X','Y','Z','#','#',
            '#','#','#','#','1','2','3','#','#','#','#',
            '#','#','#','#','4','5','6','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#'
          };
    int count = 1;
    char input;
    int remaining;
    int input5;

    cout << "Welcome to the peg jump puzzle! \n"
         << "Enter '-' to exit, or '+' for instructions. "
         << endl;

    displayBoard(board);
    // Main loop to play the game
    // ...
    while (true) {
        // Prompt for and get move
				// ... 
        cout << count << ". Enter the peg to move: ";
        cin >> input;
        cout << endl;
        input = toupper(input);
        // Check for '-' to exit, and '+' for displaying instructions
				// ... 
        if (input == '-') {
          cout << "Exiting..." << endl;
          break;
        }
        if (input == '+') {
          displayInstructions();
        }
        // Make move
				// ...
        else if (makeMove(input,board) == 0) {
          cout << "*** Invalid move, please retry. ***" << endl;
        }
				// Increment move number and display the board
				// ...
        else {
          ++count;
          displayBoard(board);
        }
        if (notDone(board) == 0) {
            break;
        } 
    }
    // Display appropriate message depending on number of remaining pegs
    // ...
    cout << endl;
    remaining = countRemainingPegs(board);
    displayMessages(remaining);
    return 0;
}//end main()