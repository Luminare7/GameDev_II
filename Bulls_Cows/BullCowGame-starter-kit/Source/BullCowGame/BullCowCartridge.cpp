// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt"); // Path to the file
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath); //Function to populate the WordList array 

    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& WordList)
    {
        return WordList.Len() >= 4 && WordList.Len() <= 10 && IsIsogram(WordList);
    });

    // Isograms = GetValidWords(WordList);

    SetupGame(); 
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

/*   if the game is over then do ClearScreen() and SetupGame() 
    else check the playerGuess() */
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
        return;
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame() 
{
    //Welcome the player
    PrintLine(TEXT("Welcome to BullCows"));
    
    Hiddenword = Isograms[FMath::RandRange(0, Isograms.Num()-1)];  //Set hidden word
    Lives = Hiddenword.Len();                  //Set lives
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), Hiddenword.Len());  
    PrintLine(TEXT("Type in your guess and \npress Enter to Continue..."));  //Prompt player for guess
    PrintLine(TEXT("Your number of lives is: %i."), Lives);
    // PrintLine(TEXT("Tere are %i words in the list!"), WordList.Num());
    PrintLine(TEXT("The Hiddenword is: %s."), *Hiddenword); //Debug Line 

/*     const TCHAR HW[] = TEXT("plums");
    PrintLine(TEXT("Character 1 of the Hidden word is: %c"), HW[0]);
    HW; */
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    //CheckPlayerGuess
    if(Guess == Hiddenword)
    {
        PrintLine(TEXT("You have won!!!"));
        EndGame();
        return;
    }

    if(Guess.Len() != Hiddenword.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), Hiddenword.Len());
        PrintLine(TEXT("Sorry, guess again.\nYou have %i lives left"), Lives);
        return;
    }

    //Check if it's an isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("There are no repeating letters.. \nGuess again."));
        return;
    }

    //Prompt to Guess Again and Remove a life
    PrintLine(TEXT("You've lost a life."));
    --Lives;

    //Check if lives > 0
    if(Lives<=0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was %s!!"), *Hiddenword);
        EndGame(); 
        return;
    }
    //Show the player the bulls and the cows
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows!"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess again, \nyou have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)  //If your function doesn't alter any member variable, make it a const function
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex]==Hiddenword[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for(int32 HiddenWordIndex = 0; HiddenWordIndex < Hiddenword.Len(); HiddenWordIndex ++)
        {
            if(Guess[GuessIndex] == Hiddenword[HiddenWordIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}
/* 
TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    //

    TArray<FString> ValidWords;

    for(FString Wrd : WordList) 
    {
        if (Wrd.Len() >=4 && Wrd.Len() <= 8 && IsIsogram(Wrd) == true)
        {
            ValidWords.Emplace(Wrd);
        }
    }
    return ValidWords;
} */