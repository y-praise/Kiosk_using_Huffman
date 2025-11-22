#pragma once
#include <string>
#include <iostream>

using namespace std;

class Node {
public:
    std::string data;
    Node* link;

    Node(const std::string& d) : data(d), link(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

    void add(const string& data);
    bool remove(const string& data);
    void print() const;
	Node* search(const string& data);
	Node* locate(int location);
    void clear();

private:
    Node* head_ptr;
};
