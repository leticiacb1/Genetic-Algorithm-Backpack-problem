#include "crossover.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> crossover(const std::vector<std::vector<int>>& parents, int num_offsprings) {
    std::vector<std::vector<int>> offsprings(num_offsprings, std::vector<int>(parents[0].size()));
    int crossover_point = parents[0].size() / 2;
    double crossover_rate = 0.8;
    int i = 0;
    int cnt_offsprings = 0;

    while (cnt_offsprings < num_offsprings) {
        int parent1_index = i % parents.size();
        int parent2_index = (i + 1) % parents.size();
        double x = (double)rand() / RAND_MAX;

        if (x > crossover_rate) {
            // Não ocorre crossover
        } else {
            // Realiza crossover
            for (int j = 0; j < crossover_point; ++j) {
                offsprings[cnt_offsprings][j] = parents[parent1_index][j];
            }

            for (size_t j = crossover_point; j < parents[0].size(); ++j) {
                offsprings[cnt_offsprings][j] = parents[parent2_index][j];
            }
            cnt_offsprings++;
        }

        i++;
    }

    return offsprings;
}