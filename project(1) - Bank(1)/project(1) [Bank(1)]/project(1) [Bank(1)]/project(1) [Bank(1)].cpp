#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


const string ClientsFileName = "Clients.txt";


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


enum enOperation
{
	enShowClientList = 1,
	enAddNewClient = 2,
	enDeletePreviousClient = 3,
	enUpdateClientInfo = 4,
	enFindClientInfo = 5,

};


vector <string> SplitString(string S1, string Delim)
{
	vector <string> vString;
	string sWord;
	short pos = 0;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}


string CounvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string sClientRecord = "";

	sClientRecord += Client.AccountNumber + Seperator;
	sClientRecord += Client.PinCode + Seperator;
	sClientRecord += Client.Name + Seperator;
	sClientRecord += Client.Phone + Seperator;
	sClientRecord += to_string(Client.AccountBalance);

	return sClientRecord;

}



sClient CounvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector <string> vClinetData;

	vClinetData = SplitString(Line, Seperator);

	Client.AccountNumber = vClinetData[0];
	Client.PinCode = vClinetData[1];
	Client.Name = vClinetData[2];
	Client.Phone = vClinetData[3];
	Client.AccountBalance = stod(vClinetData[4]); // case string to duoble

	return Client;
}


void PrintClinetRecord(sClient Client)
{
	cout << "\n\nThe following are the client Data : \n\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "PinCode : " << Client.PinCode << endl;
	cout << "Name : " << Client.Name << endl;
	cout << "Phone : " << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
}


vector <sClient> LoadClientsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;


	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = CounvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}


string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber ? ";
	cin >> AccountNumber;
	return AccountNumber;
}


void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "------------------------------------------------------\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n------------------------------------------------------\n";
}


bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}


bool IsClientInData(string AccountNumber, vector <sClient> vClients)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			return true;
		}
	}
	return false;
}


vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); //overwrite

	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				// we only write record that are not marked for delete
				DataLine = CounvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}


void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
	system("cls");
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\n\n\nPress any key to go back to Main Menue. . .";
	system("pause>0");
}


// First Operation.
void ShowMainMenueScreen()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "=================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit." << endl;
	cout << "=================================================\n";
}


short ChooseOption()
{
	short Option = -1;
	do
	{
		cout << "Choose what do you want to do? [1 to 6]? ";
		cin >> Option;
	} while (Option <= 0 || Option > 6);
	return Option;
}


void AddNewClientScreen()
{
	system("cls");
	cout << "------------------------------------------------------" << endl;
	cout << "\t\tAdd New Clients Screen" << endl;
	cout << "------------------------------------------------------\n";
	cout << "Adding New Client:\n\n";
}


void AddDataLineToFile(string FileName, string DataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}

}

sClient ReadNewClient(vector <sClient>& vClients)
{
	sClient Client;
	cout << "Enter Account Number? ";

	// Usage of std::ws will extract all the whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (IsClientInData(Client.AccountNumber, vClients) == true)
	{
		cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	vClients.push_back(Client);

	return Client;
}


void AddClient(vector <sClient>& vClients)
{
	sClient Client;
	Client = ReadNewClient(vClients);
	AddDataLineToFile(ClientsFileName, CounvertRecordToLine(Client));
}


// Second Operation
void AddClients(vector <sClient>& vClients)
{
	char AddMore = 'Y';
	do
	{
		AddNewClientScreen();
		AddClient(vClients);
		cout << "\nClient Added Successfully, do you want to add more Clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');

	cout << "\n\nPress any key to go back to Main Menue . . .";
	system("pause>0");

}


// Third Operation
void DeleteClientScreen()
{
	system("cls");
	cout << "------------------------------------------------------" << endl;
	cout << "\t\tDelete Client Screen\n";
	cout << "------------------------------------------------------" << endl;
}


void UpdateClientData(vector <sClient>& vClients, sClient Client)
{
	fstream MyFile;
	MyFile.open(ClientsFileName, ios::out | ios::trunc);

	if (MyFile.is_open())
	{
		for (sClient Record : vClients)
		{
			if ((Client.AccountNumber != Record.AccountNumber))
			{
				MyFile << CounvertRecordToLine(Record) << endl;
			}
		}
		MyFile.close();
	}

}


void DeleteClient(vector <sClient>& vClients)
{
	DeleteClientScreen();
	sClient Client;

	string AccountNumber = ReadClientAccountNumber();

	
	bool ExitLoopOrNot = false;

	while (!ExitLoopOrNot)
	{
		if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		{
			ExitLoopOrNot = true;
			cout << "The following are the client details:\n\n";
			
			PrintClientCard(Client);
			
			char DeleteClient = ' ';
			
			cout << "\n\nAre you sure you want to delete this client? Y/N ? ";
			cin >> DeleteClient;
			
			if (toupper(DeleteClient) == 'Y')
			{
				UpdateClientData(vClients, Client);
				
				vClients.clear();
				vClients = LoadClientsDataFromFile(ClientsFileName);

				cout << "\n\nClient Deleted Successfully.";
				cout << "\n\nPress any key to go back to Main Menue . . .";
				system("pause>0");

				break;
			}
			else
			{
				cout << "\n\nPress any key to go back to Main Menue . . .";
				system("pause>0");
				break;
			}
		}

		else
		{
			cout << "\nPlease enter a valid Account Number.\n";
		
			AccountNumber = ReadClientAccountNumber();
		}
	}
}


	// Fourth Operation

void UpdateClientInfoScreen()
{
	system("cls");
	cout << "------------------------------------------------------\n";
	cout << "\t\tUpdateClientInfoScreen" << endl;
	cout << "------------------------------------------------------\n";
}


sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void UpdateClientByAccountNumber( vector <sClient>& vClients)
{
	UpdateClientInfoScreen();
	
	string AccountNumber = ReadClientAccountNumber();
	sClient Client;
	
	char Answer = 'n';

	bool ExitLoopOrNot = false;
	
	while (!ExitLoopOrNot)
	{
		if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		{
			PrintClientCard(Client);

			cout << "\n\nAre you sure you want to update this client? y/n? ";
			cin >> Answer;
			
			if (Answer == 'y' || Answer == 'Y')
			{
				for (sClient& C : vClients)
				{
					if (C.AccountNumber == AccountNumber)
					{
						C = ChangeClientRecord(AccountNumber);
						break;
					}
				}

				SaveClientsDataToFile(ClientsFileName, vClients);

				cout << "\n\nClient Updated Successfully.";
				cout << "\n\nPress any key to go back to Main Menue . . .";
			
				ExitLoopOrNot = true;
				system("pause>0");
				
				return;
			}
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\nPlease Enter a valid Account Number.\n";
			AccountNumber = ReadClientAccountNumber();
		}
	}
	
}

	// Fifth Operation

void PrintClientInfoScreen()
{
	system("cls");
	cout << "------------------------------------------------------\n";
	cout << "\t\tFind Client Screen" << endl;
	cout << "------------------------------------------------------\n";
}


void FindClientInfo(vector <sClient> vClients)
{
	PrintClientInfoScreen();
	
	string AccountNumber = ReadClientAccountNumber();
	bool ExitLoopOrNot = false;
	
	sClient Client;

	while (!ExitLoopOrNot)
	{

		if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		{
			PrintClientCard(Client);
			cout << "\n\nPress any key to go back to Main Menue . . .";
			system("pause>0");
			return;
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\nPlease Enter a valid Account Number.\n";
			AccountNumber = ReadClientAccountNumber();
		}
	}

}





	// sixth operation
void ExitProgramScreen()
{
	system("cls");
	cout << "------------------------------------------------------" << endl;
	cout << "\t\tProgram Ends :-)" << endl;
	cout << "------------------------------------------------------";
	cout << "\n\nPress any key to close this window . . .";
	system("pause>0");
}


void ExitProgram()
{
	ExitProgramScreen();
	return;
}



void DoOperation(short Option, vector <sClient>& vClients)
{
	enOperation Operation;
	switch (Option)
	{
		case (enOperation::enShowClientList):   // PrintALlClientsData
		{
			PrintAllClientsData(vClients);
			break;
		}
		case (enOperation::enAddNewClient): // Add New Client
		{
			AddClients(vClients);
			break;
		}
		case (enOperation::enDeletePreviousClient): // Delete Client
		{
			DeleteClient(vClients);
			break;
		}
		case (enOperation::enUpdateClientInfo): // Update Client Info
		{
			UpdateClientByAccountNumber(vClients);
			break;
		}
		case (enOperation::enFindClientInfo): // Find Client
		{
			FindClientInfo(vClients);
			break;
		}
	}
}



void StartProgram(vector <sClient>& vClients)
{
	while (true)
	{
		ShowMainMenueScreen();
		short Option = ChooseOption();
		if (Option == 6) // Exit the program
		{
			ExitProgram();
			break;
		}
	
		DoOperation(Option, vClients);
	
	}

	return;
}


int main()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	
	StartProgram(vClients);

	return 0;
}