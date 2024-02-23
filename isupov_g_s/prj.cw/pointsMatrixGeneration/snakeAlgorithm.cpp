#include "pointsMatrixGeneration/snakeAlgorithm.hpp"

#include <algorithm>
#include <ctime>
#include <iostream>

SnakeAlgorithm::SnakeAlgorithm(const int rows, const int cols, const Difficulty difficulty) : rows_(rows), cols_(cols),
                                                                            difficulty(difficulty) {
    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error("Недопустимые значения");
    }
    matrix.resize(rows, std::vector<int>(cols));
}

std::map<int, std::vector<Point>> SnakeAlgorithm::Init() {
    StartFill();

    for (int i = 0; i < EVOLUTION_STEP_COUNT; i++) {
        EvolutionStep();
    }

    return pointsMap;
}

void SnakeAlgorithm::StartFill() {
    int index = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix[i][j] = index;
            pointsMap[index++] = std::vector<Point>{Point(i, j)};
        }
    }
}

void SnakeAlgorithm::EvolutionStep() {
    for (const auto& pair: pointsMap) {
        TryToGrow(pair.first);
    }
}

void SnakeAlgorithm::TryToGrow(const int index) {
    if (!pointsMap.count(index)) {
        return;
    }

    std::vector<Point> snake = pointsMap[index];
    Point head = snake[0];
    Point tail = snake[snake.size() - 1];

    std::vector<Direction> possibleDirection = GetPossibleDirection(tail, index);
    if (!possibleDirection.empty()) {
        ChooseDirectionAndGrow(index, possibleDirection, tail);
        return;
    }

    possibleDirection = GetPossibleDirection(head, index);
    if (!possibleDirection.empty()) {
        std::vector<Point> futureReverseVector = pointsMap[index];
        std::reverse(futureReverseVector.begin(), futureReverseVector.end());
        pointsMap[index] = std::move(futureReverseVector);

        ChooseDirectionAndGrow(index, possibleDirection, head);
        return;
    }
}

void SnakeAlgorithm::ChooseDirectionAndGrow(const int index, const std::vector<Direction>& possibleDirection, const Point point) {
    const Direction direction = possibleDirection[GetRandomNumberFromRange(0, static_cast<int>(possibleDirection.size()))];

    int deltaX = 0;
    int deltaY = 0;
    switch (direction) {
        case Direction::LEFT:
            deltaY = -1;
            break;
        case Direction::RIGHT:
            deltaY = 1;
            break;
        case Direction::TOP:
            deltaX = -1;
            break;
        case Direction::BOTTOM:
            deltaX = 1;
            break;
    }

    GrowFromPointToDirection(index, Point(point.x + deltaX, point.y + deltaY));
}

void SnakeAlgorithm::GrowFromPointToDirection(const int index, const Point point) {
    const int key = matrix[point.x][point.y];
    if (key == index) {
        throw std::runtime_error("Свой");
    }

    if (pointsMap[index].size() + pointsMap[key].size() > GetMaxLengthOfSnakeByDifficulty(difficulty)) {
        return;
    }

    if (point != pointsMap[key][0]) {
        std::vector<Point> futureReverseVector = pointsMap[key];
        std::reverse(futureReverseVector.begin(), futureReverseVector.end());
        pointsMap[key] = std::move(futureReverseVector);
    }

    for (const Point& pointEl: pointsMap[key]) {
        matrix[pointEl.x][pointEl.y] = index;
    }

    pointsMap[index].insert(pointsMap[index].end(), pointsMap[key].begin(), pointsMap[key].end());
    pointsMap.erase(key);

    // Если 66 процентов, то переворачиваем вектор
    if (GetRandomNumberFromRange(0, 100) < 66) {
        std::vector<Point> futureReverseVector = pointsMap[index];
        std::reverse(futureReverseVector.begin(), futureReverseVector.end());
        pointsMap[index] = std::move(futureReverseVector);
    }
}

std::vector<Direction> SnakeAlgorithm::GetPossibleDirection(Point point, int index) {
    std::vector<Direction> possibleDirection;

    int x = point.x;
    int y = point.y;

    if (y > 0 && matrix[x][y - 1] != index && IsPointHeadOrTail(Point(x, y - 1))) {
        possibleDirection.push_back(Direction::LEFT);
    }
    if (y < cols_ - 1 && matrix[x][y + 1] != index && IsPointHeadOrTail(Point(x, y + 1))) {
        possibleDirection.push_back(Direction::RIGHT);
    }
    if (x > 0 && matrix[x - 1][y] != index && IsPointHeadOrTail(Point(x - 1, y))) {
        possibleDirection.push_back(Direction::TOP);
    }
    if (x < rows_ - 1 && matrix[x + 1][y] != index && IsPointHeadOrTail(Point(x + 1, y))) {
        possibleDirection.push_back(Direction::BOTTOM);
    }

    return possibleDirection;
}

bool SnakeAlgorithm::IsPointHeadOrTail(Point point) {
    if (point.x < 0 || point.y < 0) {
        return false;
    }

    int key = matrix[point.x][point.y];
    if (!pointsMap.count(key)) {
        return false;
    }

    return point == pointsMap[key][0] || point == pointsMap[key][pointsMap[key].size() - 1];
}

int GetRandomNumberFromRange(const int min, const int max) {
    srand(time(0));
    return rand() % (max - min) + min;
}

int GetMaxLengthOfSnakeByDifficulty(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::VERY_EASY:
            return 4;
        case Difficulty::EASY:
            return 6;
        case Difficulty::NORMAL:
            return 12;
        case Difficulty::HARD:
            return 14;
        case Difficulty::VERY_HARD:
            return 16;
        default:
            return 12;
    }
}
