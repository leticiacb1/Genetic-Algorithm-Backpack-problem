#include "fitness.h"
#include <iostream>
#include <vector>
#include <numeric>

std::vector<int> fitness(const std::vector<int>& weight, const std::vector<int>& value, const std::vector<std::vector<int>>& population, int capacity) {
    std::vector<int> fitness_values(population.size());

    for (size_t i = 0; i < fitness_values.size(); ++i) {
        int S1 = 0;
        int S2 = 0;

        for (size_t j = 0; j < population[i].size(); ++j) {
            S1 += population[i][j] * value[j];
            S2 += population[i][j] * weight[j];
        }

        if (S2 <= capacity) {
            fitness_values[i] = S1;
        } else {
            fitness_values[i] = 0;
        }
    }

    return fitness_values;
}