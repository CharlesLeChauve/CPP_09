#include "PmergeMe.hpp"

void PmergeMe::binaryInsertVector(std::vector<int>& sortedList, int element) {
    std::vector<int>::iterator it = std::lower_bound(sortedList.begin(), sortedList.end(), element);
    sortedList.insert(it, element);
}

// Fonction principale de tri par fusion-insertion
std::vector<int> PmergeMe::mergeInsertionSortVector(const std::vector<int>& input) {
    if (input.size() <= 1) {
        return input;
    }
    // Étape 1 : Regrouper les éléments en paires
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> remainingElements;

    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        pairs.emplace_back(input[i], input[i + 1]);
    }

    // Si le nombre d'éléments est impair, ajouter l'élément non apparié
    if (input.size() % 2 != 0) {
        remainingElements.push_back(input.back());
    }

    // Étape 2 : Déterminer le maximum de chaque paire
    std::vector<int> maxima;
    std::vector<int> minima;

	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
	{
		if ((*it).first >= (*it).second) {
            maxima.push_back((*it).first);
            minima.push_back((*it).second);
        } else {
            maxima.push_back((*it).second);
            minima.push_back((*it).first);
        }
	}

	for(std::vector<int>::iterator it = remainingElements.begin(); it != remainingElements.end(); ++it)
	{
        minima.push_back(*it);
	}

    // Étape 3 : Trier récursivement les maxima
    std::vector<int> sortedMaxima = mergeInsertionSortVector(maxima);

    // Étape 4 : Insérer les éléments restants dans la liste triée des maxima
	for (std::vector<int>::iterator it = minima.begin(); it != minima.end(); ++it)
	{
        binaryInsertVector(sortedMaxima, *it);
	}

    return sortedMaxima;
}

void PmergeMe::binaryInsertList(std::list<int>& sortedList, int element) {
    std::list<int>::iterator it = std::lower_bound(sortedList.begin(), sortedList.end(), element);
    sortedList.insert(it, element);
}

// Fonction principale de tri par fusion-insertion
std::list<int> PmergeMe::mergeInsertionSortList(const std::list<int>& input) {
        // Cas de base : une liste vide ou avec un seul élément est déjà triée
	if (input.size() <= 1) {
		return input;
	}

	// Déclaration locale des conteneurs maxima et minima
	std::list<int> maxima;
	std::list<int> minima;

	// Regroupement des éléments en paires
	std::list<int>::const_iterator it = input.begin();
	while (it != input.end()) {
		int first = *it;
		++it;
		if (it != input.end()) {
			int second = *it;
			if (first >= second) {
				maxima.push_back(first);
				minima.push_back(second);
			} else {
				maxima.push_back(second);
				minima.push_back(first);
			}
			++it;
		} else {
			// Nombre impair, ajouter l'élément non apparié aux minima
			minima.push_back(first);
		}
	}

	// Tri récursif des maxima
	std::list<int> sortedMaxima = mergeInsertionSortList(maxima);

	// Insertion des minima dans la liste triée des maxima
	std::list<int>::const_iterator minIt = minima.begin();
	while (minIt != minima.end()) {
		binaryInsertList(sortedMaxima, *minIt);
		++minIt;
	}

	return sortedMaxima;
}
