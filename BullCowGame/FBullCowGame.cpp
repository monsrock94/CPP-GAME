#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;

	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
}

//receives a valid guess, and increments turns and returns counts of bulls and cows 
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;


	//loop through all letters in the guess
	int HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		//compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++) 
		{
			//if they match then
			if (Guess[i] == MyHiddenWord[i])
			{
				//increment bulls if they are in the same place
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					//increment cows if not
					BullCowCount.Cows++;
				}
			}

		}
			
	}
	return BullCowCount;
}
