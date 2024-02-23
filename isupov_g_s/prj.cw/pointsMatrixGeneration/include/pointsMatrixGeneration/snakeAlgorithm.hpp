#ifndef TESTQT_SNAKEALGORITHM_H
#define TESTQT_SNAKEALGORITHM_H

#include "point.hpp"
#include "direction.hpp"
#include "difficulty.hpp"

#include "vector"
#include "map"

/**
 * \brief Алгоритм генерации поля с помощью змеееподобных объектов, которые могут двигаться, есть другие объекты и исчезать.
 */
class SnakeAlgorithm {
public:
    ~SnakeAlgorithm() = default;

    SnakeAlgorithm() = delete;

    SnakeAlgorithm(SnakeAlgorithm& w) = default;

    SnakeAlgorithm& operator=(const SnakeAlgorithm& w) = delete;

    SnakeAlgorithm(int rows, int cols, Difficulty difficulty);

    /// \brief Инициализация алгоритма генерации поля.
    std::map<int, std::vector<Point>> Init();

private:
    /// \brief количество строк.
    int rows_{};
    /// \brief количество столбцов.
    int cols_{};

    /// \brief Сложность генерации поля.
    Difficulty difficulty;

    /// \brief Количесвто итераций для развития змееподобных объектов
    const int EVOLUTION_STEP_COUNT = 15;

    /// \brief Карта поля в виде массива значений <длина змеи, вектор точек>.
    std::map<int, std::vector<Point>> pointsMap;

    /// \brief Матрица, в которой хранится индекс каждой змеи.
    std::vector<std::vector<int>> matrix;

    void StartFill();

    /**
     * \brief Одна итерация развития змей на поле.
     */
    void EvolutionStep();

    /**
     * \brief Функция, которая пытается развить змею.
     * \param index - индекс змеи в матрице.
     */
    void TryToGrow(int index);

    /**
     * \brief Поиск и выбор направления для определенных действий змеи.
     * \param index - индекс змеи в матрице.
     * \param possibleDirection - возможные направления.
     * \param point - текущая точка.
     */
    void ChooseDirectionAndGrow(int index, const std::vector<Direction>& possibleDirection, Point point);

	/**
	 * \brief Функция, в которой змея уже непосредственно растет (развивается).
	 * \param index - индекс змеи в матрице.
	 * \param point - точка, в которую змея будет двигаться.
	 */
	void GrowFromPointToDirection(int index, Point point);

	/**
	 * \brief Функция, в которой выбирается и возвращается направление для змеи.
	 * \param point - точка, в которой сейчас голова или хвост змеи.
	 * \param index - индекс змеи в матрице.
	 * \return Направление, в котором змея будет двигаться.
	 */
	std::vector<Direction> GetPossibleDirection(Point point, int index);

	/**
	 * \brief Функция, которая определяет является ли точка хвостом или головой змеи.
	 * \param point - точка, в которой сейчас голова или хвост змеи.
	 * \return Если голова или хвост змеи, то возвращается true. Иначе false.
	 */
	bool IsPointHeadOrTail(Point point);
};

/**
 * \brief Функция, которая возвращает рандомное число в диапазоне.
 * \param min - минимальное значение.
 * \param max - максимальное значение.
 * \return Рандомное число в диапазоне min и max.
 */
int GetRandomNumberFromRange(int min, int max);

/**
 * \brief Функция, которая возвращает максимальную длину тела змеи в зависимости от сложности.
 * \param difficulty - уровень сложности.
 * \return
 */
int GetMaxLengthOfSnakeByDifficulty(Difficulty difficulty);

#endif //TESTQT_SNAKEALGORITHM_H
