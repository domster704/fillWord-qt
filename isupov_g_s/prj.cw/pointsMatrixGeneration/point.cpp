#include "pointsMatrixGeneration/point.hpp"

Point::Point(int x, int y) : x(x), y(y) {}

bool Point::operator==(const Point& point2) const {
    return x == point2.x && y == point2.y;
}

bool Point::operator!=(const Point& point2) const {
    return !(*this == point2);
}
