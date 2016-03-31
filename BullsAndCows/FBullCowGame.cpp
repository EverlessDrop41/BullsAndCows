#include "FBullCowGame.h"
#include <map>
#define TMap std::map  

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	if (MyHiddenWord.length() > 6) { return 30; }
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 4 },{ 4, 7 },{ 5,10 },{ 6,16 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyCurrentTry = DEFAULT_BASE_CURRENT_TRY;
	MyHiddenWord = DEFAULT_HIDDEN_WORD;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (guess.length() != GetHiddenWordLength()) {
		if (guess.length() > GetHiddenWordLength()) {
			return EGuessStatus::TooLong;
		}
		else
		{
			return EGuessStatus::TooShort;
		}
	}
	else if (!IsIsogram(guess)) {
		return EGuessStatus::NotIsogram;
	}
	else if (!IsLowercase(guess)) {
		return EGuessStatus::NotLowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments tries, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	for (int32 HWCharIndex = 0; HWCharIndex < MyHiddenWord.length(); HWCharIndex++) {
		char hiddenWordChar = MyHiddenWord[HWCharIndex];
		// compare letters against the guess
		for (int32 GCharIndex = 0; GCharIndex < guess.length(); GCharIndex++) {
			char guessChar = guess[GCharIndex];
			//if they match then
			if (hiddenWordChar == guessChar) {
				//if they're in the same place
				if (HWCharIndex == GCharIndex) {
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (guess == MyHiddenWord) {
		bGameIsWon = true;
	}
		
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto Letter : word) {
		if (!islower(Letter)) { return false;  }
	}

	return true;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() < 2) { return true; }

	//define a hash map
	TMap<char,bool> LetterSeen;

	//loop through each character in the word
	for (auto Letter : word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}

	return true;
}
