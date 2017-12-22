
#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
    
};


class FBullCowGame {
public:
    FBullCowGame(); // Constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    //Counts bulls & cows , and increases try # assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private:
    // See Constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

#endif /* FBullCowGame_hpp */
