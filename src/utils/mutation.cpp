#include "mutation.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> mutation(const std::vector<std::vector<int>>& offsprings) {
    std::vector<std::vector<int>> mutants(offsprings.size(), std::vector<int>(offsprings[0].size()));
    double mutation_rate = 0.15;

    for (size_t i = 0; i < mutants.size(); ++i) {
        double random_value = static_cast<double>(rand()) / RAND_MAX;
        mutants[i] = offsprings[i];

        if (random_value > mutation_rate) {
            continue;
        }

        int int_random_value = rand() % offsprings[0].size();
        if (mutants[i][int_random_value] == 0) {
            mutants[i][int_random_value] = 1;
        } else {
            mutants[i][int_random_value] = 0;
        }
    }

    return mutants;
}