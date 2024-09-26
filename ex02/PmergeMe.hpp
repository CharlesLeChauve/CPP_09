#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

class PmergeMe {
public:
    // Point d'entrée public pour trier une liste
    std::vector<int> sortVect(const std::vector<int>& input) {
        return mergeInsertionSortVector(input);
    }
	std::list<int> sortList(const std::list<int>& input) {
        return mergeInsertionSortList(input);
    }
private:
	std::vector<int> mergeInsertionSortVector(const std::vector<int>& input);
	void binaryInsertVector(std::vector<int>& sortedList, int element);
	std::list<int> mergeInsertionSortList(const std::list<int>& input);
	void binaryInsertList(std::list<int>& sortedList, int element);
};