#pragma once
#include <iostream>

using namespace std;

class Node {
	string data;
	Node* link;
};

class LinkedList {
public:
	LinkedList() { head_ptr = new Node(); }

private:
	Node* head_ptr;
};

class CustomerMode {
public:
	CustomerMode();
	void printMenu();
	void addOrder(string add_item);
	void deleteOrder();

private:
	LinkedList order;
};