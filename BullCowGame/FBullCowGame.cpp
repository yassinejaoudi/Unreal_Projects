#pragma once

#include "FBullCowGame.hpp"
#include <map>

// To make Syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;  }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

FBullCowGame::FBullCowGame(){ Reset(); } // default constructor


void FBullCowGame::Reset(){

    const FString HIDDEN_WORD = "and"; // This MUST be an ISOGRAM
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
    if (!IsIsogram(Guess)) // if the guess is not an isogran
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(Guess)) // if the guess is not all lower guess
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() !=  GetHiddenWordLength()) // if the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}
    

//Recieves a valid guess, increaments turn, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length(); // Assuming same length as guess
    
    //Loop through all the letters in the hidden word
    for (int32 MHWChar =0; MHWChar < WordLength; MHWChar++){
        //Compare letters against the guess
        for (int32 GChar =0; GChar<WordLength; GChar++){
            //if they match then
            if (Guess[GChar] == MyHiddenWord[MHWChar]){
                //if they in the same place
                if (MHWChar == GChar){
                    BullCowCount.Bulls++; //increment bulls
                }
                else{
                    BullCowCount.Cows++;  //increment cows
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength){
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    // Treat 0 and 1 letter words as Isograms
    if (Word.length() <= 1) { return true;}
    
    TMap<char, bool> LetterSeen; //Set up our map
    for (auto Letter : Word) { // for all letters of the word
        Letter = tolower(Letter); // handle mixed case
        if (LetterSeen[Letter]){// if the letter is in the map
            return false;  // we do not have an isogram
        } else {
            LetterSeen[Letter] = true; // add the letter to the map as seen
        }
    }
    
    return true; // for example in cases where \0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const {
    for (auto Letter : Word ){
        if (!islower(Letter)){
            return false;
        }
    }
    return true;
}
