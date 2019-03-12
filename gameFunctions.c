#include <math.h>
#include <stdio.h>
#include <string.h>

#include "gameFunctions.h"

initializeBlankString() {}

printWithSpaces() {}

revealGuessedLetter() {}

checkGuess() {}

void startGame(char word[25]) {
  int won = 0;  // Flag to see if the user has won yet
  int numBadGuesses = 0;  // Counter to end the game on a lose condition
  int possibleBadGuesses;  // Total number of bad guesses allowed
  int charRevealed;  // Flag to see if the user guessed a good letter
  char guess;  // The user's guess
  char revealedLetters[25];  // What the user has revealed so far

  // Initializes the guessing array to all underscores
  initializeBlankString(strlen(word), revealedLetters);
  clearScreen();

  // Gets the total number of chances
  printf(
      "Please enter the total number of incorrect guesses you would like to be "
      "able to make: ");
  scanf("%d", &possibleBadGuesses);
  printWithSpaces(revealedLetters);

  // Runs the game loop until the number of tries are exhausted or the word is
  // found
  while (numBadGuesses <= possibleBadGuesses && !won) {
    printf("Enter a letter to guess: ");
    scanf(" %c", &guess);

    // Updates the revealed letters and checks to see if the user won
    charRevealed = revealGuessedLetter(word, revealedLetters, guess);
    won = checkGuess(word, revealedLetters);

    // Increments bad guesses if the last guess was a miss
    if (!charRevealed) {
      numBadGuesses++;
    }

    // Outputs game information to the user
    drawHorse(numBadGuesses, possibleBadGuesses);
    printWithSpaces(revealedLetters);
  }

  if (won)
    printf("Congratulations!  You correctly guessed the word %s\n", word);
  else
    printf("You've run out of guesses.  The correct word was %s\n", word);
}

// Draws part of the horse pending on how many guesses have been made so far
// Horse grabbed from: http://www.virtualhorses.com/graphics/asciiart.htm
// And no, I don't know why there's an entire site dedicated to virtualhorses =/
void drawHorse(int guessedSoFar, int allowedGuesses) {
  // The horse!  Duh!
  char horsey[14][29] = {{"    (\\(\\_\\\0"},
                         {" _.o o`\\\\\\\\\0"},
                         {"('_     ))))\0"},
                         {" '---'  ((((          .=,\0"},
                         {"     )   )))___.-''-./=;\\\\\\\0"},
                         {"    /    (((         \\  ))))\0"},
                         {"   ;                  | |//\0"},
                         {"   /\\          |      | ((\0"},
                         {"  (  \\    /__.-'\\    /   )\0"},
                         {" / /` |  /    \\  \\  |\0"},
                         {"/ /   \\ ;      \\ (\\ (\0"},
                         {"\\\\_    ||       || ||\0"},
                         {" \\_]   ||       || ||\0"},
                         {"      /_<      /_</_< \0"}};

  clearScreen();

  // Determines how much of the horse to print and prints it
  double ratio = (double)guessedSoFar / (double)allowedGuesses;
  int linesToDraw = floor(ratio * 13);
  linesToDraw = linesToDraw <= 14 ? linesToDraw : 14;

  int i;
  for (i = 14 - linesToDraw; i < 14; i++) {
    printf("%s\n", horsey[i]);
  }
}

void clearScreen() {
  // Some UNIX hackary to clear the terminal.  Makes this not portable to some
  // systems,
  // but should work fine on CSE
  printf("\033[2J");
  printf("\033[0;0f");
}



/*----------------------------------------------------------------------------------------------------------------------------------------------*/

//This is my work so far
void initializeBlankString(int size, char arr[size]){ // Should initialize the blank string with '_' in each spot except the null character \0
	for (int i = 0; i < size - 1; i++){
		arr[i] = '_';
	}
}

void printWithSpaces(char * arr[]){
	int size = strlen(*arr[]);
	for (int i = 0; i < size - 1; i++){
		printf("%s ", *arr[i]);
	}
}

int revealGuessedLetter(char *arr[], char *arrUS[], char guess){ // arrUS stands for Array Underscores
	int size = strlen(*arr[]);
	for (int i = 0; i < size; i++){
		if (*arr[i] == guess){
			*arrUS[i] = guess;
			return 1;
		}
		else{
			return 0;
		}
	}
}

int checkGuess(char *arr[], char *arrCmpr[]){ // arrCmpr is short for array compare as in the array the first parameter is compared to
	if (strcmp(*arr[], *arrCmpr[]) == 0){
		return 1;
	}
	else {
		return 0;
	}
}
