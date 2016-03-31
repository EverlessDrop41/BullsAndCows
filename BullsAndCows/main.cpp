//
//  BullsAndCows
//  
//  The console executable
//
//  Created by Emily Peregrine on 26/03/2016.
//  Copyright © 2016 Emily Peregrine. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using std::cout;
using std::cin;
using std::endl;

using int32 = int;
using FText = std::string;

void PrintIntro();
FText GetInput(FText prompt);
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;

int main(int argc, const char * argv[]) {
	PrintIntro();

	do {
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro() {
	cout << "Welcome to bulls and cows, a fun word game" << endl;
	cout << "Can you think of the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? " << endl << endl;
}

void PlayGame() {
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		if (!BCGame.IsGameWon()) {
			cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows << endl << endl;
		}
	}

	PrintGameSummary();
	BCGame.Reset();
}

bool AskToPlayAgain() {
	FText response = " ";

	while (tolower(response[0]) != 'y' && tolower(response[0]) != 'n') {
		response = GetInput("Would you like to play again? (Y or N): ");
		if (tolower(response[0]) != 'y' && tolower(response[0]) != 'n') {
			cout << "Please enter a valid response! " << endl;
		}
	}

	return tolower(response[0]) == 'y';
}

FText GetValidGuess() {

	const int32 CurrentGuess = BCGame.GetCurrentTry();
	const int32 MaxTries = BCGame.GetMaxTries();
	EGuessStatus Status = EGuessStatus::InvalidStatus;

	while (true){
		cout << "You have " << MaxTries - CurrentGuess << " guess(es) remaining" << endl << endl;
		FText Guess = GetInput("Enter your guess: ");

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::NotIsogram:
			cout << "Not an isogram! An isogram is when a word has no repeating letters\n";
			break;
		case EGuessStatus::TooShort:
			cout << "Too Short, Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n";
			break;
		case EGuessStatus::TooLong:
			cout << "Too Long, Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n";
			break;
		case EGuessStatus::NotLowercase:
			cout << "UPPER CASE DETECTED!!! please make sure your guess is in lowercase\n";
			break;
		case EGuessStatus::InvalidStatus:
			cout << "ERROR, INVALID STATUS";
		default:
			return Guess;
		}
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		cout << "Congrats, you guessed the isogram\n\n";
	}
	else {
		cout << "Sorry, you ran out of guesses, Better luck next time!\n\n";
	}
}

FText GetInput(FText prompt) {
	cout << prompt;
	FText input;
	std::getline(cin, input);
	return input;
}