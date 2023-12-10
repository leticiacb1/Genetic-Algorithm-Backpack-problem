#pragma once

#include <vector>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> optimize(const std::vector<int>& weight,
                                                                                  const std::vector<int>& value,
                                                                                  std::vector<std::vector<int>>& population,
                                                                                  const std::vector<int>& pop_size,
                                                                                  int num_generations,
                                                                                  int capacity);