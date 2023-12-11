#include "utils/optimize.h"
#include "utils/crossover.h"
#include "utils/fitness.h"
#include "utils/selection.h"
#include "utils/mutation.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

void printParameters(const std::vector<std::vector<int>>& parameters) {
    std::cout << "Indivíduo da última geração com maior fitness:" << std::endl;
    for (const auto& row : parameters) {
        std::cout << "[ ";
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << "]" << std::endl;
    }
}

void printSelectedItems(const std::vector<int>& item_number, const std::vector<std::vector<int>>& parameters, const std::vector<int>& weight) {
    std::vector<std::vector<int>> selected_items;

    for (const auto& row : parameters) {
        std::vector<int> selected_row;
        for (size_t i = 0; i < row.size(); ++i) {
            selected_row.push_back(item_number[i] * row[i]);
        }
        selected_items.push_back(selected_row);
    }

    std::cout << "\nQuais itens irão na mochila:" << std::endl;
    int peso = 0;
    for (size_t i = 0; i < selected_items[0].size(); ++i) {
        if (selected_items[0][i] != 0) {
            std::cout << selected_items[0][i] << "\t";
            peso += weight[i];
        }
    }

    std::cout << "\nPeso total da mochila = " << peso << std::endl;
}

int main() {

    /* ----- Parâmetros -----*/
    int num_items = 40;
    int knapsack_capacity = 100;

    int solutions_per_pop = 16;
    int num_generations = 1000;

    std::vector<int> item_number(num_items);
    std::vector<int> weight(num_items);
    std::vector<int> value(num_items);
    
     /* ----- Inicialização -----*/
    srand(time(0));
    for (int i = 0; i < num_items; ++i) {
        item_number[i] = i + 1;
        weight[i] = rand() % 14 + 1; 
        value[i] = rand() % 99 + 1; 
    }

    std::cout << "Possíveis itens:" << std::endl;
    std::cout << "Item\tPeso\tValor" << std::endl;
    for (int i = 0; i < num_items; ++i) {
        std::cout << item_number[i] << "\t" << weight[i] << "\t" << value[i] << std::endl;
    }

    std::vector<int> pop_size = {solutions_per_pop, num_items};
    std::cout << "Tamanho da população = {" << pop_size[0] << ", " << pop_size[1] << "}" << std::endl;

    // Inicialização da população inicial
    srand(time(0));
    std::vector<std::vector<int>> initial_population(solutions_per_pop, std::vector<int>(num_items));
    for (int i = 0; i < solutions_per_pop; ++i) {
        for (int j = 0; j < num_items; ++j) {
            initial_population[i][j] = rand() % 2; // Valores aleatórios 0 ou 1
        }
    }

    std::cout << "População inicial:" << std::endl;
    for (int i = 0; i < solutions_per_pop; ++i) {
        std::cout << " ";
        for (int j = 0; j < num_items; ++j) {
            std::cout << initial_population[i][j] << " ";
        }
        std::cout << std::endl;
    }


    auto [parameters, fitness_history] = optimize(weight, value, initial_population, pop_size, num_generations, knapsack_capacity);

    printParameters(parameters);
    printSelectedItems(item_number, parameters, weight);
    
    std::cout << "\n  > Fitness_History : \n";
    for (size_t i = 0; i < fitness_history.size(); ++i) {
        std::cout << "[";
        for (size_t j = 0; j < fitness_history[i].size(); ++j) {

            if(j != fitness_history.size() - 1){
                std::cout << fitness_history[i][j]  << " , ";
            }else{
                std::cout << fitness_history[i][j];
            }

        }
        std::cout <<  "]" <<std::endl;
    }

    std::cout << "\n > Num_generations : " <<  num_generations << std::endl;

    return 0;
}