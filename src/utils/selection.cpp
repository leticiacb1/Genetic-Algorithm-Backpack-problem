#include "selection.h"

#include <algorithm>
#include <vector>

std::vector<std::vector<int>> selection(const std::vector<int>& fitness, int num_parents, const std::vector<std::vector<int>>& population) {
    std::vector<int> fitness_copy = fitness;  // Cópia para não modificar o original
    std::vector<std::vector<int>> parents(num_parents, std::vector<int>(population[0].size()));

    for (int i = 0; i < num_parents; ++i) {
        auto max_fitness_it = std::max_element(fitness_copy.begin(), fitness_copy.end());
        int max_fitness_idx = std::distance(fitness_copy.begin(), max_fitness_it);

        for (size_t j = 0; j < population[max_fitness_idx].size(); ++j) {
            parents[i][j] = population[max_fitness_idx][j];
        }

        fitness_copy[max_fitness_idx] = -9999;
    }

    return parents;
}
