/* This is the console executable that makes use of the Bull cow class
 this acts as the view in a MVX pattern, and is responsible for all user
 interaction. For game logic see the FBullCowGame class.
 */

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// To make syntax Unreal friendly
using FText = std::string;
using int32 = int;


void PrintIntro();
FText GetValidGuess();
bool AskToPlayAgain();
void PlayGame();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game, re-use across plays


// Entry point for our application
int main(int argc, const char * argv[]) {
    bool bPlayAgain = false;
    do {
    PrintIntro();
    PlayGame();
    bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    return 0;
}

void PrintIntro(){
    // Introduce the game

    std::cout << "\n\nWelcome To Bulls and Cows" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letters isogram I'm thinking of?" << std::endl;
    return;
}

void PlayGame() {
    //Reset the game state
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // Loop asking for guesses while the game is not won
    // and there are still tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess();         //Submit valid guess to the game, and receives couts
        
        //Submit valid guess to the game,  and recieve counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls equals : " << BullCowCount.Bulls;
        std::cout << " & Cows equals : " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

// Loop continually until the user gives a valid guess
FText GetValidGuess(){
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess= "";
    do{
        // Get a guess from the player
        int32 MyCurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << MyCurrentTry <<  " of " << BCGame.GetMaxTries() << " Please enter the a "<< BCGame.GetHiddenWordLength() << " letters world: ";
        getline(std::cin, Guess);
        
        //Check Status and give feedback
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
        case EGuessStatus::Wrong_Length:
            std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letters word. \n\n";
            break;
        
        case EGuessStatus::Not_Isogram:
            std::cout << " Please enter a VALID Isogram (Word without repeating letters) . \n\n ";
            break;
        
        case EGuessStatus::Not_Lowercase:
            std::cout << " Please enter your guess in lowercase. \n\n";
            break;
            
        default:
            
            break;
        }
        
    } while (Status != EGuessStatus::OK); // Keep looping until valid answer
    return Guess;
}

bool AskToPlayAgain(){
    std::cout << "Do you want to play again with the same Hidden Word (y/n) ? ";
    FText Response = "";
    getline (std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary(){
    if (BCGame.IsGameWon()){
        std::cout << "Well Done! You have Won the Game!! \n " << std::endl;
    }
    else {
        std::cout << "Better Luck in next Game!! \n  " << std::endl;
    }
}


