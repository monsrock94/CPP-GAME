#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const {return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return static_cast<int32>(MyHiddenWord.length());}



void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGUESSSTATUS FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (false)//if not an isogram
	{
		return EGUESSSTATUS::NOT_ISOGRAM;
	}
	else if (false)
	{
		return EGUESSSTATUS::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength() )
	{
		return EGUESSSTATUS::Wrong_Length;

	}
	else
	{
		return EGUESSSTATUS::OK;
	}
}

//receives a valid guess, and increments turns and returns counts of bulls and cows 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	int32 WordLength = static_cast<int32>(MyHiddenWord.length());

	//increment the turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;


	//loop through all letters in the hidden word
	for (int32 MHCHAR = 0; MHCHAR < WordLength; MHCHAR++)
	{
		//compare letters against the guess
		for (int32 GCHAR = 0; GCHAR < WordLength; GCHAR++)
		{
			//if they match then
			if (Guess[GCHAR] == MyHiddenWord[MHCHAR])
			{
				//increment bulls if they are in the same place
				if (GCHAR == MHCHAR)
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

