#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

// datafield는 menu name, frequency로 구성
// left/right child Node pointer를 가짐
// priorty_queue에서 우선순위 계산 위해 operator()를 정의함.
class HNode {
public:
	HNode() : data(""), frequency(0), left(nullptr), right(nullptr) {}
	HNode(const string& d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}

	// priority_queue에서 빈도수 비교를 위한 operator() 오버로딩 (빈도수가 낮은 HNode가 우선순위 높음)
	bool operator()(HNode* a, HNode* b) { return a->frequency > b->frequency; }

	// getter/setter
	string getData() const { return data; }
	int getFrequency() const { return frequency; }
	HNode* getLeft() const { return left; }
	HNode* getRight() const { return right; }

	void setLeft(HNode* l) { left = l; }
	void setRight(HNode* r) { right = r; }

private:
	string data;
	int frequency;
	HNode* left;
	HNode* right;

};

class Huffman {
private:
	map<string, int> frequencies;		// 메뉴 별 빈도수 저장
	priority_queue<HNode*, vector<HNode*>, HNode> pq;		// 빈도수 비교 및 tree 생성을 위한 priority queue
	map<string, string> huffmanCodes;		// 메뉴 별 압축된 코드 저장
	vector<LinkedList> orderLists;		// 주문 내역 담는 vector

public:
	void compressOrder(LinkedList orderList);	// order.txt의 첫줄(header)에서 메뉴 별 압축된 코드 파악 -> 저장할 주문을 압축된 코드로 변환해 저장
	void compressEntire();		// (order.txt 전체 다시 압축, header 재구성) pq에서 빈도수 가장 낮은 두 Node로 트리 생성 -> 두 Node pop, 새로운 Node push -> 반복
	void decompress();		// order.txt에서 첫 줄(header) 읽기(huffmanCodes에 저장) -> 한줄씩 읽으면서 복호화해 orderListHeads에 저장
	void printDecompressedOrders();		// 복호화된 주문 리스트 출력

	// compressOrder()에서 사용하는 함수
	void saveCompressedOrder();		// 주문 압축 후 order.txt에 저장

	// compressEntire()에서 사용하는 함수들
	void countFrequencies();		// 메뉴 별 빈도수 frequencies map에 저장
	void buildHuffmanTree();		// frequencies map을 기반으로 pq에 HNode 삽입
	void generateCodes();		// 재귀적으로 트리 순회하며 각 메뉴에 대한 코드 생성

	// decompress()에서 사용하는 함수들
	void loadHeader();		// order.txt의 첫 줄(header)에서 메뉴 별 압축된 코드 파악 (huffmanCodes에 저장)
	void decodeOrder();		// 압축된 주문 코드 복호화해 orderListHeads에 저장
};