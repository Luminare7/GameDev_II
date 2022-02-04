#include <iostream>
#include <ctime>

void printIntroduction(int Difficulty)
{

    std::cout << std::endl;
    std::cout << "You are a secret agent breaking into a " << Difficulty << " secret server room.. \n" ;
    std::cout << "Enter the correct code to proceed.. \n";
    std::cout << std::endl;
}
bool playGame(int Difficulty)
{
    printIntroduction(Difficulty);

    const int CodeA = rand() % (Difficulty*2); 
    const int CodeB = rand() % (Difficulty*2);
    const int CodeC = rand() % (Difficulty*2);
    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    std::cout << std::endl;
    std::cout << "there are 3 numbers in the code \n" << std::endl;
    std::cout << "The code adds-up to: " << CodeSum << std::endl;
    std::cout << "The product of its digits is: " << CodeProduct << std::endl;

    //Store player guess
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Verify player guess
    if(GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        //something happens if I win
        std::cout << "Bravo!\n \n \n \n" << "MOVING TO THE NEXT LEVEL \n \n \n";
        return true;
    }
    else
    {
        //something happens if I lose
        std::cout << "Try again or Die! \n \n \n \n" << "UNABLE TO PROCEED \n \n \n";
        return false;
    }
}



int main()
{
    srand(time(NULL));
    int LevelDifficulty = 1;
    const int maxDiffLevel = 5;
    while(LevelDifficulty <= maxDiffLevel)
    {
        bool bLevelComplete = playGame(LevelDifficulty);
        if(bLevelComplete)
        {
            //increase difficulty
            LevelDifficulty++;
        }
        std::cin.clear();
        std::cin.ignore();
    }

    std::cout << "\n \n \n \n CONGRATULATIONS!!!! \n \n \n \n";
    return 0;
}
