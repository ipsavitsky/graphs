#include "graph.hpp"

#include <algorithm>
#include <cmath>
#include <list>
#include <vector>

Graph::Graph(Matrix &matr) : adjacency{matr} {};

auto Graph::find_most_loaded_vertex() -> size_t {
    auto all_rows = adjacency.num_rows();
    std::vector<size_t> sum(all_rows);
    for (size_t i = 0; i < all_rows; ++i) {
        for (auto it = adjacency.iterate_rows(i); it != adjacency.end_rows(i);
             ++it) {
            ++sum[it.get_col()];
            ++sum[i];
        }
    }
    return std::distance(sum.begin(), std::max_element(sum.begin(), sum.end()));
}


auto Graph::calculate_diameter() -> size_t {
    auto rows = adjacency.num_rows();
    std::vector<std::vector<double>> dist(rows);
    for (size_t i = 0; i < rows; ++i) {
        dist[i] = std::vector<double>(rows);
    }
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < rows; j++) {
            if (fabs(adjacency.get(i, j)) <
                    std::numeric_limits<double>::epsilon() &&
                i != j) {
                dist[i][j] = std::numeric_limits<double>::infinity();
            } else {
                dist[i][j] = adjacency.get(i, j);
            }
        }
    }
    for (size_t k = 0; k < rows; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < rows; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    auto distance = -1;
    for (auto &vec : dist) {
        for (auto cur : vec) {
            if(cur > distance && cur < std::numeric_limits<double>::infinity()){
                distance = cur;
            }
        }
    }
    return distance;
    
}