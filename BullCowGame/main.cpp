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

	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	//is not won and there are still tries remaining
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) { // TODO change from FOR to WHILE loop once we are validating tries
		FText Guess = GetValidGuess(); 

		
		
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
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
	FText Guess = "";

	do 
	{

		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
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
			break;
		}

	} while (GuessStatus != EGUESSSTATUS::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	if (BCGame.IsGameWon() == true) 
	{
		std::cout << "You have won the game.\nDo You want to play again (y/n)?";
		FText Response = "";
		std::getline(std::cin, Response);
		return (Response[0] == 'y') || (Response[0] == 'Y');
	}
	else
	{
		std::cout << "You loose better luck next time!!\nDo you want to play again (y/n)? ";
		FText Response = "";
		std::getline(std::cin, Response);
		return (Response[0] == 'y') || (Response[0] == 'Y');
	}
	

}
