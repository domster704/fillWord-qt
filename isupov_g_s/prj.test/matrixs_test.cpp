#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "matrixs/matrixs.hpp"

TEST_CASE("Default constructor") {
    MatrixS m;
    CHECK(m.ssize() == std::make_tuple(0, 0));
}

TEST_CASE("Explicit constructor with tuple") {
    MatrixS m(std::make_tuple(2, 3));
    CHECK(m.ssize() == std::make_tuple(2, 3));
    CHECK(m.nRows() == 2);
    CHECK(m.nCols() == 3);

    m.at(0, 0) = 1;
    m.at(0, 1) = 2;
    m.at(0, 2) = 3;
    m.at(1, 0) = 4;
    m.at(1, 1) = 5;
    m.at(1, 2) = 6;

    CHECK(m.at(0, 0) == 1);
    CHECK(m.at(0, 1) == 2);
    CHECK(m.at(0, 2) == 3);
    CHECK(m.at(1, 0) == 4);
    CHECK(m.at(1, 1) == 5);
    CHECK(m.at(1, 2) == 6);
}

TEST_CASE("Copy constructor") {
    MatrixS m1(std::make_tuple(3, 3));
    m1.at(0, 0) = 1;
    m1.at(0, 1) = 2;
    m1.at(0, 2) = 3;
    m1.at(1, 0) = 4;
    m1.at(1, 1) = 5;
    m1.at(1, 2) = 6;
    m1.at(2, 0) = 7;
    m1.at(2, 1) = 8;
    m1.at(2, 2) = 9;

    MatrixS m2(m1);
    CHECK(m2.ssize() == std::make_tuple(3, 3));
    CHECK(m2.nRows() == 3);
    CHECK(m2.nCols() == 3);
    CHECK(m2.at(0, 0) == 1);
    CHECK(m2.at(0, 1) == 2);
    CHECK(m2.at(0, 2) == 3);
    CHECK(m2.at(1, 0) == 4);
    CHECK(m2.at(1, 1) == 5);
    CHECK(m2.at(1, 2) == 6);
    CHECK(m2.at(2, 0) == 7);
    CHECK(m2.at(2, 1) == 8);
    CHECK(m2.at(2, 2) == 9);
}

TEST_CASE("Assignment operator") {
    MatrixS m1(std::make_tuple(2, 2));
    m1.at(0, 0) = 1;
    m1.at(0, 1) = 2;
    m1.at(1, 0) = 3;
    m1.at(1, 1) = 4;

    MatrixS m2(std::make_tuple(3, 3));
    m2.at(0, 0) = 5;
    m2.at(0, 1) = 6;
    m2.at(0, 2) = 7;
    m2.at(1, 0) = 8;
    m2.at(1, 1) = 9;
    m2.at(1, 2) = 10;
    m2.at(2, 0) = 11;
    m2.at(2, 1) = 12;
    m2.at(2, 2) = 13;

    m2 = m1;
    CHECK(m2.ssize() == std::make_tuple(2, 2));
    CHECK(m2.nRows() == 2);
    CHECK(m2.nCols() == 2);
    CHECK(m2.at(0, 0) == 1);
    CHECK(m2.at(0, 1) == 2);
    CHECK(m2.at(1, 0) == 3);
    CHECK(m2.at(1, 1) == 4);
}

TEST_CASE("Indexing operator") {
    MatrixS m(std::make_tuple(2, 2));
    m.at(0, 0) = 1;
    m.at(0, 1) = 2;
    m.at(1, 0) = 3;
    m.at(1, 1) = 4;

    CHECK(m.at(0, 0) == 1);
    CHECK(m.at(0, 1) == 2);
    CHECK(m.at(1, 0) == 3);
    CHECK(m.at(1, 1) == 4);

    CHECK_THROWS_AS(m.at(-1, 0), std::out_of_range);
    CHECK_THROWS_AS(m.at(0, -1), std::out_of_range);
    CHECK_THROWS_AS(m.at(2, 0), std::out_of_range);
    CHECK_THROWS_AS(m.at(0, 2), std::out_of_range);
}

TEST_CASE("Resize method") {
    MatrixS m(std::make_tuple(2, 2));
    m.at(0, 0) = 1;
    m.at(0, 1) = 2;
    m.at(1, 0) = 3;
    m.at(1, 1) = 4;

    m.resize(std::make_tuple(3, 3));
    CHECK(m.ssize() == std::make_tuple(3, 3));
    CHECK(m.nRows() == 3);
    CHECK(m.nCols() == 3);
    CHECK(m.at(0, 0) == 1);
    CHECK(m.at(0, 1) == 2);
    CHECK(m.at(0, 2) == 0);
    CHECK(m.at(1, 0) == 3);
    CHECK(m.at(1, 1) == 4);
    CHECK(m.at(1, 2) == 0);
    CHECK(m.at(2, 0) == 0);
    CHECK(m.at(2, 1) == 0);
    CHECK(m.at(2, 2) == 0);

    m.resize(std::make_tuple(2, 4));
    CHECK(m.ssize() == std::make_tuple(2, 4));
    CHECK(m.nRows() == 2);
    CHECK(m.nCols() == 4);
    CHECK(m.at(0, 0) == 1);
    CHECK(m.at(0, 1) == 2);
    CHECK(m.at(0, 2) == 0);
    CHECK(m.at(0, 3) == 0);
    CHECK(m.at(1, 0) == 3);
    CHECK(m.at(1, 1) == 4);
    CHECK(m.at(1, 2) == 0);
    CHECK(m.at(1, 3) == 0);

    CHECK_THROWS_AS(m.resize(0, 2), std::invalid_argument);
    CHECK_THROWS_AS(m.resize(2, 0), std::invalid_argument);
}


