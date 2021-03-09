#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H
#include <Matrix.h>
#include <vector>
#include <filesystem>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.cpp>




TEST_CASE("test file exists") {
  REQUIRE(std::filesystem::exists("./data/crossword.dat") == true);
}

TEST_CASE("matrices can be filled from user input", "[matrix]" ) {
  vector<string> crossword;
  vector<string> words {"EXIT", "HERO", "OREO", "ICE"};
  std::ifstream f {"./data/crossword.dat"};
  REQUIRE(std::filesystem::exists("./data/crossword.dat") == true);
  REQUIRE(f.is_open() == true);
  copy(std::istream_iterator<string>{f}, {}, std::back_inserter(crossword));
  Matrix<char> mat(crossword); //(crossword);

  SECTION("Can load a vector of strings") {
    REQUIRE(mat.numRows() == 4);
    REQUIRE(mat[3][3] >= 43); // {-+}
  }
}

TEST_CASE("matrices have STL-compliant access", "[matrix-iterator]" ) {
  vector<string> crossword;
  vector<string> words {"EXIT", "HERO", "OREO", "ICE"};
  std::ifstream f {"./data/crossword.dat"};
  REQUIRE(f.is_open() == true);
  copy(std::istream_iterator<string>{f}, {}, std::back_inserter(crossword));
  Matrix<char> mat(crossword); //(crossword);

  SECTION("Can access data", "[STL]") {
    REQUIRE(!empty(mat.data()));
    REQUIRE(mat[0][0] == '-');
  }
}

TEST_CASE("matrices can be iterated", "[matrix-iterator]" ) {
  vector<string> crossword;
  vector<string> words {"EXIT", "HERO", "OREO", "ICE"};
  std::ifstream f {"./data/crossword.dat"};
  copy(std::istream_iterator<string>{f}, {}, std::back_inserter(crossword));
  Matrix<char> mat(crossword); //(crossword);

  SECTION("iterating horizontally via range-based for") {
    [[maybe_unused]] auto loop = [&mat]() {
      for ([[maybe_unused]]auto& c : mat) {
        continue;
      }
    };
    loop();
    REQUIRE_NOTHROW(loop());
  }

  SECTION("iterating vertically") {

    SECTION("Can fill entire column with new character") {
      for (auto vIt {mat.colBegin(1)}; vIt != mat.colEnd(1); ++vIt) {
        *vIt = 'A';
      }
      REQUIRE(mat[0][1] == 'A');
      REQUIRE(mat[3][1] == 'A');
    }

    SECTION("Can fill column range with new character") {
      MatrixColumnIterator<char> toIt(mat, 2, 2); 
      for (auto vIt {mat.colBegin(2)}; vIt != toIt; ++vIt) {
        *vIt = 'B';
      }

      REQUIRE(mat[1][2] == 'B');
    }
  }
}
#endif /* ifndef MATRIX_TEST_H */
