//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:
 
     Varun Ahuja
     UIC CS 141, Spring 2019
     Welcome to 1024.
     This program is based off of Gabriele Cirulli's game online at
     bit.ly/great2048
 
     For each move enter a direction as a letter key, as follows:
         W
       A S D
     where A=left,W=up, D=right and S=down.
 
     After a move, when two identical valued tiles come together they
     join to become a new single tile with the value of the sum of the
     two originals. This value gets added to the score.  On each move
     one new randomly chosen value of 2 or 4 is placed in a random open
     square.  User input of x exits the game.
 
     Game ends when you reach 1024.
 
     Score: 0
	 .     4     .     .

	 .     .     .     .

	 .     .     4     .

	 .     .     .     .
 
     1. Your move: a
 
     Score: 0
	 4     .     .     .

	 .     .     .     .

	 4     .     .     .

	 .     .     2     .
 
     2. Your move: a
     .
     .
     .
*/

#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board

#include <SFML/Graphics.hpp> // Needed to access all the SFML graphics libraries
          
                             
#include <cstdio>            // For sprintf, "printing" to a string
#include <cstring>           // For c-string functions such as strlen() 
#include <chrono>            // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>            // Used in pausing for some milliseconds using sleep_for(...)

const int WindowXSize = 400;
const int WindowYSize = 500;
//---------------------------------------------------------------------------------------
class Square {
	public:
		// Default Constructor 
		Square()
		{
			size = 0;
			xPosition = 0;
			yPosition = 0;
			color = sf::Color::Black;
			isVisible = false;
			isCaptured = false;
			text = "";		
		}
	
		// Fully-qualified constructor, used to set all fields
		Square( int theSize, int theXPosition, int theYPosition, 
			     const sf::Color &theColor, bool theVisibility, std::string theText)
		{
			// Set the class fields
			size = theSize;
			xPosition = theXPosition;
			yPosition = theYPosition;
			color = theColor;
			isVisible = theVisibility;
			isCaptured = false;   // By default squares have not been captured
			text = theText;
			// Use the values to set the display characteristics of theSquare
			theSquare.setSize( sf::Vector2f(theSize, theSize));
			theSquare.setPosition( theXPosition, theYPosition);   // Set the position of the square
			theSquare.setFillColor( theColor);
		}
			
		// Get (accessor) functions
		sf::RectangleShape getTheSquare() { return theSquare; }
		int getSize() { return size; }
		int getXPosition() { return xPosition; }
		int getYPosition() { return yPosition; }
		sf::Color& getColor() { return color; }
		bool getIsVisible() { return isVisible; }
		bool getIsCaptured() { return isCaptured; }
		std::string getText() { return text; }
	
		// Set (mutator) functions
		void setSize( int theSize) { 
			size = theSize; 
			theSquare.setSize( sf::Vector2f(theSize, theSize));
		}
		void setXPosition( int theXPosition) { 
			xPosition = theXPosition; 
			theSquare.setPosition( theXPosition, yPosition);   // Set the position of the square
		}
		void setYPosition( int theYPosition) { 
			yPosition = theYPosition; 
			theSquare.setPosition( xPosition, theYPosition);   // Set the position of the square
		}
		void setColor( sf::Color & theColor) { 
			color = theColor; 
			theSquare.setFillColor( theColor);    // Also update the color on the square itself
		}
		void setColor( int R, int G, int B) {
			sf::Color theNewColor( R, G, B);
			color = theNewColor;
			theSquare.setFillColor( theNewColor);
		}
		void setVisibility( bool theVisibility) { isVisible = theVisibility; }
		void setIsCaptured( bool isCaptured) { this->isCaptured = isCaptured; }
		void setText( std::string theText) { text = theText; }

		// Utility functions
		void displayText( sf::RenderWindow *pWindow, sf::Font theFont, sf::Color theColor, int textSize);
	
	private:
		int size;
		int xPosition;
		int yPosition;
		sf::Color color;
		bool isVisible;
		bool isCaptured;   // Indicates whether or not it is part of the captured area
		std::string text;
		sf::RectangleShape theSquare;

}; //end class Square


//---------------------------------------------------------------------------------------
// Square class utility function to create a sf::Text object to store and display text 
// associated with this Square.
// 
// Assuming we display output in sf::RenderWindow window(...), then call this function using: 
//    aSquare.displayTest( &window);
// or when using an array of Square pointers declared as:  Square *squaresArray[ 4];
// then call it using:  squaresArray[i]->displayText( &window);
void Square::displayText( 
		sf::RenderWindow *pWindow,   // The window into which we draw everything
		sf::Font theFont,            // Font to be used in displaying text   
		sf::Color theColor,          // Color of the font
		int textSize)                // Size of the text to be displayed
{	
	// Create a sf::Text object to draw the text, using a sf::Text constructor
	sf::Text theText( text,        // text is a class data member
					  theFont,     // font from a font file, passed as a parameter
					  textSize);   // this is the size of text to be displayed

	// Text color is the designated one, unless the background is Yellow, in which case the text
	// color gets changed to blue so we can see it, since we can't see white-on-yellow very well
	if( this->getColor() == sf::Color::Yellow) {
		theColor = sf::Color::Blue;
	}
	theText.setColor( theColor);

	// Place text in the corresponding square, centered in both x (horizontally) and y (vertically)
	// For horizontal center, find the center of the square and subtract half the width of the text 
	int theXPosition = xPosition + (size / 2) - ((strlen(text.c_str()) * theText.getCharacterSize()) / 2);
	// For the vertical center, from the top of the square go down the amount: (square size - text size) / 2
	int theYPosition = yPosition + (size - theText.getCharacterSize()) / 2;
	// Use an additional offset to get it centered
	int offset = 5;
	theText.setPosition( theXPosition + offset, theYPosition - offset);

	// Finally draw the Text object in the RenderWindow
	pWindow->draw( theText);
}


//---------------------------------------------------------------------------------------
// Initialize the font
void initializeFont( sf::Font &theFont)
{
	// Create the global font object from the font file
	if (!theFont.loadFromFile("arial.ttf"))
	{
		std::cout << "Unable to load font. " << std::endl;
		exit( -1);
	}	
}

//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to 1024. \n"
         << "  \n"
         << "For each move enter a direction as a letter key, as follows: \n"
		 << "    W    \n"
		 << "  A S D  \n"
		 << "where A=left,W=up, D=right and S=down. \n"
		 << "  \n"
		 << "After a move, when two identical valued tiles come together they    \n"
		 << "join to become a new single tile with the value of the sum of the   \n"
		 << "two originals. This value gets added to the score.  On each move    \n"
		 << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		 << "square.  User input of x exits the game.                            \n"
		 << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide*squaresPerSide);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
}//end placeRandomPiece()

// Creating the function that takes in the board, squaresPerSide, and the score which displays the board when it is called
void displayAsciiBoard(int* x, int y, int z) {
    cout << endl;
    cout << "Score: " << z << endl;
    
    for (int i = 0; i < y; i++) {
        int a1;
        cout << "    ";
        for (int j = 0; j < y; j++) {
            a1 = (y * i) + j;
            
            cout << setw(6);
            //cout << "     ";
            if (x[a1] != 0) {
                cout << x[a1];
            } else {
              cout << '.';  
            }
            
        }
        cout << endl;
        cout << endl;
    }
}

// Creating the function where it takes in the board, squaresPerSide, and the maxTileValue to create the new board
int getSizeAndSetBoard(int* x,int &z, int &a) {
    for(int i = 0; i < z; i++) {
        for(int j = 0; j < z; j++) {
            x[(i * z) + j] = 0;
        }
    }
    a = 1024;
    for(int k = 4; k < z; k++) {
        a = a * 2;
    }
    
    cout << endl;
    cout << "Game ends when you reach " << a << "." << endl;
    placeRandomPiece(x,z);
    placeRandomPiece(x,z);
}

// Creating the function that takes in the board, the copyBoard, and squaresPerSide so it can copy the board's content
void copyBoard(int* x, int* y, int z) {
    for(int i = 0; i < z; i++) {
        for(int j = 0; j < z; j++) {
            y[z * i + j] = x[z * i + j];
        }
    }
}

// Creating the function that takes in the board, the copyBoard, and squaresPerSide to compare both boards to see if 
// they are different.
int boardChanged(int* x, int* y, int z) {
    for(int i = 0; i < z; i++) {
        for(int j = 0; j < z; j++) {
            if (x[z * i + j] != y[z * i + j]) {
                return 1;
            }
        }
    }
    return 0;
}

// Creating the function that takes the board, squaresPerSide, and the score to slide the values to the left on the board
void slideLeft(int* board, int squaresPerSide, int &score) {
    int x;
    int k;
    for(int i = 0; i < squaresPerSide; ++i) {
        x = squaresPerSide * i;
        for(int j = 1; j < squaresPerSide; ++j) {
            for(k = squaresPerSide * i + j; k > x; --k) {
                if(board[k - 1] == 0) {
                    board[k - 1] = board[k];
                    board[k] = 0;
                }
                if (board[k - 1] == board[k]) {
                    if(board[k] != 0) {
                       board[k - 1] = board[k - 1] + board[k];
                    board[k] = 0;
                    x = k;
                    score = score + board[k - 1]; 
                    }
                }
                
            }
        }
    }   
}

// Creating the function that takes the board, squaresPerSide, and the score to slide the values to the right on the board
void slideRight(int* board, int squaresPerSide, int &score) {
    int x;
    int k;
    for(int i = 0; i < squaresPerSide; i++) {
        x = squaresPerSide * (i + 1) - 1;
        for(int j = squaresPerSide - 1; j >= 0; --j) {
            for(k = squaresPerSide * i + j; k < x && !board[k + 1]; k++) {
                board[k + 1] = board[k];
                board[k] = 0;
            }
            if(k < x && board[k + 1] == board[k]) {
                if(board[k]) {
                    board[k + 1] = board[k + 1] + board[k];
                    board[k] = 0;
                    x = k;
                    score = score + board[k + 1];
                }
            }
        }
    }
}

// Creating the function that takes the board, squaresPerSide, and the score to slide the values up on the board
void slideUp(int* board, int squaresPerSide, int &score) {
    int x;
    int k;
    // i is column
    // j is every row
    for(int i = 0; i < squaresPerSide; i++) {
        x = i;
        for(int j = 0; j < squaresPerSide; j++) {
            for (k = squaresPerSide * j + i; k > i && !board[k - squaresPerSide]; k -= squaresPerSide) {
                board[k - squaresPerSide] = board[k];
                board[k] = 0;
            }
            if(k > i && board[k - squaresPerSide] == board[k]) {
                if(board[k]) {
                    board[k - squaresPerSide] = board[k - squaresPerSide] + board[k];
                    board[k] = 0;
                    x = k;
                    score = score + board[k - squaresPerSide];
                }
            }
        }
    }
}

// Creating the function that takes the board, squaresPerSide, and the score to slide the values down on the board
void slideDown(int* board, int squaresPerSide, int &score) {
    int x;
    int k;
    for(int i = 0; i < squaresPerSide; i++) {
        x = squaresPerSide * (squaresPerSide - 1) + i;
        for(int j = squaresPerSide - 1; j >= 0; j--) {
            for(k = squaresPerSide * j + i; k < x && !board[k + squaresPerSide]; k += squaresPerSide) {
                board[k + squaresPerSide] = board[k];
                board[k] = 0;
            }
            if(k < x && board[k + squaresPerSide] == board[k]) {
                if(board[k]) {
                    board[k + squaresPerSide] = board[k + squaresPerSide] + board[k];
                    board[k] = 0;
                    x = k;
                    score = score + board[k + squaresPerSide];
                }
            }
        }
    }
}

// Creating a function that takes in the board, squaresPerSide, and the maxTileValue to check if the maxTileValue is present
// on the board.
int gameOver(int* board, int squaresPerSide, int maxTileValue) {
    int x;
    int secondBoard[MaxBoardSize * MaxBoardSize];
    for(int i = 0; i < squaresPerSide * squaresPerSide; i++) {
        if(board[i] == maxTileValue) {
           cout << "Congratulations!  You made it to " << maxTileValue << " !!!" << endl;
            return 1;
        }
    }
    
    for(int j = 0; j < squaresPerSide * squaresPerSide; j++) {
        if(!board[j]) {
            return 0;
        } 
    }
    
    copyBoard(board,secondBoard,squaresPerSide);
    x = 0;
    slideLeft(secondBoard,squaresPerSide,x);
    slideDown(secondBoard,squaresPerSide,x);
    
    for(int k = 0; k < squaresPerSide * squaresPerSide; k++) {
        if(secondBoard[k] != board[k]) {
            return 0;
        }
    }
    
    cout << endl;
    cout << "No more available moves.  Game is over." << endl;
    cout << endl;
    return 1;
}


//---------------------------------------------------------------------------------------
int main()
{
    int score = 0;
    int squaresPerSide = 4;        // User will enter this value.  Set default to 4
    int board[ MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
                                                      //    if a move changed the board.
    //int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    //char userInput = ' ';                  // handles user input
    int move = 1;                         // user move counter
    
    int input;
    int input2;
    
    // Create the graphical board, an array of Square objects set to be the max size it will ever be.
	Square squaresArray[ MaxBoardSize * MaxBoardSize]; 
    int maxTileValue = 1024;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';     // Stores user input
	char aString[ 81];        // C-string to hold concatenated output of character literals

	// Create the graphics window
	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "Program 5: 1024");
	std::cout << std::endl;
    // Create and initialize the font, to be used in displaying text.
	sf::Font font;  
	initializeFont( font);
	// Create the messages label at the bottom of the graphics screen, for displaying debugging information
	sf::Text messagesLabel( "Welcome to 1024", font, 20);
	// Make a text object from the font
	messagesLabel.setColor( sf::Color(255,255,255));
	// Place text at the bottom of the window. Position offsets are x,y from 0,0 in upper-left of window
	messagesLabel.setPosition( 0, WindowYSize - messagesLabel.getCharacterSize() - 5); 
	
    displayInstructions();
    
    // Get the board size, create and initialize the board, and set the max tile value depending on board size
    // ..
    getSizeAndSetBoard(board,squaresPerSide,maxTileValue);
    // Infinite loop to run program until user selects exit, board is full, or max tile value is reached
    while(window.isOpen())
    {
        // Create array of Square objects
	//int arraySize = 4;
	//Square squaresArray[ arraySize];
	for( int i=0; i<MaxBoardSize*MaxBoardSize; i++) {
		// Allocate each square individually.
		// Store a string in each square which contains its number, in order of creation
		char name[ 81];
		// Squares with a 0 value should not have a number displayed
		if( board[ i] == 0) {
			strcpy( name, "");   // "print" a blank text string
		}
		else {
		   sprintf( name, "%d", board[ i]);   // "print" the square creation order number into a string to be stored in the square
		}
		// Set each array pointer have the address of a new Square, created with a Square constructor
		squaresArray[ i] = Square(50, 50 * i + i*10, 0, sf::Color::Red, true, name);
		// Draw the square
		window.draw( squaresArray[ i].getTheSquare());
		// Draw the text associated with the Square, in the window with the indicated color and text size
		int red = 255, green = 255, blue = 255;
		squaresArray[i].displayText( &window, font, sf::Color(red, green, blue), 30);
	}
	// Display the background frame buffer, replacing the previous RenderWindow frame contents.
	// This is known as "double-buffering", where you first draw into a background frame, and then
	// replace the currently displayed frame with this background frame.
	window.display();
	
        
        
        
        // Display the text-based board
        displayAsciiBoard( board, squaresPerSide, score);
        
        // Make a copy of the board.  After we then attempt a move, the copy will be used to
        // verify that the board changed, which only then allows randomly placing an additional
        // piece on the board and updating the move number.
        // ...
        copyBoard(board,previousBoard,squaresPerSide);
        // Prompt for and handle user input
        cout << move << ". Your move: ";
        cin >> userInput;
        
        // Creating if-else statements for the various userInputs
        if(userInput == 'a') {
            slideLeft(board,squaresPerSide,score);
        } else if (userInput == 'd') {
            slideRight(board,squaresPerSide,score);
        } else if (userInput == 'p') {
            cin >> input;
            cin >> input2;
            board[input] = input2;
            continue;
        } else if (userInput == 'r') {
            cout << endl;
            cout << endl;
            cout << "Resetting board " << endl;
            cout << endl;
            cout << "Enter the size board you want, between 4 and 12: ";
            cin >> input;
            squaresPerSide = input;
            getSizeAndSetBoard(board,squaresPerSide,maxTileValue);
            score = 0;
            move = 1;
            continue;
        } else if (userInput == 's') {
            slideDown(board,squaresPerSide,score);
        } else if (userInput == 'w') {
            slideUp(board,squaresPerSide,score);
        } else if (userInput == 'x') {
            cout << endl;
            cout << "Thanks for playing. Exiting program... \n\n";
            exit( 0);
            break;
        } else {
            cout << "Invalid input, please retry.";
            continue;
            break;
        }
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update the move number.
        // ...
        if(boardChanged(board,previousBoard,squaresPerSide) == 1) {
            placeRandomPiece(board,squaresPerSide);
            move++;
        }
        // See if we're done.  If so, display the final board and break.
        // ...
        if(!gameOver(board,squaresPerSide,maxTileValue)) {
            std::this_thread::sleep_for(std::chrono::milliseconds( 50));
            continue;
        }
        displayAsciiBoard(board,squaresPerSide,score);
        break;
        //system("clear");   // Clear the screen in UNIX / Codio.  Should be "cls" on windows.
                             //     May not work in default Mac Xcode configuration, or some other environments.
        
    }//end while( true)

    return 0;
}//end main()