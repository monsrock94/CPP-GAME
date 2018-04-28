#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all values initialised to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGUESSSTATUS {
	OK,
	NOT_VALID,
	NOT_ISOGRAM,
	Wrong_Length,
	Not_Lowercase,
};
class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void GetHiddenWord(int32);
	bool IsGameWon() const;
    EGUESSSTATUS CheckGuessValidity(FString) const; // TODO make a more rich return value.

	void Reset(); // TODO make a more rich return value.
	
	// provide a method for counting bulls & cows, and increasing try #

	//counts bulls & cows and increase try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);


// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};