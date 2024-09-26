#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sys/time.h>

#include "PmergeMe.hpp"

long getMicroseconds(struct timeval start, struct timeval end);

int main(int ac, char **av) {
	std::list<int> list;
	std::vector<int> vect;

	if (ac < 2) {
		std::cerr << "Usage : ./PmergeMe <int1> <int2> ... <intN>" << std::endl;
		return 1;
	}
	for (int i = 1; i < ac; ++i) {
        char* end;
        long val = std::strtol(av[i], &end, 10);
        
        if (*end == '\0' && (val >= 0 && val <= INT_MAX)) {
            vect.push_back(static_cast<int>(val));
			list.push_back(static_cast<int>(val));
		}
        else
            std::cerr << "Tous les arguments doivent etre des entiers positifs valides" << std::endl;
    }

	PmergeMe sorter;

	struct timeval listStart, listEnd, vectStart, vectEnd;

    // Mesure du temps pour la liste
    gettimeofday(&listStart, NULL);
    std::list<int> sortedList = sorter.sortList(list);
    gettimeofday(&listEnd, NULL);
    long listTime = getMicroseconds(listStart, listEnd);

    // Mesure du temps pour le vecteur
    gettimeofday(&vectStart, NULL);
    std::vector<int> sortedVect = sorter.sortVect(vect);
    gettimeofday(&vectEnd, NULL);
    long vectTime = getMicroseconds(vectStart, vectEnd);
	std::cout << "Before : ";
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << "After : ";
	for (std::vector<int>::iterator it = sortedVect.begin(); it != sortedVect.end(); ++it) {
		std::cout << *it << " ";
	}
    std::cout << std::endl << "Time to process a range of " << ac - 1 << " elements with std::list : " << listTime << " usec" << std::endl;
    std::cout << std::endl << "Time to process a range of " << ac - 1 << " elements with std::vector : " << vectTime << " usec" << std::endl;
    return 0;
}

long getMicroseconds(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}
