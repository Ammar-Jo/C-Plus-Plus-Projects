#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

enum enChoices { Rock = 1, Paper, Scissors };

enum enResult { UserWin = 1, Draw, CompWin };

int ReadPositiveNumber(string msg)
{
	int Number;
	cout << msg;
	do
	{
		cin >> Number;
	} while (Number < 0);

	return Number;
}

short NumberOfRounds()
{
	return ReadPositiveNumber("Enter how many rounds 1 to 10: ");
}

int RandomNumber(int From = 1, int To = 3)
{
	return rand() % (To - From + 1) + From;
}

enChoices ReadUserChoice()
{
	switch (ReadPositiveNumber("\n\nEnter your choice: [1]: Rock, [2]: Paper, [3]: Scissors ? "))
	{
	case 1: return enChoices::Rock;
		break;
	case 2: return enChoices::Paper;
		break;
	case 3: return enChoices::Scissors;
		break;
	default: return enChoices::Rock;
	}
}

enChoices ComputerChoice()
{
	switch (RandomNumber())
	{
	case 1: return enChoices::Rock;
		break;
	case 2: return enChoices::Paper;
		break;
	case 3: return enChoices::Scissors;
	}
}

bool UserWins(enChoices CompChoice, enChoices UserChoice)
{
	if ((UserChoice == enChoices::Rock && CompChoice == enChoices::Scissors)
		|| (UserChoice == enChoices::Scissors && CompChoice == enChoices::Paper)
		|| (UserChoice == enChoices::Paper && CompChoice == enChoices::Rock))
		return true;
	return false;
}

bool CompWins(enChoices CompChoice, enChoices UserChoice)
{
	if ((CompChoice == enChoices::Rock && UserChoice == enChoices::Scissors)
		|| (CompChoice == enChoices::Scissors && UserChoice == enChoices::Paper)
		|| (CompChoice == enChoices::Paper && UserChoice == enChoices::Rock))
		return true;
	return false;
}

void PaintScreen(enResult Winner)
{
	if (Winner == enResult::CompWin)
		system("color 4F");
	else if (Winner == enResult::Draw)
		system("color 6F");
	else if (Winner == enResult::UserWin)
		system("color 2F");
}

enResult Winner(bool UserWinner, bool CompWinner)
{
	if (UserWinner)
		return enResult::UserWin;
	else if (CompWinner)
		return enResult::CompWin;
	else
		return enResult::Draw;
}

void Choice(enChoices comp, enChoices user)
{
	if (comp == 1)
		cout << "\nComputer choice: Rock" << endl;
	else if (comp == 2)
		cout << "\nComputer choice: Paper" << endl;
	else if (comp == 3)
		cout << "\nComputer choice: Scissors" << endl;

	if (user == 1)
		cout << "\nUser choice: Rock" << endl;
	else if (user == 2)
		cout << "\nUser choice: Paper" << endl;
	else if (user == 3)
		cout << "\nUser choice: Scissors" << endl;

}

void PrintResult(enResult Result, enChoices Comp, enChoices User)
{
	switch (Result)
	{
	case enResult::UserWin: PaintScreen(UserWin);
		Choice(Comp, User);
		cout << "\nUser Wins!" << endl;
		break;

	case enResult::Draw: PaintScreen(Draw);
		Choice(Comp, User);
		cout << "\nDraw!" << endl;
		break;

	case enResult::CompWin: PaintScreen(CompWin);
		Choice(Comp, User);
		cout << "\nComputer Wins!\a" << endl;
		break;
	}
}

bool ReplayGame()
{
	char Replay;
	cout << "Do you want to play again: Y/N ? ";
	cin >> Replay;
	if (Replay == 'Y' || Replay == 'y')
	{
		system("cls");
		system("color 07");
		return true;
	}
	return false;
}

void FinalResult(short ComputerWins, short UserWins, short Draws)
{

	cout << "\n\n_________Final Result_________\n\n";
	cout << "\nComputer Wins:\t" << ComputerWins << endl;
	cout << "\nYour Wins    :\t" << UserWins << endl;
	cout << "\nDraws        :\t" << Draws << endl;

	if (ComputerWins > UserWins)
	{
		cout << "\n\nWinner is: COMPUTER\n" << endl;
		PaintScreen(CompWin);
	}
	else if (ComputerWins < UserWins)
	{
		cout << "\n\nWinner is: YOU\n" << endl;
		PaintScreen(UserWin);
	}
	else
		PaintScreen(Draw);

}

void StartGame()
{


	do
	{
		short Rounds = NumberOfRounds(), AllComputerWins = 0, AllUserWins = 0, AllDraws = 0;

		for (int i = 0; i < Rounds; i++)
		{
			bool UserWinner = false, CompWinner = false;

			cout << "\n___________________ROUND[" << i + 1 << "]___________________\n\n";

			enChoices UserChoice = ReadUserChoice(), CompChoice = ComputerChoice();

			if (UserWins(CompChoice, UserChoice)) {
				AllUserWins++;
				UserWinner = true;
			}
			else if (CompWins(CompChoice, UserChoice)) {
				AllComputerWins++;
				CompWinner = true;
			}
			else
				AllDraws++;

			PrintResult(Winner(UserWinner, CompWinner), CompChoice, UserChoice);
			cout << "\n______________________________________________\n\n";

		}

		FinalResult(AllComputerWins, AllUserWins, AllDraws);

		cout << "\n________________END GAME________________\n\n";

	} while (ReplayGame());


}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
}