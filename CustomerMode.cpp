#include "CustomerMode.h"
#include "Huffman.h"

void CustomerMode::run() {
	totalPrice = 0;
	loadMenu();
	string mode;

	do {
		loadMenu();
		#ifdef _WIN32
				system("cls");
		#else
				system("clear");
		#endif
		cout << "\n==================Menu==================" << endl;
		for (int i = 0; i < menuItems.size(); i++) {
			cout << i+1 << ". " << menuItems[i] << ": " << menuPrices[i] << endl;
		}
		cout << "========================================" << endl;
		cout << "Add to Order List: 1 ~ " << menuItems.size() << " (Select Item Number)" << endl;
		cout << "Show Order List: o" << endl;
		cout << "Complete Order: c" << endl;
		cout << "Exit(Cancel Order): q" << endl;
		cout << "========================================" << endl;
		cout << "Select: ";
		cin >> mode;

		if (isalpha(mode[0])) {
			switch (mode[0]) {
			case 'o': 
				editOrder(); 
				break;

			case 'c': 
				completeOrder(); 
				return;

			case 'q': 
				return;

			default: 
				cout << "Invalid mode selected (Press Enter)";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
			}
		}
		else if (isdigit(mode[0])) {
			int itemNum = stoi(mode);
			if (itemNum >= 1 && itemNum <= menuItems.size()) 
				addToOrder(itemNum);
			else {
				cout << "Invalid item number selected (Press Enter)";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin.get();
			}
		}
		else {
			cout << "Invalid mode selected (Press Enter)";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		}

	} while (true);
}

void CustomerMode::loadMenu() {
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

void CustomerMode::addToOrder(int num) {
	num--;
	orderList.add(menuItems[num]);
	totalPrice += menuPrices[num];
	cout << menuItems[num] << " added to order list." << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

void CustomerMode::deleteFromOrder(int num) {
	num--;
	Node* itemNode = orderList.locate(num);
	if (itemNode != nullptr) {
		string itemName = itemNode->data;
		auto it = find(menuItems.begin(), menuItems.end(), itemName);
		if (it != menuItems.end()) {
			int index = distance(menuItems.begin(), it);
			int itemPrice = menuPrices[index];
			removedItem.push(itemName);
			removedItemPrice.push(itemPrice);
			orderList.remove(itemName);
			totalPrice -= itemPrice;
		}
	}
	else {
		cout << "Invalid item number." << endl;
	}
}

void CustomerMode::restoreItem() {
	if (!removedItem.empty()) {
		orderList.add(removedItem.top());
		totalPrice += removedItemPrice.top();
		removedItem.pop();
		removedItemPrice.pop();
	}
}

void CustomerMode::completeOrder() {
	Huffman huff;
	huff.compressOrder(orderList);
	cout << "Order Received! (Implementing)" << endl;
}

void CustomerMode::editOrder() {
	int mode;
	do {
		#ifdef _WIN32
				system("cls");
		#else
				system("clear");
		#endif
		cout << "\n\n==============Order List==============" << endl;
		orderList.print();
		cout << "Total Price: " << totalPrice << endl;
		cout << "========================================" << endl;
		cout << "1. Delete Item" << endl;
		cout << "2. Restore Item" << endl;
		cout << "3. Exit" << endl;
		cout << "========================================" << endl;
		cout << "Select: ";
		cin >> mode;

		switch (mode)
		{
		case 1:
		{
			int item_num;
			cout << "Enter Item number: ";
			cin >> item_num;
			deleteFromOrder(item_num);
			break;
		}
		case 2:
		{
			restoreItem();
			break;
		}
		case 3:
			return;
		default:
			cout << "Invalid mode selected (Press Enter)";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		}

	} while (true);
}