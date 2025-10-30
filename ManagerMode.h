#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

class ManagerMode {
public:
    void run();

private:
    void editMenu();
    void checkOrderHistory();

    void loadMenu();
	void addMenuItem(const string& item, const int& price);
	void removeMenuItem(const string& item);
	void saveMenu();

	vector<string> menuItems;
	vector<int> menuPrices;
};