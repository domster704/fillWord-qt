#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <rational/rational.hpp>

TEST_CASE("testing the Rational arithmetic") {
    Rational first = Rational(2, 8);
    Rational second = Rational(1, 17);

    SUBCASE("Addition") {
        CHECK(first + second == Rational(21, 68));
        CHECK(++first == Rational(5, 4));
        CHECK(first++ == Rational(5, 4));
    }

    SUBCASE("Difference") {
        CHECK(first - second == Rational(13, 68));
        CHECK(--first == Rational(-3, 4));
        CHECK(first-- == Rational(-3, 4));
    }

    SUBCASE("Multiply") {
        CHECK(first * second == Rational(1, 68));
    }

    SUBCASE("Division") {
        CHECK(first / second == Rational(17, 4));
        CHECK_THROWS_AS(Rational(1, 0), const std::invalid_argument);
        CHECK_THROWS_AS(first / Rational(0, 1), const std::invalid_argument);

        Rational a = {5, -7};
        Rational b = {2, 3};
        b /= a;
        std::cout << b;
    }
}

TEST_CASE("testing comparison of rational") {
    Rational first = Rational(2, 8);
    Rational firstC = Rational(2, 8);
    Rational second = Rational(1, 17);

    SUBCASE("==") {
        CHECK_FALSE(first == second);
        CHECK(first != second);
        CHECK(first == firstC);
        CHECK_FALSE(first != firstC);
    }

    SUBCASE("<>") {
        CHECK(first > second);
        CHECK_FALSE(first > firstC);
        CHECK_FALSE(first < second);
    }

    SUBCASE("<>=") {
        CHECK(first >= second);
        CHECK(first >= firstC);
        CHECK_FALSE(first <= second);
    }
}
