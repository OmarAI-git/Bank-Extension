#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include "MyLibrary.h";
#include "MyLibraryS.h";
#include <cctype>
#include <fstream>

using namespace std;
using namespace MyLib;

enum enprogramOption { Show_ClientList = 1, Add_NewClient = 2, Delete_Client = 3, Update_ClientInfo = 4, Find_Client = 5, Transactions = 6, Exit = 7 };
enum enTransactionOption { Deposit = 1, Withdraw = 2, Total_Balance = 3, Main_Menue = 4 };

struct strClient_Data
{
	string accountNumber = "", name = "", phone = "", pinCode = "";
	double accountBalance = 0;
	bool markDelete = false;
};

const string fileName = "Client Data.txt";
vector<strClient_Data> simply;

void BackToMenueScreen();
void StartProgram();
void TransactionsShowScreen();

vector<string> SpiltFunction(string line, string separator)
{
	vector<string> vLine;
	short pos = 0;
	string sWord = "";

	for (short i = 0; i < line.length(); i++)
	{
		pos = line.find(separator);
		sWord = line.substr(0, pos);

		if (sWord != separator)
		{
			vLine.push_back(sWord);
			line.erase(0, pos + separator.length());
		}
	}

	if (line != separator)
	{
		vLine.push_back(line);
	}

	return vLine;
}

strClient_Data ConvertLineToRecord(string line)
{
	strClient_Data cliD;
	vector<string> vLine;
	vLine = SpiltFunction(line, "#//#");

	cliD.accountNumber = vLine.at(0);
	cliD.name = vLine.at(1);
	cliD.pinCode = vLine.at(2);
	cliD.phone = vLine.at(3);
	cliD.accountBalance = stod(vLine.at(4));

	return cliD;
}

string ConvertRecordToLine(strClient_Data cLine)
{
	string line = "";

	line += cLine.accountNumber + "#//#";
	line += cLine.name + "#//#";
	line += cLine.pinCode + "#//#";
	line += cLine.phone + "#//#";
	line += to_string(cLine.accountBalance);

	return line;
}

vector<strClient_Data> LoadDataFromFile()
{
	fstream ClientData;
	vector<strClient_Data> vClientData;

	ClientData.open(::fileName, ios::in);

	if (ClientData.is_open())
	{
		string line;
		strClient_Data cliD;

		while (getline(ClientData, line))
		{
			cliD = ConvertLineToRecord(line);
			vClientData.push_back(cliD);
		}

		ClientData.close();
	}

	return vClientData;
}

void PrintClientDetails(strClient_Data cliD)
{
	cout << "| " << left << setw(15) << cliD.accountNumber;
	cout << "| " << left << setw(25) << cliD.name;
	cout << "| " << left << setw(12) << cliD.pinCode;
	cout << "| " << left << setw(14) << cliD.phone;
	cout << "| " << left << setw(12) << cliD.accountBalance;
}

void HeaderClientDetailsScreen(vector<strClient_Data> vClientData)
{
	cout << "\t\t\t\tClient List(" << vClientData.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(25) << "Name";
	cout << "| " << left << setw(12) << "PinCode";
	cout << "| " << left << setw(14) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n-------------------------------------------------------------------------------------------------------\n";

}

void PrintClientDetailsScreen(vector<strClient_Data> vClientData)
{
	HeaderClientDetailsScreen(vClientData);

	for (strClient_Data C : vClientData)
	{
		PrintClientDetails(C);
		cout << endl;
	}
	cout << "\n-------------------------------------------------------------------------------------------------------\n";

}

void PrintHeaderMainMenueScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "------------------------------------------------------\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "______________________________________________________\n";
	cout << "------------------------------------------------------\n";
}

void PrintProgramOption()
{
	cout << "\t\t[1] Show Client List." << endl;
	cout << "\t\t[2] Add New Client." << endl;
	cout << "\t\t[3] Delete Client." << endl;
	cout << "\t\t[4] Update Client Info." << endl;
	cout << "\t\t[5] Find Client." << endl;
	cout << "\t\t[6] Transaction." << endl;
	cout << "\t\t[7] Exit." << endl;
	cout << "______________________________________________________\n";
	cout << "------------------------------------------------------\n";
}

bool ClientExistByAccountNumber(strClient_Data cliD)
{
	fstream ClientData;

	ClientData.open(::fileName, ios::in);

	if (ClientData.is_open())
	{
		string line;
		strClient_Data cliF;

		while (getline(ClientData, line))
		{
			cliF = ConvertLineToRecord(line);

			if (cliD.accountNumber == cliF.accountNumber)
			{
				return true;
			}
		}

		ClientData.close();

		return false;
	}
}

void ShowScreenOption()
{
	PrintHeaderMainMenueScreen();

	PrintProgramOption();
}

void AddClientData(strClient_Data& cliD)
{
	cout << "\nEnter account number? ";
	getline(cin >> ws, cliD.accountNumber);

	while (ClientExistByAccountNumber(cliD))
	{
		cout << "\n\nClient with account number(" << cliD.accountNumber << ") already exist,Please enter another account number? ";
		getline(cin >> ws, cliD.accountNumber);
		cout << endl;
	}

	cout << "Enter name? ";
	getline(cin, cliD.name);

	cout << "Enter pinCode? ";
	getline(cin, cliD.pinCode);

	cout << "Enter phone? ";
	getline(cin, cliD.phone);

	cout << "Enter account balance? ";
	cin >> cliD.accountBalance;
}

void ChangeClientRecord(strClient_Data& cliD)
{
	cout << "\n\nEnter name? ";
	getline(cin >> ws, cliD.name);

	cout << "Enter pinCode? ";
	getline(cin, cliD.pinCode);

	cout << "Enter phone? ";
	getline(cin, cliD.phone);

	cout << "Enter account balance? ";
	cin >> cliD.accountBalance;
}

void AddNewClient(vector<strClient_Data>& vClientData)
{
	char answer = 'y';
	strClient_Data cliD;

	//cout << "Do you want to add anew client (y/n)?";
	//cin >> answer;

	while (answer == 'y' || answer == 'Y')
	{
		AddClientData(cliD);

		vClientData.push_back(cliD);

		cout << "\nAdded Successfully";

		cout << "\n\nDo you want to add another client (y/n)?";
		cin >> answer;
	}
}

void SaveNewClient(vector<strClient_Data> vClientData)
{
	fstream ClientData;

	ClientData.open(fileName, ios::out);

	if (ClientData.is_open())
	{
		string line = "";

		for (strClient_Data C : vClientData)
		{
			line = ConvertRecordToLine(C);
			ClientData << line << endl;
		}

		ClientData.close();
	}

}

void AddClient(vector<strClient_Data>& vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\tAdd New Client Screen\n";
	cout << "-------------------------------------------------\n";

	cout << "Adding New Client:\n\n";

	AddNewClient(vClientData);

	SaveNewClient(vClientData);

}

void ClientDetails(strClient_Data cliD)
{
	cout << "-------------------------------------------------\n";
	cout << "\nThe following is client details:\n\n";
	cout << "Account Number: " << cliD.accountNumber << endl;
	cout << "Name: " << cliD.name << endl;
	cout << "Phone: " << cliD.phone << endl;
	cout << "PinCode: " << cliD.pinCode << endl;
	cout << "Account Balance: " << cliD.accountBalance << endl;
	cout << "-------------------------------------------------\n";
}

bool FindClient(vector<strClient_Data>& vClientData, string account_Number)
{
	bool markFound = false;

	for (strClient_Data C : vClientData)
	{
		if (C.accountNumber == account_Number)
		{
			markFound = true;
			ClientDetails(C);
			return true;
		}
	}

	if (markFound == false)
	{
		return false;
	}
}

bool FoundClient(vector<strClient_Data>& vClientData, string account_Number)
{
	bool markFound = false;

	for (strClient_Data C : vClientData)
	{
		if (C.accountNumber == account_Number)
		{
			markFound = true;
			return true;
		}
	}

	if (markFound == false)
	{
		return false;
	}
}

void FindClientFeature(vector<strClient_Data> vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\t Find Client Screen\n";
	cout << "-------------------------------------------------\n";
	char answer = 'y';
	do {

		string account_Number = MyLibS::ReadString("Please enter the account number? ");

		if (FindClient(vClientData, account_Number))
		{
			cout << "\nDo you want to find another client (y/n)? ";
			cin >> answer;
			cout << endl << endl;
		}

		else if (!FindClient(vClientData, account_Number))
		{
			cout << "\n\nThe client with account number(" << account_Number << ") is Not Found!\n";

			cout << "\nDo you want to find another client (y/n)? ";
			cin >> answer;
			cout << endl << endl;
		}

	} while (answer == 'y' || answer == 'Y');

}

void MarkDeleteFunction(vector<strClient_Data>& vClientData, string account_Number)
{
	for (strClient_Data& Delete : vClientData)
	{
		if (Delete.accountNumber == account_Number)
		{
			Delete.markDelete = true;
		}
	}
}

void SaveClient(vector<strClient_Data>& vClientData)
{
	fstream ClientData;

	ClientData.open(fileName, ios::out);

	if (ClientData.is_open())
	{
		string line = "";

		for (strClient_Data C : vClientData)
		{
			if (C.markDelete == false)
			{
				line = ConvertRecordToLine(C);
				ClientData << line << endl;
			}
		}

		ClientData.close();
	}


}

void DeleteClient(vector<strClient_Data>& vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\tDelete Client Screen\n";
	cout << "-------------------------------------------------\n";

	char answer = 'y';

	do {

		string account_Number = MyLibS::ReadString("Please enter the account number? ");

		if (FindClient(vClientData, account_Number))
		{
			cout << "\nDo you want to delete client that has the account number(" << account_Number << ") (y/n)? ";
			cin >> answer;

			if (answer == 'y' || answer == 'Y')
			{
				MarkDeleteFunction(vClientData, account_Number);

				SaveClient(vClientData);

				cout << "\n\nDelete Client Successfully\n";

				cout << "\nDo you want to delete another client (y/n)? ";
				cin >> answer;
				cout << endl << endl;
			}
		}

		else if (!FindClient(vClientData, account_Number))
		{
			cout << "\n\nThe client with account number(" << account_Number << ") is Not Found!\n";

			cout << "\nDo you want to delete another client (y/n)? ";
			cin >> answer;
			cout << endl << endl;
		}

	} while (answer == 'y' || answer == 'Y');

	vClientData = LoadDataFromFile();

}

void UpdateClient(vector<strClient_Data>& vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\tUpdate Client Info Screen\n";
	cout << "-------------------------------------------------\n";

	char answer = 'y';

	do
	{
		string account_Number = MyLibS::ReadString("Please enter the account number? ");

		if (FindClient(vClientData, account_Number))
		{
			cout << "\n\nDo you want to update client that has the account number(" << account_Number << ") (y/n)? ";
			cin >> answer;

			if (answer == 'y' || answer == 'Y')
			{
				for (strClient_Data& C : vClientData)
				{
					if (C.accountNumber == account_Number)
					{
						ChangeClientRecord(C);
						break;
					}
				}

				cout << "\n\nUpdate Successfully";
				cout << "\n\nDo you want to update another client (y/n)? ";
				cin >> answer;
				cout << endl << endl;
			}
		}

		else if (!FindClient(vClientData, account_Number))
		{
			cout << "\n\nThe client with account number(" << account_Number << ") is Not Found!\n";

			cout << "\n\nDo you want to update another client (y/n)? ";
			cin >> answer;
		}


	} while (answer == 'y' || answer == 'Y');

	SaveClient(vClientData);

}

void EndsProgram()
{
	cout << "-------------------------------------------------\n";
	cout << "\t\t  Program Ends :-)\n";
	cout << "-------------------------------------------------\n";
}

void BackToTransactionsScreen(vector<strClient_Data>& vClientData)
{

	cout << "\n\nPress any key to go back to Transactions Menue....";

	system("pause>0");

	system("cls");

	TransactionsShowScreen();
}

void PrintTransactionsOption()
{
	cout << "\t\t[1] Deposit." << endl;
	cout << "\t\t[2] Withdraw." << endl;
	cout << "\t\t[3] Total Balance." << endl;
	cout << "\t\t[4] Main Menue." << endl;
	cout << "_________________________________________________\n";
	cout << "-------------------------------------------------\n";
}

void DepositFunction(vector<strClient_Data>& vClientData)
{

	char answer = 'y', perform = 'n';
	string account_Number;
	double amount = 0;

	do
	{
		account_Number = MyLibS::ReadString("\n\nPlease enter the account number? ");

		for (strClient_Data& C : vClientData)
		{
			if (C.accountNumber == account_Number)
			{
				ClientDetails(C);

				cout << "\nPlease enter deposit amount? ";
				cin >> amount;

				cout << "\n\nAre you sure you want perform this transaction (y,n)? ";
				cin >> perform;

				if (perform == 'y' || perform == 'Y')
				{
					C.accountBalance += amount;
					cout << "\n\nDone Successfully,New Balance = " << C.accountBalance << endl;
				}

				cout << "\nDo you want to deposit another account (y,n)? ";
				cin >> answer;
			}
		}

		if (!FoundClient(vClientData, account_Number))
		{
			cout << "\n\nClient with [" << account_Number << "] does not exist!\n";
			cout << "\nDo you want to deposit another account (y,n)? ";
			cin >> answer;
		}

	} while (answer == 'y' || answer == 'Y');

}

void DepositScreen(vector<strClient_Data>& vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\t Deposit Screen\n";
	cout << "-------------------------------------------------\n";

	DepositFunction(vClientData);

	SaveClient(vClientData);


}

void WithDrawFunction(vector<strClient_Data>& vClientData)
{
	char answer = 'y', perform = 'n';
	string account_Number;
	double amount = 0;

	do
	{
		account_Number = MyLibS::ReadString("\n\nPlease enter the account number? ");

		for (strClient_Data& C : vClientData)
		{
			if (C.accountNumber == account_Number)
			{
				ClientDetails(C);

				cout << "\nPlease enter Withdraw amount? ";
				cin >> amount;

				while (amount > C.accountBalance)
				{
					cout << "\n\nAmount Exceeds balance, you can withdraw up to : " << C.accountBalance << endl;

					cout << "\nPlease enter another Withdraw amount? ";
					cin >> amount;
				}

				cout << "\n\nAre you sure you want perform this transaction (y,n)? ";
				cin >> perform;

				if (perform == 'y' || perform == 'Y')
				{
					C.accountBalance -= amount;
					cout << "\n\nDone Successfully,New Balance = " << C.accountBalance << endl;
				}

				cout << "\nDo you want to withdraw another account (y,n)? ";
				cin >> answer;
			}
		}

		if (!FoundClient(vClientData, account_Number))
		{
			cout << "\n\nClient with [" << account_Number << "] does not exist!\n";
			cout << "\nDo you want to withdraw another account (y,n)? ";
			cin >> answer;
		}

	} while (answer == 'y' || answer == 'Y');


}

void WithdrawScreen(vector<strClient_Data>& vClientData)
{
	cout << "-------------------------------------------------\n";
	cout << "\t\t Withdraw Screen\n";
	cout << "-------------------------------------------------\n";

	WithDrawFunction(vClientData);

	SaveClient(vClientData);

}

void TotalBalanceScreen(vector<strClient_Data>& vClientData)
{
	double total = 0;

	cout << "\n\t\t\t\tBalances List(" << vClientData.size() << ") Client(s)" << endl;
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(25) << "Name";
	cout << "| " << left << setw(18) << "Account Balance";
	cout << "\n-------------------------------------------------------------------------------------------------------\n";

	if (vClientData.size() == 0)
	{
		cout << "\t\t\tNo Clients Available In the System!\n";
	}

	else
	{
		for (strClient_Data& cliD : vClientData)
		{
			cout << "| " << left << setw(15) << cliD.accountNumber;
			cout << "| " << left << setw(25) << cliD.name;
			cout << "| " << left << setw(18) << cliD.accountBalance;
			total += cliD.accountBalance;
			cout << endl;
		}

		cout << "\n-------------------------------------------------------------------------------------------------------\n";

		cout << "\n\t\t\tTotal Balances = " << total << endl;
	}
}

void RunTransactionOption(enTransactionOption trsop, vector<strClient_Data>& vClientData)
{
	switch (trsop)
	{

	case enTransactionOption::Deposit:
	{
		system("cls");
		DepositScreen(vClientData);
		BackToTransactionsScreen(vClientData);
	}
	case enTransactionOption::Withdraw:
	{
		system("cls");
		WithdrawScreen(vClientData);
		BackToTransactionsScreen(vClientData);
	}
	case enTransactionOption::Total_Balance:
	{
		system("cls");
		TotalBalanceScreen(vClientData);
		BackToTransactionsScreen(vClientData);
	}
	case enTransactionOption::Main_Menue:
	{
		StartProgram();
	}

	}
}

void TransactionsShowScreen()
{
	vector<strClient_Data> vClientData = LoadDataFromFile();

	cout << "\n_________________________________________________\n";
	cout << "-------------------------------------------------\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "_________________________________________________\n";
	cout << "-------------------------------------------------\n";

	PrintTransactionsOption();

	short choose;

	cout << "\nChoose what do you want to do [1 to 4] ? ";
	cin >> choose;

	RunTransactionOption((enTransactionOption)choose, vClientData);

}

void RunOption(enprogramOption choose, vector<strClient_Data>& vClientData)
{
	switch (choose)
	{
	case ::Show_ClientList:
	{
		system("cls");
		PrintClientDetailsScreen(vClientData);
		BackToMenueScreen();
		break;
	}
	case::Add_NewClient:
	{
		system("cls");
		AddClient(vClientData);
		BackToMenueScreen();
		break;
	}
	case::Delete_Client:
	{
		system("cls");
		DeleteClient(vClientData);
		BackToMenueScreen();
		break;
	}
	case::Update_ClientInfo:
	{
		system("cls");
		UpdateClient(vClientData);
		BackToMenueScreen();
		break;
	}
	case::Find_Client:
	{
		system("cls");
		FindClientFeature(vClientData);
		BackToMenueScreen();
		break;
	}
	case ::Transactions:
	{
		system("cls");
		TransactionsShowScreen();
		BackToMenueScreen();
		break;
	}
	case::Exit:
	{
		system("cls");
		EndsProgram();
		break;
	}

	}
}

void BackToMenueScreen()
{
	cout << "\n\nPress any key to go back to Main Menue....";

	system("pause>0");

	StartProgram();
}

void StartProgram()
{
	vector<strClient_Data> vClientData = LoadDataFromFile();
	short choose = 0;

	system("cls");
	ShowScreenOption();
	cout << "\nChoose what do you want to do? [1 to 7]? ";
	cin >> choose;

	RunOption((enprogramOption)choose, vClientData);
}

int main()
{
	StartProgram();

	system("pause>0");
}