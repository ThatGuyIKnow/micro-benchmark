#include "tree_compression.h"

#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <sstream>
#include <optional>
#include <benchmark/benchmark.h>
#include <vector>
#include <ranges>

std::string formatNumbers(int i, int j, int k, int n) {
    std::ostringstream formattedString;
    formattedString << i << i << j << j << k << k << n << n;
    return formattedString.str();
}

// Function to generate all formatted strings
std::vector<std::string> generateAllFormattedStrings() {
    std::vector<std::string> formattedStrings;

    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            for (int k = 0; k <= 9; ++k) {
                for (int l = 0; l <= 9; ++l) {
                    formattedStrings.push_back(formatNumbers(i, j, k, l));
                }
            }
        }
    }

    return formattedStrings;
}



DecompositionFunction<std::string> decompose = [](const std::string& s) -> std::tuple<std::string, std::optional<std::string>> {
    int length = s.length();
    if (length <= 1) {
        return std::make_tuple(s, std::nullopt);
    }
    std::string l = s.substr(0, length / 2);
    std::string r = s.substr(length / 2);
    return std::make_tuple(l, r);
};

TreeHashTable<std::string> hash_table = TreeHashTable<std::string>();

template <class ...Args>
static void BM_fill_trees(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    std::vector<std::string> insertions = std::get<0>(args_tuple);
    
    for (auto _ : state) 
        for (auto value : insertions | std::views::take(state.range(0)))
            tree_find_or_put<std::string>(value, decompose, hash_table);
}

static void DoSetup(const benchmark::State& state) {
    hash_table = TreeHashTable<std::string>();
}

static void DoTeardown(const benchmark::State& state) {
    hash_table.clear();
}


// Register the function as a benchmark
BENCHMARK_CAPTURE(BM_fill_trees, "fill_tree_shared_subtree", generateAllFormattedStrings())
    ->Range(0, 10000)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown);

BENCHMARK_MAIN();