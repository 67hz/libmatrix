#ifndef MATRIX_H
#define MATRIX_H 
#include <cstddef>
#include <cassert>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

using std::string;
using std::vector;

template <typename T> class Matrix;

// \todo: copyable, assignable, swappable, dtor
template <typename T> class MatrixColumnIterator {
  T *p {};
  Matrix<T> &mat;
  std::pair<int, int> pos; // x,y coords of matrix

public:
  MatrixColumnIterator(Matrix<T> &mat, int x_ = 0, int y_ = 0)
      : mat(mat), pos(x_, y_) {}

  T &operator*() { return mat[pos.first][pos.second]; }

  /// \todo make const?
  MatrixColumnIterator &operator++() {
    ++pos.first; // increase x coord (keep col same)
    return *this;
  }

  MatrixColumnIterator operator++(int) {
    auto tmp{*this};
    ++this;
    return tmp;
  }

  template <typename U>
  friend bool operator!=(const MatrixColumnIterator<U> &lhs,
                         const MatrixColumnIterator<U> &rhs) {
    assert(lhs.pos.second == rhs.pos.second);
    return rhs.pos != lhs.pos;
  }

  template <typename U>
  friend bool operator==(const MatrixColumnIterator<U> &lhs,
                         const MatrixColumnIterator<U> &rhs) {
    assert(lhs.pos.second == rhs.pos.second);
    return !(*lhs != rhs);
  }
};


// implement transpose as either copy or temp view... see EOCI
template <typename T>
class Matrix {
  using Mat = vector<vector<T>>;

public:
  using vert_iterator = MatrixColumnIterator<T>;
  using iterator = typename vector<T>::iterator;
  using const_iterator = typename vector<T>::const_iterator;

  Matrix(const vector<string> &XCoord)
      : rows{XCoord.size()}, cols{XCoord.size()}, coll(rows) {
    {
      size_t i, j;
      const char *c;
      for (i = 0; i < XCoord.size(); ++i) {
        for (j = 0, c = XCoord[i].c_str(); *c != '\0'; ++c, ++j) {
          coll[i].emplace_back(*c);
        }
      }
    }
  }

  vector<char> &operator[](int row) { return coll[row]; }

  /// \param col[in] column to iterate
  /// \todo implement via slices. See Stoustrop 29.2.2
  vert_iterator colBegin(const int col = 0) noexcept {
    assert(col <= numCols());
    return MatrixColumnIterator<char>(*this, 0, col);
  }

  vert_iterator colEnd(const int col = 0) noexcept {
    return MatrixColumnIterator<char>(*this, rows, col);
  }

  // should remove and use matrix[row].begin() instead
  iterator begin(const int row = 0) noexcept { return coll[row].begin(); }

  const_iterator cBegin(const int row = 0) const noexcept {
    assert(row <= numRows());
    return coll[row].begin();
  }

  iterator end(const int row = 0) noexcept { return coll[row].end(); }

  const_iterator cEnd(const int row = 0) const noexcept {
    return coll[row].end();
  }

  int numRows() { return rows; }
  int numCols() { return cols; }
  Mat data() { return coll; }

private:
  size_t rows{};
  size_t cols{};
  Mat coll;
};

namespace std {
template <typename T>
struct iterator_traits<MatrixColumnIterator<T>> { // post-C++17 do this instead
                                                  // of inheriting from
                                                  // std::iterator
  using vector_t = std::vector<T>;
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type =
      typename vector_t::difference_type; // ->std::ptrdiff_t;
  using iterator = MatrixColumnIterator<T>;
  using pointer = typename vector_t::pointer;
  using const_pointer = typename vector_t::const_pointer;
  using size_type = typename vector_t::size_type;
};
} // namespace std

#endif /* ifndef MATRIX_H */
