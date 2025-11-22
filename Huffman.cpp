#include "Huffman.h"

void Huffman::compressOrder(LinkedList orderList) {
	decompress();
	orderLists.push_back(orderList);
	saveCompressedOrder();
}

void Huffman::compressEntire() {
	decompress();
	countFrequencies();
	buildHuffmanTree();
	saveCompressedOrder();
}

void Huffman::decompress() {
	loadHeader();
	decodeOrder();
}

void Huffman::printDecompressedOrders() {
	for (int i = 0; i < orderLists.size(); i++) {
		cout << "Order " << i + 1 << ": ";
		Node* current = orderLists[i].locate(0);
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->link;
		}
		cout << endl;
	}
}

void Huffman::loadHeader() {
	ifstream menuFile;
	menuFile.open("order.txt");

	if (menuFile.is_open()) {
		string line;

		getline(menuFile, line); // 첫 줄(header)만 읽고 나머지는 무시
		istringstream iss(line);
		string menu;
		string code;
		while (iss >> menu >> code) {
			huffmanCodes.insert({ menu, code });
		}
		menuFile.close();
	}
	else
		cout << "Unable to open file" << endl;
}

void Huffman::saveCompressedOrder() {
	ofstream orderFile;
	orderFile.open("order.txt");
	if (orderFile.is_open()) {

		// Save header
		for (const auto& pair : huffmanCodes) {
			orderFile << pair.first << " " << pair.second << " ";
		}
		orderFile << endl;

		// Save compressed orders
		for (auto& head : orderLists) {
			Node* current = head.locate(0);
			while (current != nullptr) {
				string item = current->data;
				orderFile << huffmanCodes[item];
				current = current->link;
			}
			orderFile << endl;
		}
		orderFile.close();
	}
	else
		cout << "Unable to open file" << endl;
}

void Huffman::countFrequencies() {
	frequencies.clear();

	// 기존 주문내역에서 빈도수 계산
	for (auto& head : orderLists) {
		Node* current = head.locate(0);
		while (current != nullptr) {
			frequencies[current->data]++;
			current = current->link;
		}
	}

	// menu.txt에서 새로 추가된 메뉴 추가
	ifstream menuFile;
	menuFile.open("menu.txt");
	if (menuFile.is_open()) {
		string line;
		while (getline(menuFile, line)) {
			istringstream iss(line);
			string word;
			int price;
			while (iss >> word >> price) {
				if (frequencies.find(word) == frequencies.end())
					frequencies[word] = 0;
			}
		}
		menuFile.close();
	}
	else
		cout << "Unable to open file" << endl;

}

void Huffman::buildHuffmanTree() {
	// frequencies map을 기반으로 pq에 HNode 삽입
	while (!pq.empty()) pq.pop();
	for (const auto& pair : frequencies) {
		HNode* newNode = new HNode(pair.first, pair.second);
		pq.push(newNode);
	}

	// pq에서 두 개의 노드를 꺼내 새로운 노드를 만들어 다시 삽입하는 과정 반복
	while (pq.size() > 1) {
		HNode* left = pq.top(); pq.pop();
		HNode* right = pq.top(); pq.pop();
		HNode* merged = new HNode("", left->getFrequency() + right->getFrequency());
		merged->setLeft(left);
		merged->setRight(right);
		pq.push(merged);
	}
}

void Huffman::generateCodes() {
	huffmanCodes.clear();
	if (pq.empty()) return;
	HNode* root = pq.top();
	// Huffman Tree를 순회하며 각 메뉴에 대한 코드 생성
	string code = "";
	stack<pair<HNode*, string>> st;
	st.push({ root, code });

	while (!st.empty()) {
		HNode* node = st.top().first;
		string currentCode = st.top().second;
		st.pop();

		// 리프 노드인 경우 코드 저장
		if (node->getLeft() == nullptr && node->getRight() == nullptr) {
			huffmanCodes[node->getData()] = currentCode;
		}
		// 오른쪽 자식 노드 방문
		if (node->getRight() != nullptr) {
			st.push({ node->getRight(), currentCode + "1" });
		}
		// 왼쪽 자식 노드 방문
		if (node->getLeft() != nullptr) {
			st.push({ node->getLeft(), currentCode + "0" });
		}
	}
}

void Huffman::decodeOrder() {
	// 압축된 주문 코드 복호화해 orderLists에 저장
	orderLists.clear();
	ifstream orderFile;
	orderFile.open("order.txt");
	if (orderFile.is_open()) {
		string line;

		map<string, string> codeToMenu;
		for (const auto& pair : huffmanCodes)
			codeToMenu[pair.second] = pair.first;

		// 첫 줄(header) 건너뛰기
		getline(orderFile, line);
		while (getline(orderFile, line)) {
			LinkedList orderList;
			string currentCode = "";
			for (char ch : line) {
				currentCode += ch;
				if (codeToMenu.count(currentCode)) {
					orderList.add(codeToMenu[currentCode]);
					currentCode = "";
				}
			}
			orderLists.push_back(orderList);
		}
		orderFile.close();
	}
	else
		cout << "Unable to open file" << endl;
}