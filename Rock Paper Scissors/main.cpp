// Displaying the header information which includes the rubric but is not outputted 
/* ------------------------------------------------
   prog1RockPaperScissors.cpp
 
   Program #1: Play the game of Paper / Rock / Scissors against the computer.
   Class: CS 141
   Author: Varun Ahuja
	 
	 See the program description page on the course web site at bit.ly/cs141
	 Within Codio you can run the solution by doing the following steps:
   1. Select the Tools / Terminal menu option
	 2. Within the terminal window, type in:  ./solution

   Grading Rubric:
		 55 Execution points
						  Option 1: (Computer always chooses R) and:
					 2		 User input of X immediately exits program
					 3		 User input of x (lower case) immediately exits program
				  10		 Program handles both lower and upper case user input (e.g. 'r' and 'R'); also
					          move number increments each move
				  15		 Score updates correctly for all user inputs: r, p, s
						  Option 2: Computer's move is random and:
					 7		 Predetermined input sequence correctly leads to computer win
				   8		 Predetermined input sequence correctly leads to human win
		         Option 3: 
           2     Correctly displays and updates the graphical score
		       8     Correctly displays and updates the graphical score, with assessment results hidden

		 45 Programming Style (Given only if program runs substantially correctly)
					10 Meaningful identifier names
					10 Comments: Has header.  Comments on each block of code.
					15 Appropriate data and control structures.  Code duplication is avoided.
					10 Code Layout: Appropriate indentation and blank lines.
 
   Having sample program output is not required within this header of your program, though it is helpful.
	 
	 
*/

// Including the libraries that are needed for this program
#include <iostream>    // For cin and cout
#include <cstdlib>     // For rand()
using namespace std;

// Creating the main function
//-----------------------------------------------------------------------------------------
int main()
{
    // Displaying Instructions
    cout << "CS 141 Program #1: Rock/Paper/Scissors\n"
         << endl
         << "Welcome to the game of Rock/Paper/Scissors where you play against     \n"
         << "the computer.  On each move the computer will choose R, P, or S, then \n"
         << "the user will be prompted for their choice, and then the score will   \n"
         << "be updated.  P beats R, R beats S, and S beats P. The score starts    \n"
         << "at 0.  Add one if the person wins, subtract one if the computer wins. \n"
         << "The game ends if the score reaches -5 or + 5.                         \n"
         << "User input of 'x' or 'X' causes the game to exit.                     \n"
         << endl
         << "Here we go!\n"
         << endl;
    
    // Creating variable for choosing the computer Choice
    int computerChoiceVersion;
    cout << "Select how the computer chooses its move:\n"
         << "1. Always choose Rock\n"
         << "2. Random guess\n"
         << "3. Random guess with graphical score\n"
         << "Enter your choice: ";
    cin >> computerChoiceVersion;
    cout << endl;
    cout << "" << endl;
    
    // Creating variables that are needed for the gameplay
    int movenumber = 1; // The first move of the game starts at 1
    int computerVersion = 0; // This variable just creates a copy of the game mode
    int score = 0; // This variable will keep track of the gamescore
    char userChoice; // This char variable will hold the user's choice
    char computerChoice; // This char variable will hold the computer's choice
    int randomValue; // This variable will hold the randomValue for the game mode

    // Main loop should go here, with the indented sections below inside the main loop
    // ...
    // Creating a while loop for the gameplay where it will continue until score is equal to 5 or -5
    while (score != 5 || score != -5) {
// *** Yuwei: you have checked if score equals to 5 or -5 in while loop, no need to check it again.
       // Creating a if statement to check for winning scores 
       if (score == 5 || score == -5) {
          break;
        }
        // Get the computer choice
				// ...
          computerVersion = computerChoiceVersion;
          randomValue = rand() % 3;
        // Prompt for and get the user's choice
        // ...
          cout << movenumber << ". Your move: ";
          cin >> userChoice;
          cout << endl;
          userChoice = toupper(userChoice); // Converting the input to uppercase
          
          // Creating a if statement to check for the input of 'x' so the program can exit
          if (userChoice == 'X') {
            cout << "Exiting program..." << endl;
            break;
          }
        // Display computer choice
        // ...
          
          // Creating if-else statements to assign the computer choice depending on the version and random value
          if (computerVersion == 1) {
            computerChoice = 'R';
          } else if (computerVersion == 2 || computerVersion == 3) {
              if (randomValue == 0) {
                computerChoice = 'R';
              } else if (randomValue == 1) {
                computerChoice = 'P';
              } else if (randomValue == 2) {
                computerChoice = 'S';
              }
          }
          cout << "   " << "Computer chose " << computerChoice << endl;
        // Update score, and then display it
				// ...

// *** Yuwei: Code for calculating the score is the same for all 3 versions, you can extract this out.				 
				// Creating if-else statements to update the gamescore and to output it after each turn has occurred
          if (computerVersion == 1 || computerVersion == 2) {  
            if (userChoice == 'R' && computerChoice == 'S' || userChoice == 'S' && computerChoice == 'P' || userChoice == 'P'
               && computerChoice == 'R') {
              score = score + 1;
              cout << "   User's point. Score: " << score << endl;
              cout << "" << endl;
            } else if (userChoice == computerChoice) {
                score = score;
                cout << "   Tie. Score: " << score << endl;
                cout << "" << endl;
            } else if (computerChoice == 'R' && userChoice == 'S' || computerChoice == 'S' && userChoice == 'P' || 
                computerChoice == 'P' && userChoice == 'R') {
                score = score - 1;
                cout << "   Computer's point. Score: " << score << endl;
                cout << "" << endl;
            }
          } else if (computerVersion == 3) {
              if (userChoice == 'R' && computerChoice == 'S' || userChoice == 'S' && computerChoice == 'P' || userChoice == 'P'
               && computerChoice == 'R') {
              score = score + 1;
              cout << "   User's point." << endl;
            } else if (userChoice == computerChoice) {
                score = score;
                cout << "   Tie." << endl;
            } else if (computerChoice == 'R' && userChoice == 'S' || computerChoice == 'S' && userChoice == 'P' || 
                computerChoice == 'P' && userChoice == 'R') {
                score = score - 1;
                cout << "   Computer's point." << endl;
            }
            
            // Creating the graphical representation for the gamescore
            cout << "    -5 -4 -3 -2 -1  0  1  2  3  4  5" << endl;
            cout << "   ----------------------------------" << endl;
            cout << "   ";
            for(int i = 0; i < score + 5; i++) {
              cout << "...";
            }
            cout << "..^" << endl;
            
          }
        // Increment move number
				// ...
          movenumber++;
    }
    // Display final message, depending on the score
    // ...
    // Creating if-else statements to display the final message depending on the gamescore
// *** Yuwei: Computer wins as long as score < 0, no need to consider score equals to -5 as a special case. 
    if (score == 5 || score > 0) {
      cout << "User wins!" << endl
           << "" << endl;
    } else if (score == -5 || score < 0) {
      cout << "Computer wins!" << endl
           << "" << endl;
    } else if (score == 0) {
      cout << "Tie game!" << endl
           << "" << endl;
    }
    cout << "Ending program..." << endl;
    return 0;   // Keep C++ happy
}//end main()
