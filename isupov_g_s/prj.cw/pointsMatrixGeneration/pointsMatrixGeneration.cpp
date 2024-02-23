#include "pointsMatrixGeneration/pointsMatrixGeneration.hpp"

PointsMatrixGeneration::PointsMatrixGeneration(const int rows, const int cols,
                                               const Difficulty difficulty) : rows(rows), cols(cols),
                                                                              pointMap(SnakeAlgorithm(rows,
                                                                                  cols,
                                                                                  difficulty).Init()),
                                                                              difficulty(difficulty) {
}
