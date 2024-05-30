//
// Created by 刘鑫 on 2024/5/29.
//

#include "commons.h"
#include <random>

template<typename T>
vector<T> random_matrix(int capital, int start_include, int stop_exclude) {
    vector<T> result = new vector<T>(capital);
    default_random_engine generator;
    uniform_real_distribution<T> distribution(start_include, stop_exclude);
    auto dice = std::bind(distribution, generator);
    for (int i = 0; i < capital; i++) {
        result.push_back(dice());
    }
    return result;
}