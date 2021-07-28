#include "matrix/denseMatrix.hpp"
#include "matrix/sparseMatrix.hpp"
#include "matrix/Matrix.hpp"

class Graph {
   private:
    Matrix& adjacency;
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