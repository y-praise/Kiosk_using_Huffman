#define CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ManagerMode.h"
#include "CustomerMode.h"

using namespace std;

int main() {
	int mode;
	

	do {
		cout << "\n\n========================================" << endl;
		cout << "Chose Mode" << endl;
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
			cout << "Invalid mode selected. Exiting." << endl;
		}
	} while (mode >= 1 || mode <= 3);

    return 0;
}