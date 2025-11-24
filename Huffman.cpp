#include "Huffman.h"

// order.txt의 헤더를 기준으로 주문 압축 후 저장
void Huffman::compressOrder(LinkedList orderList) {
	decompress();	
	orderLists.push_back(orderList);
	saveCompressedOrder();
}

// 메뉴별 빈도수 다시 계산해 헤더 다시 만들고 전체 다시 압축 후 저장
void Huffman::compressEntire() {
	decompress();
	countFrequencies();
	buildHuffmanTree();
	generateCodes();
	saveCompressedOrder();
}

// order.txt에 저장된 주문 내역 불러오기
void Huffman::decompress() {
	loadHeader();
	decodeOrder();
}

// orderLists에 있는 모든 주문 내역 출력
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

// order.txt의 헤더(첫번째 줄) 읽어와 huffmanCodes에 저장
void Huffman::loadHeader() {
	ifstream menuFile;
	menuFile.open("order.txt");

	if (menuFile.is_open()) {
		string line;

		getline(menuFile, line);
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

// order.txt에 헤더와 주문 내역 저장
void Huffman::saveCompressedOrder() {
	ofstream orderFile;
	orderFile.open("order.txt");
	if (orderFile.is_open()) {

		// 헤더 저장
		for (const auto& pair : huffmanCodes) {
			orderFile << pair.first << " " << pair.second << " ";
		}
		orderFile << endl;

		// 주문 별 압축된 코드를 order.txt에 저장
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

// orderLists에서 메뉴별 주문 빈도수 계산
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

	// menu.txt에서 새로 추가된 메뉴 추가 (빈도수 0으로 저장)
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

// pq에서 Huffman Tree 생성
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

// Huffman Tree 순회하면서 각 메뉴 별 코드 생성
void Huffman::generateCodes() {
	huffmanCodes.clear();
	if (pq.empty()) return;
	HNode* root = pq.top();
	
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

// 압축된 주문 코드 복호화해 orderLists에 저장
void Huffman::decodeOrder() {
	orderLists.clear();
	ifstream orderFile;
	orderFile.open("order.txt");
	if (orderFile.is_open()) {
		string line;

		// huffmanCodes에 있는 (코드, 메뉴)를 codeToMenu에 (메뉴, 코드)로 저장 -> 코드로 메뉴 검색 가능하게 함
		map<string, string> codeToMenu;
		for (const auto& pair : huffmanCodes)
			codeToMenu[pair.second] = pair.first;

		getline(orderFile, line);
		while (getline(orderFile, line)) {
			LinkedList orderList;
			string currentCode = "";
			// 한 줄의 한 글자씩 읽어 currentCode에 추가
			for (char ch : line) {
				currentCode += ch;
				// currentCode가 codeToMenu에 있으면 orderList에 추가
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