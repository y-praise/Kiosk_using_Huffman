#include "ManagerMode.h"
#include <iostream>

using namespace std;

void ManagerMode::run() {
	int mode;
	do {
		cout << "\n========================================" << endl;
		cout << "Chose One" << endl;
		cout << "1. Order History" << endl;
		cout << "2. Edit Menu" << endl;
		cout << "3. Exit" << endl;
		cout << "========================================" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch (mode)
		{
		case 1:

		case 2:
			editMenu();
			break;
		case 3:
			return;
		default:
			cout << "Invalid mode selected. Exiting." << endl;
		}
	} while (mode < 1 || mode > 3);
}

void ManagerMode::checkOrderHistory() {

}


void ManagerMode::editMenu() {
	int mode;
	do {
		loadMenu();
		cout << "\n\n==================Menu==================" << endl;
		for (int i = 0; i < menuItems.size(); i++) {
			cout << menuItems[i] << ": " << menuPrices[i] << endl;
		}
		cout << "========================================" << endl;
		cout << "Chose One" << endl;
		cout << "1. Add Item" << endl;
		cout << "2. Delete Item" << endl;
		cout << "3. Exit" << endl;
		cout << "========================================" << endl;
		cout << "Select Mode: ";
		cin >> mode;

		switch (mode)
		{
		case 1:
		{
			string newItem;
			int newPrice;
			cout << "Enter new item name(No blank!): ";
			cin >> newItem;
			cout << "Enter new item price: ";
			cin >> newPrice;
			addMenuItem(newItem, newPrice);
			break;
		}
		case 2:
		{
			string delItem;
			cout << "Enter item name to delete: ";
			cin >> delItem;
			removeMenuItem(delItem);
			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid mode selected. Exiting." << endl;
		}
	} while (mode >= 1 || mode <= 3);
}

void ManagerMode::loadMenu() {
	ifstream menuFile;
	menuFile.open("menu.txt");

	menuItems.clear();
	menuPrices.clear();

	if (menuFile.is_open()) {
		string line;

		while (getline(menuFile, line)) {
			istringstream iss(line);
			string word;
			int price;

			while (iss >> word >> price) {
				menuItems.push_back(word);
				menuPrices.push_back(price);
			}
		}
		menuFile.close();
	}
	else
		cout << "Unable to open file" << endl;
	
}

void ManagerMode::addMenuItem(const string& item, const int& price) {
	menuItems.push_back(item);
	menuPrices.push_back(price);
	saveMenu();
}

void ManagerMode::removeMenuItem(const string& item) {
	for (int i = 0; i < menuItems.size(); i++) {
		if(menuItems[i] == item) {
			menuItems.erase(menuItems.begin() + i);
			menuPrices.erase(menuPrices.begin() + i);
		}
	}
	saveMenu();
}

void ManagerMode::saveMenu() {
	ofstream menuFile;
	menuFile.open("menu.txt");
	if (menuFile.is_open()) {
		for (int i = 0; i < menuItems.size(); i++) {
			menuFile << menuItems[i] << " " << menuPrices[i] << endl;
		}
		menuFile.close();
	}
	else
		cout << "Unable to open file" << endl;
}