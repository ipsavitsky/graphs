#include "matrix/denseMatrix.hpp"
#include "matrix/sparseMatrix.hpp"
#include "matrix/Matrix.hpp"

class Graph {
   private:
    Matrix& adjacency;
    // auto BronKerbosch(std::vector<size_t> R, std::vector<size_t> P, std::vector<size_t> X) -> void;
    auto floydWarshall () -> void;
   public:
    Graph() = delete;
    explicit Graph(Matrix&);
    Graph(const Graph&) = default;
    Graph(Graph&&) = default;
    ~Graph() = default;

    // Graph& operator=(Graph) noexcept;
    auto find_most_loaded_vertex() -> size_t;
    // auto find_max_clique() -> size_t;
    auto calculate_diameter() -> size_t;
};