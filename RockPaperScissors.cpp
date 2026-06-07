#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

enum enChoice
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};

enum enResult
{
    PlayerWin = 1,
    PlayerLose = 2,
    Draw = 3
};

int RandomNumber(int From, int To)
{
    return From + rand() % (To - From + 1) ;
}

bool numberInRange(int From, int To, int num) {
    	return (From <= num && num <= To);
 }

int readPositiveNum(string message1) {
    int num;
    do {
        cout << message1;
        cin >> num;
    } while (!numberInRange(1,10,num));
    return num;
}

void ReadHowManyRounds(short& GameRounds)
{
    do
    {
        GameRounds = readPositiveNum("How many rounds do you want to play? ");
    } while (GameRounds < 1);
}

void ReadPlayerChoice(enChoice& PlayerChoice)
{
    short Choice;

    do
    {
        cout << "\nYour Choice:\n";
        cout << "[1] Rock\n";
        cout << "[2] Paper\n";
        cout << "[3] Scissors\n";
        cout << "Enter your choice: ";
        cin >> Choice;

    } while (!numberInRange(1,3,Choice));

    PlayerChoice = (enChoice)Choice;
}

void GetComputerChoice(enChoice& ComputerChoice)
{
    ComputerChoice = (enChoice)RandomNumber(1, 3);
}

string ChoiceToString(enChoice Choice)
{
    switch (Choice)
    {
    case Rock:
        return "Rock";

    case Paper:
        return "Paper";


    default:
        return "Scissors";
    }
}

string ResultToString(enResult Result)
{
    switch (Result)
    {
    case PlayerWin:
        return "Player Win";

    case PlayerLose:
        return "Computer Win";

    default:
        return "Draw";
    }
}

void GetRoundResult(enChoice PlayerChoice, enChoice ComputerChoice, enResult& Result)
{
    if (PlayerChoice == ComputerChoice)
    {
        Result = Draw;
    }
    else if (PlayerChoice == Rock && ComputerChoice == Scissors)
    {
        Result = PlayerWin;
    }
    else if (PlayerChoice == Paper && ComputerChoice == Rock)
    {
        Result = PlayerWin;
    }
    else if (PlayerChoice == Scissors && ComputerChoice == Paper)
    {
        Result = PlayerWin;
    }
    else
    {
        Result = PlayerLose;
    }
}

void ShowScreenResult(enResult Result)
{
    if (Result == PlayerWin)
    {
        system("color 2F"); 
    }
    else if (Result == PlayerLose)
    {
        system("color 4F"); 
        cout << "\a";       
    }
    else
    {
        system("color 6F");
    }
}

void PrintRoundHeader(short RoundNumber)
{
    cout << "\n\n";
    cout << "========== Round [" << RoundNumber << "] ==========\n";
}

void PrintRoundResult(short RoundNumber,enChoice PlayerChoice,  enChoice ComputerChoice, enResult Result)
{
    cout << "\n____________ Round [" << RoundNumber << "] Result ____________\n";
    cout << "Player Choice   : " << ChoiceToString(PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceToString(ComputerChoice) << endl;
    cout << "Round Result    : " << ResultToString(Result) << endl;
    cout << "_________________________________________________\n";
}

void UpdateGameResults(enResult Result, short& PlayerWinTimes,short& ComputerWinTimes,short& DrawTimes)
{
    if (Result == PlayerWin)
    {
        PlayerWinTimes++;
    }
    else if (Result == PlayerLose)
    {
        ComputerWinTimes++;
    }
    else
    {
        DrawTimes++;
    }
}

void PlayRound(short RoundNumber,short& PlayerWinTimes,short& ComputerWinTimes,short& DrawTimes)
{
    enChoice PlayerChoice;
    enChoice ComputerChoice;
    enResult Result;

    PrintRoundHeader(RoundNumber);

    ReadPlayerChoice(PlayerChoice);
    GetComputerChoice(ComputerChoice);

    GetRoundResult(PlayerChoice, ComputerChoice, Result);

    ShowScreenResult(Result);

    PrintRoundResult(RoundNumber, PlayerChoice, ComputerChoice, Result);

    UpdateGameResults(Result, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void GetFinalWinner(short PlayerWinTimes,short ComputerWinTimes,enResult& FinalResult)
{
    if (PlayerWinTimes > ComputerWinTimes)
    {
        FinalResult = PlayerWin;
    }
    else if (ComputerWinTimes > PlayerWinTimes)
    {
        FinalResult = PlayerLose;
    }
    else
    {
        FinalResult = Draw;
    }
}

void PrintGameOver()
{
    cout << "\n\n";
    cout << "\t\t====================================\n";
    cout << "\t\t\t+++ GAME OVER +++\n";
    cout << "\t\t====================================\n";
}

void PrintFinalGameResults( short GameRounds,short PlayerWinTimes,short ComputerWinTimes, short DrawTimes)
{
    enResult FinalResult;

    GetFinalWinner(PlayerWinTimes, ComputerWinTimes, FinalResult);

    cout << "\n";
  
    cout << "\t\tGame Rounds        : " << GameRounds << endl;
    cout << "\t\tPlayer Win Times   : " << PlayerWinTimes << endl;
    cout << "\t\tComputer Win Times : " << ComputerWinTimes << endl;
    cout << "\t\tDraw Times         : " << DrawTimes << endl;
    cout << "\t\tFinal Winner       : " << ResultToString(FinalResult) << endl;
    cout << "============================================\n";
}

void AskToPlayAgain(bool& PlayAgain)
{
    char Answer;

    cout << "\nDo you want to play again? Y/N: ";
    cin >> Answer;

    PlayAgain = (Answer == 'Y' || Answer == 'y');
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void PlayGameRounds(short GameRounds,short& PlayerWinTimes, short& ComputerWinTimes, short& DrawTimes)
{
    for (short RoundNumber = 1; RoundNumber <= GameRounds; RoundNumber++)
    {
        PlayRound(RoundNumber, PlayerWinTimes, ComputerWinTimes, DrawTimes);
    }
}

void gamePlay()
{
    bool PlayAgain = true;

    while (PlayAgain)
    {
        short GameRounds = 0;
        short PlayerWinTimes = 0;
        short ComputerWinTimes = 0;
        short DrawTimes = 0;

        ResetScreen();

        ReadHowManyRounds(GameRounds);

        PlayGameRounds(GameRounds, PlayerWinTimes,ComputerWinTimes, DrawTimes);

        PrintGameOver();

        PrintFinalGameResults(GameRounds,PlayerWinTimes,ComputerWinTimes,DrawTimes);

        AskToPlayAgain(PlayAgain);
    }
}

int main()
{
    srand((unsigned)time(NULL));

    gamePlay();



    return 0;
}