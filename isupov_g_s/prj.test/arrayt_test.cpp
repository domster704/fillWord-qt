#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "arrayt/arrayt.hpp"
#include "doctest/doctest.h"


TEST_CASE("DefaultConstructor") {
    ArrayT arr;
    CHECK(arr.ssize() == 0);
    CHECK(arr.capacity() == 0);
}

TEST_CASE("ConstructorWithParameter") {
    ArrayT arr(5);
    CHECK(arr.ssize() == 5);
    CHECK(arr.capacity() == 5);
}

TEST_CASE("CopyConstructor") {
    ArrayT arr1(5);
    arr1[0] = 1.0;
    ArrayT arr2(arr1);
    CHECK(arr1.ssize() == arr2.ssize());
    CHECK(arr1.capacity() == arr2.capacity());
    CHECK(arr1[0] == arr2[0]);
}

TEST_CASE("SubscriptOperator") {
    ArrayT arr(5);
    arr[0] = 1.0;
    CHECK(arr[0] == 1.0);
    CHECK_THROWS_AS(arr[5], std::out_of_range);
}

TEST_CASE("InsertMethod") {
    ArrayT arr(5);
    arr.insert(1.0, 0);
    CHECK(arr[0] == 1.0);
    CHECK_THROWS_AS(arr.insert(1.0, 6), std::invalid_argument);
}

TEST_CASE("remove") {
    SUBCASE("remove from middle") {
        ArrayT arr(4);
        arr[0] = 1.0;
        arr[1] = 2.0;
        arr[2] = 3.0;
        arr[3] = 4.0;

        arr.remove(2);
        REQUIRE(arr[0] == 1.0);
        REQUIRE(arr[1] == 2.0);
        REQUIRE(arr[2] == 4.0);
        REQUIRE(arr.ssize() == 3);
    }

    SUBCASE("remove from front") {
        ArrayT arr(4);
        arr[0] = 1.0;
        arr[1] = 2.0;
        arr[2] = 3.0;
        arr[3] = 4.0;

        arr.remove(0);
        REQUIRE(arr[0] == 2.0);
        REQUIRE(arr[1] == 3.0);
        REQUIRE(arr[2] == 4.0);
        REQUIRE(arr.ssize() == 3);
    }

    SUBCASE("remove from back") {
        ArrayT arr(4);
        arr[0] = 1.0;
        arr[1] = 2.0;
        arr[2] = 3.0;
        arr[3] = 4.0;

        arr.remove(3);
        REQUIRE(arr[0] == 1.0);
        REQUIRE(arr[1] == 2.0);
        REQUIRE(arr[2] == 3.0);
        REQUIRE(arr.ssize() == 3);
    }

    /*SUBCASE("remove from empty array") {
        ArrayD emptyArr(0);
        REQUIRE_THROWS_AS(emptyArr.remove(0), std::invalid_argument);
        REQUIRE(emptyArr.ssize() == 0);
    }*/

    SUBCASE("remove from single element array") {
        ArrayT singleArr(1);
        singleArr[0] = 1.0;
        singleArr.remove(0);
        REQUIRE(singleArr.ssize() == 0);
    }

    SUBCASE("remove from single element array with invalid index") {
        ArrayT singleArr(1);
        singleArr[0] = 1.0;
        REQUIRE_THROWS_AS(singleArr.remove(1), std::invalid_argument);
        REQUIRE(singleArr.ssize() == 1);
    }
}


TEST_CASE("ClearMethod") {
    ArrayT arr(5);
    arr.clear();
    CHECK(arr.ssize() == 0);
    CHECK(arr.capacity() == 0);
}

TEST_CASE("ResizeMethod") {
    ArrayT arr(5);
    arr.resize(10);
    CHECK(arr.ssize() == 10);
    CHECK(arr.capacity() == 10);
    arr.resize(2);
    CHECK(arr.ssize() == 2);
    CHECK(arr.capacity() == 2);
}

TEST_CASE("AssignmentOperator") {
    ArrayT arr1(5);
    arr1[0] = 1.0;
    ArrayT arr2;
    arr2 = arr1;
    CHECK(arr1.ssize() == arr2.ssize());
    CHECK(arr1.capacity() == arr2.capacity());
    CHECK(arr1[0] == arr2[0]);
}
