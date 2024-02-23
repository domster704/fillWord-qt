#ifndef TESTQT_POINT_HPP
#define TESTQT_POINT_HPP

/**
 * @brief Класс для описания положения в матрице
 */
class Point {
public:
    /** @brief Номер строки */
    int x;
    /** @brief Номер столбца */
    int y;

    Point() = default;

    ~Point() = default;

    Point(int x, int y);

    Point(const Point& point) = default;

    Point(Point&& point) = default;

    Point& operator=(const Point& point) = default;

    bool operator==(const Point& point2) const;

    bool operator!=(const Point& point2) const;
};

#endif //TESTQT_POINT_HPP
