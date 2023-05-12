#include <iostream>

namespace geo2d::orto {
    class Point {
    public:
        Point(double x, double y) : x(x), y(y) {}

        double x;
        double y;
    };

    class Quad {
    public:
        Quad() = default;

        Quad(Quad& quad) = default;

        ~Quad() = default;

        Quad(Point p1, Point p2, Point p3, Point p4) : p1(p1), p2(p2), p3(p3), p4(p4) {}

        Point p1;
        Point p2;
        Point p3;
        Point p4;
    };

    class Square : Quad {
    public:
        Square(Point p1, Point p2, Point p3, Point p4) : Quad(p1, p2, p3, p4) {}
    };

    class Rect : Quad {
    public:
        Rect(Point p1, Point p2, Point p3, Point p4) : Quad(p1, p2, p3, p4) {}
    };

    Quad Scale(Quad a, double scaleValue) {}

    Quad Intersect(const Quad& a, const Quad& b) {}

    Quad Union(const Quad& a, const Quad& b) {}
}


int main() {

    return 0;
}
