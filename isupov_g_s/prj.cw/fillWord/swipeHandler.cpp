#include <utility>

#include "fillWord/swipeHandler.hpp"
#include "fillWord/cellButton.hpp"
#include "QDebug"

SwipeHandler::SwipeHandler(QWidget* window, std::function<void(std::vector<std::array<int, 2>>)> func,
                           const std::array<int, 2> windowLayoutSize) : window(window),
                                                                        callback(std::move(func)),
                                                                        windowLayoutSize(windowLayoutSize) {
}

void SwipeHandler::mouseMove(QMouseEvent* event) {
    if (!isMousePressed) {
        return;
    }
    QPoint position =
            event->globalPos() - window->pos() -
            // Половина высоты кнопки
            QPoint(0, static_cast<int>(0.6 * window->size().width() / windowLayoutSize[0] / 2));

    auto* widget = window->childAt(position);
    if (dynamic_cast<CellButton*>(widget) == nullptr) {
        return;
    }

    auto* cell = dynamic_cast<CellButton*>(widget);
    cell->SetSelected();

    selectedCells.push_back(cell);
    const auto last = std::unique(selectedCells.begin(), selectedCells.end());
    selectedCells.erase(last, selectedCells.end());
}

void SwipeHandler::mousePress(QMouseEvent* event) {
    isMousePressed = true;
}

void SwipeHandler::mouseRelease(QMouseEvent* event) {
    if (!selectedCells.empty()) {
        bool isWordCorrect = true;
        CellButton* previous = selectedCells[0];
        previous->SetUnSelected();

        int symbolsCount = 1;
        std::vector<std::array<int, 2>> cellsPos{{previous->row, previous->col}};
        for (int i = 1; i < selectedCells.size(); i++) {
            if (!(selectedCells[i]->word == previous->word &&
                  selectedCells[i]->serialNumber - previous->serialNumber == 1)) {
                isWordCorrect = false;
            }
            if (isWordCorrect) {
                cellsPos.push_back({selectedCells[i]->row, selectedCells[i]->col});
            }
            previous = selectedCells[i];
            selectedCells[i]->SetUnSelected();
            symbolsCount++;
        }

        if (isWordCorrect && symbolsCount == previous->word.size()) {
            callback(cellsPos);
        }
    }

    selectedCells.clear();
    isMousePressed = false;
}

SwipeHandler* SwipeHandler::getInstance(QWidget* widget, std::function<void(std::vector<std::array<int, 2>>)> callback,
                                        const std::array<int, 2> windowLayoutSize) {
    static SwipeHandler instance = SwipeHandler(widget, std::move(callback), windowLayoutSize);
    return &instance;
}
