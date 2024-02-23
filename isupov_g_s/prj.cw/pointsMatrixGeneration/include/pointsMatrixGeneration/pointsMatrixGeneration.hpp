#include "snakeAlgorithm.hpp"
#include "difficulty.hpp"

/**
 * @brief Класс для генерации матрицы точек c координатами x, y
 */
class PointsMatrixGeneration {
public:
    int rows{};
    int cols{};

    Difficulty difficulty = Difficulty::NORMAL;

    std::map<int, std::vector<Point>> pointMap;

    ~PointsMatrixGeneration() = default;

    PointsMatrixGeneration() = default;

    PointsMatrixGeneration(int rows, int cols, Difficulty difficulty);

    PointsMatrixGeneration(PointsMatrixGeneration& w) = default;

    PointsMatrixGeneration& operator=(const PointsMatrixGeneration& w) = default;
};
