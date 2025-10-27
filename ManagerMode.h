#pragma once
#include <iostream>
#include <vector>

using namespace std;

class ManagerMode {
public:
	void printMenu();
	void addMenu(string new_menu);
	void deleteMenu(string del_menu);
private:
	vector<string> menu;
};