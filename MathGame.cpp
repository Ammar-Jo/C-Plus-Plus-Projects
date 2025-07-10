#include<iostream>
using namespace std;

enum enDifficultyGame { Easy = 1, Medium, Hard, MixLevel };
enum enOpType { Add = 1, Miuns, Multiply, Division, MixOp };
enum enPassFail { Pass = 1, Fail };

struct stQuizInfo
{
	short NumberOfQuestion;
	enDifficultyGame Difficult;
	enOpType OpType;
	enPassFail PassFail;
	short PassTimes;
	short FailTimes;
};

int ReadNumberOfQuestions()
{
	int Number;
	cout << "Enter Number of questions: ";
	do
	{
		cin >> Number;
	} while (Number <= 0);

	return Number;
}

short ReadNumDifficult()
{
	short Diff;

	do
	{
		cout << "Enter qustions level: [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> Diff;

	} while (Diff < 1 || Diff > 4);

	return Diff;
}

short ReadNumOpType()
{
	short Op;

	do
	{
		cout << "Enter qustions operator: [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> Op;

	} while (Op < 1 || Op > 5);

	return Op;
}

short RandomNumber(short From, short To)
{
	return int(rand() % (To - From + 1) + From);
}

enDifficultyGame Difficulty(short Level)
{
	return enDifficultyGame(Level);
}

string GetLevelName(enDifficultyGame Level)
{
	string LevelArr[4] = { "Easy", "Medium", "Hard", "Mix" };
	return LevelArr[Difficulty(Level) - 1];
}

enOpType OpType(short NumOp)
{
	return enOpType(NumOp);
}

string GetOpName(enOpType Op)
{
	string OpArr[5] = { "Add", "Sub", "Mul", "Div", "Mix" };
	return OpArr[OpType(Op) - 1];
}

char GetOp(enOpType Type)
{

	switch (Type)
	{
	case Add: return '+';
		break;
	case Miuns: return '-';
		break;
	case Multiply: return '*';
		break;
	case Division: return '/';
		break;
	case MixOp: return (GetOp(enOpType(RandomNumber(1, 4))));
		break;

	}
}

enOpType GetMixOp()
{
	return enOpType(RandomNumber(1, 4));
}

void NumbersDependLevel(enDifficultyGame Level, int& Num1, int& Num2)
{
	switch (Level)
	{
	case Easy:
		Num1 = RandomNumber(1, 10);
		Num2 = RandomNumber(1, 10);

		break;

	case Medium:
		Num1 = RandomNumber(10, 50);
		Num2 = RandomNumber(10, 50);
		break;

	case Hard:
		Num1 = RandomNumber(50, 100);
		Num2 = RandomNumber(50, 100);
		break;

	case MixLevel: NumbersDependLevel(enDifficultyGame(RandomNumber(1, 3)), Num1, Num2);
		break;

	};

}

void ScreenColor(enPassFail PassFail)
{
	switch (PassFail)
	{
	case Pass: system("color 2F");
		break;
	case Fail: system("color 4F");
		break;
	}
}

void PrintQuestion(int num1, int num2, enOpType Op)
{
	cout << num1 << endl;
	cout << num2 << GetOp(Op) << endl;
	cout << "_______\n";
}

int Calculate(int num1, int num2, enOpType Op)
{

	switch (Op)
	{
	case Add: return num1 + num2;
		break;
	case Miuns: return num1 - num2;
		break;
	case Multiply: return num1 * num2;
		break;
	case Division: return num1 / num2;
		break;
	}
}

void PrintFinalResult(stQuizInfo Quiz)
{
	cout << "\n\n_________________________\n\n Final Result is ";
	cout << (Quiz.PassFail == enPassFail::Pass ? "Pass :-)\n" : "Fail :-(\n") << "_________________________\n";

	cout << "Number of Questions: " << Quiz.NumberOfQuestion << endl;
	cout << "Question level     : " << GetLevelName(Quiz.Difficult) << endl;
	cout << "Operator Type      : " << GetOpName(Quiz.OpType) << endl;
	cout << "Number of Right Answers: " << Quiz.PassTimes << endl;
	cout << "Number of Wrong Answers: " << Quiz.FailTimes << endl;

	cout << "\n_________________________\n";
}

char WantReplayGame()
{
	char Replay;
	cout << "Do you want to replay game: Y/N ? ";
	cin >> Replay;
	return Replay;
}

void ClearScreen()
{
	system("cls");
	system("color 07");
}

void PlayGame()
{
	stQuizInfo Info;

	int NumberOfQuestions = ReadNumberOfQuestions();

	Info.NumberOfQuestion = NumberOfQuestions;
	enDifficultyGame Level;
	enOpType Op;

	short NumOp = ReadNumOpType();
	short NumLevel = ReadNumDifficult();

	Op = OpType(NumOp);

	short PassTime = 0, FailTime = 0;

	int Number1 = 0, Number2 = 0, UserResult = 0;

	for (int i = 0; i < NumberOfQuestions; i++)
	{
		cout << "\n\nQuestion [" << i + 1 << " / " << NumberOfQuestions << "]\n\n";

		Level = Difficulty(NumLevel);

		NumbersDependLevel(Level, Number1, Number2);

		if (Op == enOpType::MixOp)
			Op = GetMixOp();

		PrintQuestion(Number1, Number2, Op);

		int Result = Calculate(Number1, Number2, Op);

		cin >> UserResult;

		if (UserResult == Result)
		{
			ScreenColor(enPassFail::Pass);
			PassTime++;
			cout << "\nRight answer :-)\n";
		}

		else
		{
			ScreenColor(enPassFail::Fail);
			FailTime++;
			cout << "\nWrong answer :-(\n";
			cout << "The right answer is: " << Result << endl;
		}

	}
	Info.FailTimes = FailTime;
	Info.PassTimes = PassTime;

	Info.OpType = OpType(NumOp);

	Info.Difficult = Difficulty(NumLevel);

	if (PassTime > FailTime)
		Info.PassFail = enPassFail::Pass;
	else
		Info.PassFail = enPassFail::Fail;

	PrintFinalResult(Info);

	char WantReplay = WantReplayGame();
	if (WantReplay == 'y' || WantReplay == 'Y')
	{
		ClearScreen();
		PlayGame();
	}
}

int main()
{
	srand((unsigned)time(NULL));

	PlayGame();
}