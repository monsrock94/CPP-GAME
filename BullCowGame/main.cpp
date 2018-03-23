/* This is the console executable, that makes use of the BullCow class 
This acts as the view in a MVC pattern, and is responsible for all user interaction
for game logic see the FBullCowGame class.
*/
#include <iostream>
#include <string>	
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}

 
// introduce the game
void PrintIntro()
{

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop for the number of turns asking for guesses
	
	for (int32 count = 1; count <= MaxTries; count++) { // TODO change from FOR to WHILE loop once we are validating tries
		FText Guess = GetValidGuess(); 

		
		
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		// print number of bulls and cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << ".\n\n";

	}

	// TODO summarise game
}


// TODO make loop checking valid
FText GetValidGuess()// TODO change to GetValidGuess
{

	EGUESSSTATUS GuessStatus = EGUESSSTATUS::NOT_VALID;

	do 
	{

		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		GuessStatus = BCGame.CheckGuessValidity(Guess);

		switch (GuessStatus)
		{
		case EGUESSSTATUS::NOT_ISOGRAM:
			std::cout << "please enter an ISOGRAM i.e a word with no repeating letters!!.\n";
			break;
		case EGUESSSTATUS::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGUESSSTATUS::Not_Lowercase:
			std::cout << "please enter all letters in lower case.\n" << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			return Guess;
		}

	} while (GuessStatus != EGUESSSTATUS::OK);
}

bool AskToPlayAgain()
{

	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

}
