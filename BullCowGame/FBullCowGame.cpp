#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const {return MyMaxTries;}
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return static_cast<int32>(MyHiddenWord.length());}
bool FBullCowGame::IsGameWon() const {return bGameWon;}


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}



EGUESSSTATUS FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess))//if not an isogram
	{
		return EGUESSSTATUS::NOT_ISOGRAM;
	}
	else if (!IsLowercase(Guess))
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
	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		 bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const 
{
	//treat 0 and 1 letter word as isogram

	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; //setup our map
		for (auto Letter : Word)
		{
			Letter = tolower(Letter);//handle mixed case
			if (LetterSeen[Letter]) //if the letter is in the map
			{
				return false; //we do NOT have an isogram
			}
			else 
			{
				LetterSeen[Letter] = true; // add the letter to the map as seen
			}
		}
	//TODO get the guess from the user
	//TODO compare them against hash table for duplicate letter
	//TODO return if the word is isogram(true) or not isogram(false) accordingly
	return true;// for example in cases where /0 is entered 
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

