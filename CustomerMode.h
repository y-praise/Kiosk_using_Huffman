#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <stack>
#include "LinkedList.h"

using namespace std;


class CustomerMode {
public:
    void run();

private:
    void loadMenu();
    void addToOrder(int num);
	void deleteFromOrder(int num);
	void restoreItem();
    void completeOrder();
	void editOrder();

	LinkedList orderList;
	stack<string> removedItem;
	stack<int> removedItemPrice;
	vector<string> menuItems;
	vector<int> menuPrices;
	int totalPrice;
};