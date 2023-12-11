#include "../utils/optimize.h"
#include "../utils/crossover.h"
#include "../utils/fitness.h"
#include "../utils/selection.h"
#include "../utils/mutation.h"

#include <vector>
#include <iostream>
#include <algorithm>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> optimize(const std::vector<int>& weight,
                                                                                  const std::vector<int>& value,
                                                                                  std::vector<std::vector<int>>& population,
                                                                                  const std::vector<int>& pop_size,
                                                                                  int num_generations,
                                                                                  int capacity) {
    std::vector<std::vector<int>> parameters;
    std::vector<std::vector<int>> fitness_history;

    int num_parents = pop_size[0] / 2;
    int num_offsprings = pop_size[0] - num_parents;

    for (int i = 0; i < num_generations; ++i) {
        std::vector<int> fitness_ = fitness(weight, value, population, capacity);
        fitness_history.push_back(fitness_);

        std::vector<std::vector<int>> parents = selection(fitness_, num_parents, population);
        std::vector<std::vector<int>> offsprings = crossover(parents, num_offsprings);
        std::vector<std::vector<int>> mutants = mutation(offsprings);

        // Substituição dos indivíduos menos aptos pelos pais e mutantes
        std::copy(parents.begin(), parents.end(), population.begin());
        std::copy(mutants.begin(), mutants.end(), population.begin() + parents.size());
    }

    // Impressão da última geração
    std::cout << "Última geração:" << std::endl;
    for (size_t i = 0; i < population.size(); ++i) {
        std::cout << "Indivíduo[" << i << "]: ";
        for (size_t j = 0; j < population[i].size(); ++j) {
            std::cout << population[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> fitness_last_gen = fitness(weight, value, population, capacity);

    // Impressão do fitness da última geração
    std::cout << "Fitness da última geração:" << std::endl;
    for (size_t i = 0; i < fitness_last_gen.size(); ++i) {
        std::cout << "Fitness[" << i << "] = " << fitness_last_gen[i] << std::endl;
    }

    // Identificação do melhor indivíduo
    auto max_fitness_it = std::max_element(fitness_last_gen.begin(), fitness_last_gen.end());
    int max_fitness_idx = std::distance(fitness_last_gen.begin(), max_fitness_it);
    parameters.push_back(population[max_fitness_idx]);

    return std::make_pair(parameters, fitness_history);
}