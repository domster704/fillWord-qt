#ifndef TESTQT_SWIPEHANDLER_HPP
#define TESTQT_SWIPEHANDLER_HPP

#include <QMouseEvent>
#include <QWidget>
#include <vector>
#include <array>
#include "fillWord/cellButton.hpp"

/**
 * @brief Класс для обработки движением мыши. Класс является примером реализации Singleton.
 */
class SwipeHandler {
public:
    SwipeHandler() = delete;

    SwipeHandler(const SwipeHandler &) = delete;

    ~SwipeHandler() = default;

    static SwipeHandler* getInstance(QWidget *widget = nullptr,
                                     std::function<void(std::vector<std::array<int, 2>>)> callback = nullptr,
                                     std::array<int, 2> windowLayoutSize = {});

    /**
     * @brief Перехват события движения мыши. В функции происходит поиск ячейки (кнопки), которая была под курсором в момент нажатия ЛКМ, чтобы выделить эту ячейку (кнопку)
     * @param event - перехваченное событие мыши
     */
    void mouseMove(QMouseEvent* event);

    /**
     * @brief Перехват события движения мыши. Функция устанавливает состояние переменной `isMousePressed` в true, если нажата ЛКМ
     * @param event - перехваченное событие мыши
     */
    void mousePress(QMouseEvent* event);

    /**
     * @brief Перехват события движения мыши. Функция устанавливает состояние переменной `isMousePressed` в false, если отжата ЛКМ
     * @param event - перехваченное событие мыши
     */
    void mouseRelease(QMouseEvent* event);
private:
    bool isMousePressed = false;
    QWidget *window;
    std::function<void(std::vector<std::array<int, 2>>)> callback;
    std::array<int, 2> windowLayoutSize;

    /// \brief Массив выделенных ячеек.
    std::vector<CellButton *> selectedCells;

    SwipeHandler(QWidget *window, std::function<void(std::vector<std::array<int, 2>>)> func,
                 std::array<int, 2> windowLayoutSize);
};

#endif // TESTQT_SWIPEHANDLER_HPP
