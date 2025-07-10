#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<fstream>


using namespace std;


enum enMainMenuOptions { eQuickWithDraw = 1, eNormalWithDraw, eDeposite, eCheckBalance, eLogout };
enum enQuickWithdrawOptions { e20 = 1, e50, e100, e200, e400, e600, e800, e1000, eExit };


const string FileName = "C:/Users/USER/source/repos/Bank1/Bank1/Clients.txt"; 
// A txt file containing in each line (AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance)
// A delimiter between each section in txt file is: "#//#"


struct sClient
{
	string Name, AccountNumber, Phone, PinCode;
	int AccountBalance = 0;
};

sClient CurrentClient;


void Login();
void ShowMainMenueScreen();
void ShowNormalWithdrawScreen();
void ShowQuickWithdrawScreen();
void GoBackToMainMenue();


string ReadAccountNumber()
{
	string A_NO;
	cout << "Enter Account Number: ";
	cin >> A_NO;
	return A_NO;
}

string ReadPinCode()
{
	string P_Code;
	cout << "Enter Pin Code: ";
	cin >> P_Code;
	return P_Code;
}

vector<string> SplitString(string S1, string Delim)
{

	vector<string> vString;

	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}

	return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double


	return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

	vector <sClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open())
	{

		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLinetoRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();

	}

	return vClients;

}

void LoadClientsDataToFile(vector<sClient> vClients)
{
	fstream File;
	File.open(FileName, ios::out);

	if (File.is_open())
	{
		string Line = "";

		for (sClient& C : vClients)
		{
			Line = ConvertRecordToLine(C);
			File << Line << endl;
		}

		File.close();
	}
}

bool ClientExistsByAccountNumberAndPinCode(string ANumber, string PCode)
{

	vector<sClient> vClients = LoadCleintsDataFromFile(FileName);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == ANumber && C.PinCode == PCode)
		{
			CurrentClient = C;
			return true;
		}
	}

	return false;
}

void UpdateClientsDataToFile(sClient Client)
{
	vector<sClient> vClients = LoadCleintsDataFromFile(FileName);

	for (sClient& C : vClients)
	{
		if (C.AccountNumber == Client.AccountNumber)
			C.AccountBalance = Client.AccountBalance;
	}

	LoadClientsDataToFile(vClients);
}


bool IsWithdrawrAmountLessThanClientBalance(int WithdrawAmount)
{
	return (WithdrawAmount < CurrentClient.AccountBalance);
}

void QuickWithdraw(int WithdrawAmount)
{
	if (!IsWithdrawrAmountLessThanClientBalance(WithdrawAmount))
	{
		cout << "\n\nThe amount exceeds your balance, so make another choice!\n";
		cout << "\nPress any key to continue...\n";
		system("pause>0");
		ShowQuickWithdrawScreen();
	}
	else
	{
		char WantWithdraw = 'y';

		cout << "\nAre you sure do you want perform this transaction? y/n? ";
		cin >> WantWithdraw;

		if (tolower(WantWithdraw) == 'y') {
			CurrentClient.AccountBalance -= WithdrawAmount;
			cout << "\nDone Successfully. New Balance is: " << CurrentClient.AccountBalance << "\n";
		}
	}

	UpdateClientsDataToFile(CurrentClient);

}

void QuickWithdrawOption(enQuickWithdrawOptions Option)
{
	switch (Option)
	{
	case e20: QuickWithdraw(20);
		break;
	case e50: QuickWithdraw(50);
		break;
	case e100: QuickWithdraw(100);
		break;
	case e200: QuickWithdraw(200);
		break;
	case e400: QuickWithdraw(400);
		break;
	case e600: QuickWithdraw(600);
		break;
	case e800: QuickWithdraw(800);
		break;
	case e1000: QuickWithdraw(1000);
		break;
	case eExit: GoBackToMainMenue();
		break;
	}
}

int ReadQuickWithdrawOption()
{
	int Num;
	cout << "Choose what do you want withdraw form [1] to [8]? ";
	cin >> Num;
	return Num;
}

void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\t Quick Withdraw Screen\n";
	cout << "====================================\n";
	cout << "\t[1] 20\t   [2] 50\n";
	cout << "\t[3] 100\t   [4] 200\n";
	cout << "\t[5] 400\t   [6] 600\n";
	cout << "\t[7] 800\t   [8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "====================================\n";
	cout << "Your Balance is: " << CurrentClient.AccountBalance << endl;

	QuickWithdrawOption((enQuickWithdrawOptions)ReadQuickWithdrawOption());

}

bool IsMultipleOf5(int Num)
{
	return Num % 5 == 0;
}

int ReadNumberMultipleOf5()
{
	int Num;
	do
	{
		cout << "\nEnter an amount multiple of 5's: ";
		cin >> Num;
	} while (!IsMultipleOf5(Num));

	return Num;
}

void NormalWithdraw(int WithdrawAmount)
{
	if (!IsWithdrawrAmountLessThanClientBalance(WithdrawAmount))
	{
		cout << "\n\nThe amount exceeds your balance, so make another choice!\n";
		cout << "\nPress any key to continue...\n";
		system("pause>0");
		ShowNormalWithdrawScreen();
	}
	else
	{
		char WantWithdraw = 'y';

		cout << "\nAre you sure do you want perform this transaction? y/n? ";
		cin >> WantWithdraw;

		if (tolower(WantWithdraw) == 'y') {
			CurrentClient.AccountBalance -= WithdrawAmount;
			cout << "\nDone Successfully. New Balance is: " << CurrentClient.AccountBalance << "\n";
		}

	}

	UpdateClientsDataToFile(CurrentClient);
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\t Normal Withdraw Screen\n";
	cout << "====================================\n";

	NormalWithdraw(ReadNumberMultipleOf5());
}

void Deposite(int DeopsiteAmount)
{
	char WantDeposite = 'y';

	cout << "\nAre you sure do you want perform this transaction? y/n? ";
	cin >> WantDeposite;

	if (tolower(WantDeposite) == 'y') {
		CurrentClient.AccountBalance += DeopsiteAmount;
		cout << "\nDone Successfully. New Balance is: " << CurrentClient.AccountBalance << "\n";
	}

	UpdateClientsDataToFile(CurrentClient);
}

int ReadPositiveDepositeAmount()
{
	int Num;

	do
	{
		cout << "\nEnter a positive Deposite Amount: ";
		cin >> Num;
	} while (Num < 0);

	return Num;
}

void ShowDepositeScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\t Deposite Screen\n";
	cout << "====================================\n";

	Deposite(ReadPositiveDepositeAmount());

}

void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "====================================\n";
	cout << "\t Check Balance Screen\n";
	cout << "====================================\n";

	printf("Your Balance is: %d\n", CurrentClient.AccountBalance);

}

void GoBackToMainMenue()
{
	cout << "\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenueScreen();
}

void PerformMainMenueOption(enMainMenuOptions Option)
{
	switch (Option)
	{
	case eQuickWithDraw:
	{
		ShowQuickWithdrawScreen();
		GoBackToMainMenue();
	}
	break;
	case eNormalWithDraw:
	{
		ShowNormalWithdrawScreen();
		GoBackToMainMenue();
	}
	break;
	case eDeposite:
	{
		ShowDepositeScreen();
		GoBackToMainMenue();
	}
	break;
	case eCheckBalance:
	{
		ShowCheckBalanceScreen();
		GoBackToMainMenue();
	}
	break;
	case eLogout: Login();
		break;
	}
}

enMainMenuOptions ReadOption()
{
	short Num;
	cout << "Choose what do you want to do? [1 - 5]? ";
	cin >> Num;
	return enMainMenuOptions(Num);
}

void ShowMainMenueScreen()
{
	system("cls");
	cout << "========================================\n";
	cout << "\t ATM Main Menue Screen\n";
	cout << "========================================\n";
	cout << "\t [1] Quick Withdraw.\n";
	cout << "\t [2] Normal Withdraw.\n";
	cout << "\t [3] Deposite.\n";
	cout << "\t [4] Check Balance.\n";
	cout << "\t [5] Logout.\n";
	cout << "========================================\n";
	PerformMainMenueOption(ReadOption());


}

bool InvalidDetails = false;

void ShowLoginScreen()
{

	system("cls");
	cout << "-------------------------------\n";
	cout << "\t Login Screen";
	cout << "\n-------------------------------\n";

	if (InvalidDetails)
		cout << "Invalid Account Number/ Pin Code!\n";

	string A_NO = ReadAccountNumber(), P_Code = ReadPinCode();

	if (!ClientExistsByAccountNumberAndPinCode(A_NO, P_Code))
	{
		InvalidDetails = true;
		ShowLoginScreen();
	}

	InvalidDetails = false;

}

void Login()
{
	ShowLoginScreen();
	ShowMainMenueScreen();
}

int main()
{
	Login();

}