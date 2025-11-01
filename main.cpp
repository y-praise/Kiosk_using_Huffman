#define CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ManagerMode.h"
#include "CustomerMode.h"
using namespace std;

void clear_screen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main() {
	int mode;

	do {
		clear_screen();
		cout << "\n========================================" << endl;
		cout << "Choose Mode" << endl;
		cout << "1. Customer Mode" << endl;
		cout << "2. Manager Mode" << endl;
		cout << "3. Exit" << endl;
		cout << "========================================" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch (mode)
		{
		case 1:
		{
			CustomerMode customer;
			customer.run();
			break;
		}

		case 2:
		{
			ManagerMode manager;
			manager.run();
			break;
		}

		case 3:
			return 0;

		default:
			cout << "Invalid mode selected (Press Enter)"; 
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
			cin.get();
		}
	} while (true);

    return 0;
}