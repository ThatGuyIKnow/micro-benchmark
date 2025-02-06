#ifndef TREE_COMPRESSION_H
#define TREE_COMPRESSION_H

#include <functional>
#include <optional>
#include <stdio.h>
#include <memory>
#include <tuple>
#include <unordered_map>

using std::shared_ptr, std::optional, std::tuple;


template<typename T>
class Tree;

template<typename T>
using TreeHashTable = std::unordered_map<T, std::shared_ptr<Tree<T>>>;

template<typename T>
using DecompositionFunction = std::function<tuple<T, std::optional<T>>(T)>;

template<typename T>
shared_ptr<Tree<T>> tree_find_or_put(T value, DecompositionFunction<T>& decomposer, TreeHashTable<T>& hash_table) {
  auto elem = hash_table.find(value);
  if (elem != hash_table.end()) {
    return elem->second;
  }
  auto tree = std::make_shared<Tree<T>>(Tree(value, decomposer, hash_table));
  hash_table[value] = tree;
  return tree;
}

template <typename T>
class Tree {

    public:
        shared_ptr<Tree> rtree;
        shared_ptr<Tree> ltree;
        optional<T> V;
        int k;

        Tree(T value, DecompositionFunction<T>& decomposer, TreeHashTable<T>& hash_table) 
        : decomposer(decomposer) {
          
          const auto [lvalue, opt_rvalue] = decomposer(value);
          if(opt_rvalue) {
              ltree = tree_find_or_put<T>(lvalue, decomposer, hash_table);
              rtree = tree_find_or_put<T>(opt_rvalue.value(), decomposer, hash_table);
              k = ltree->k;
              
          } else {
            V = lvalue;
          }
        
        };


        
    private:
        const DecompositionFunction<T> decomposer;
};



#endif