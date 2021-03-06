// Lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "FileProvider.h"



DWORD getMessage(TCHAR * message) {
	TCHAR k;
	_tscanf(_T("%c"), &k);
	int i = 0;
	for (i = 0; message[i] != (TCHAR)'\n' || message[i] != '\r'; i++) {
		_tscanf(_T("%c"), &message[i]);
		if (message[i] == (TCHAR)'\n') {
			message[i] = '\0';
			break;
		}
	}
	return (DWORD)i;
}

void printCommands() {
	_tprintf(_T("menu>\n"));
	_tprintf(_T("1 - Write keys\n"));
	_tprintf(_T("2 - Write text\n"));
	_tprintf(_T("3 - Read keys\n"));
	_tprintf(_T("4 - Read text\n"));
	_tprintf(_T("5 - Read logs\n"));
	_tprintf(_T("6 - Search keys in text\n"));
	_tprintf(_T("q - Quit\n"));
	_tprintf(_T("menu> Enter a command: "));
}

void runMenu(FileProvider * fileProvider) 
{
	TCHAR message[200];
	char command = '\0';
	printCommands();
	std::cin >> command;
	while (command != 'r' || command != 'q') 
	{
		//Add keys
		if (command == '1') {
			_tprintf(_T("keys adding> Enter your key: "));
			DWORD size = getMessage(&message[0]);
			fileProvider->WriteKeys(&message[0], size);
			_tprintf(_T("keys adding> The key is added.\n\n"));
		}
		//Add text
		else if (command == '2') {
			_tprintf(_T("text adding> Enter your text: "));
			DWORD size = getMessage(&message[0]);
			fileProvider->WriteText(&message[0], size);
			_tprintf(_T("keys adding> The text is added.\n\n"));
		}
		//Read keys
		else if (command == '3') {
			_tprintf(_T("keys reading> \n"));
			fileProvider->ReadKeys();
			_tprintf(_T("\n"));
		}
		// Read text
		else if (command == '4') {
			_tprintf(_T("text reading> \n"));
			fileProvider->ReadText();
			_tprintf(_T("\n"));
		}
		//Read logs
		else if (command == '5') {
			_tprintf(_T("log reading> \n"));
			fileProvider->ReadLogs();
			_tprintf(_T("\n"));
		}
		//find data
		else if (command == '6') {
			_tprintf(_T("keys in text observing> "));
			fileProvider->SearchData();
			_tprintf(_T("The results are in log file.\n\n"));
		}
		else if (command == 'q') {
			return;
		}
		_tprintf(_T("menu> Enter a command: "));
		std::cin >> command;
	}
}

int main()
{
	auto p = new FileProvider();
	runMenu(p);
	return 0;
}