#include <iostream>
#include <vector>
// 25级软工6班 杨佳明 202522550494
template <class T>
void printSubset(const std::vector<T>& a, std::vector<T>& cur, int pos) {
	if (pos == a.size()) {
		std::cout << "{";
		for (int i = 0; i < cur.size(); i++) {
			if (i) std::cout << ", ";
			std::cout << cur[i];
		}
		std::cout << "}\n";
		return;
	}
	printSubset(a, cur, pos + 1);
	cur.push_back(a[pos]);
	printSubset(a, cur, pos + 1);
	cur.pop_back();
}

template <class T>
void printAllSubsets(const std::vector<T>& a) {
	std::vector<T> cur;
	printSubset(a, cur, 0);
}

int main() {
	std::vector<char> a = {'a', 'b', 'c'};
	printAllSubsets(a);
	return 0;
}