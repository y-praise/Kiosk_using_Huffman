#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head_ptr = nullptr;
}

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList& other) {
    this->head_ptr = nullptr;

    Node* current_other = other.head_ptr;
    while (current_other != nullptr) {
        this->add(current_other->data);
        current_other = current_other->link;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this == &other)
        return *this;

    while (this->head_ptr != nullptr)
        clear();

    Node* current_other = other.head_ptr;
    while (current_other != nullptr) {
        this->add(current_other->data);
        current_other = current_other->link;
    }

    return *this;
}

void LinkedList::add(const string& data) {
    Node* newNode = new Node(data);
    if (!head_ptr) {
        head_ptr = newNode;
    }
    else {
        Node* temp = head_ptr;
        while (temp->link) {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}

bool LinkedList::remove(const string& data) {
    Node* temp = head_ptr;
    Node* prev = nullptr;
    while (temp) {
        if (temp->data == data) {
            if (prev) {
                prev->link = temp->link;
            }
            else {
                head_ptr = temp->link;
            }
            delete temp;
            return true;
        }
        prev = temp;
        temp = temp->link;
    }
    return false;
}

void LinkedList::print() const {
    Node* temp = head_ptr;
    int i = 1;
    while (temp != NULL) {
        cout << i << ". " << temp->data << endl;
        temp = temp->link;
		i++;
    }
}

Node* LinkedList::search(const string& data) {
    Node* temp = head_ptr;
    while (temp) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->link;
    }
    return nullptr;
}

Node* LinkedList::locate(int location) {
	Node* temp = head_ptr;
	int index = 0;
	while (temp) {
		if (index == location) {
			return temp;
		}
		temp = temp->link;
		index++;
	}
	return nullptr;
}

void LinkedList::clear() {
    Node* temp = head_ptr;
    while (temp) {
        Node* next = temp->link;
        delete temp;
        temp = next;
    }
    head_ptr = nullptr;
}
