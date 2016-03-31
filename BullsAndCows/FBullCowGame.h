#pragma once

#include <string>

using FString = std::string;
using int32 = int;

constexpr int32 DEFAULT_BASE_CURRENT_TRY = 1;
const FString DEFAULT_HIDDEN_WORD = "cosigned";

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	InvalidStatus,
	OK,
	NotIsogram,
	TooShort,
	TooLong,
	NotLowercase
};

class FBullCowGame {
public:
	//Default values
	FBullCowGame();
	//Set hidden word
	//FBullCowGame(FString);

	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	int32 GetMaxTries() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsLowercase(FString) const;
	bool IsIsogram(FString) const;
};