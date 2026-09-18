#include <iostream>

// 杨佳明 202522550494

template <class T>
struct chainNode {
	T element;
	chainNode* next;

	chainNode(T e, chainNode* nxt) : element(e), next(nxt) {}
};

template <class T>
class chain {
protected:
	chainNode<T>*firstNode, *lastNode;

public:
	chain() : firstNode(nullptr), lastNode(nullptr) {}

	friend std::ostream& operator<<(std::ostream& os, const chain& ch) {
		for (chainNode<T>* currentNode = ch.firstNode; currentNode != NULL; currentNode = currentNode->next) {
			os << currentNode->element << " ";
		}
		os << std::endl;
		return os;
	}

	void push_back(const T& theElement) {
		chainNode<T>* newNode = new chainNode<T>(theElement, NULL);
		if (firstNode == NULL) {
			firstNode = lastNode = newNode;
		} else {
			lastNode->next = newNode;
			lastNode = newNode;
		}
	}

	void reverse() {
		lastNode = firstNode;
		chainNode<T>*prev = nullptr, *current = firstNode, *next;
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		firstNode = prev;
	}
};

int main() {
	chain<int> my_chain;
	for (int i = 1; i <= 9; i++) my_chain.push_back(i);
	std::cout << my_chain;
	my_chain.reverse();
	std::cout << my_chain;
}