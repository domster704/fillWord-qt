#ifndef TESTQT_CELLBUTTON_HPP
#define TESTQT_CELLBUTTON_HPP

#include <QPushButton>

/**
 * \brief Класс для отображения кнопки в виде ячейки
 */
class CellButton final : public QPushButton {
    Q_OBJECT

public:
    int size;
    int row;
    int col;
    int serialNumber;
    char letter;
    std::string word;
    QString colorName;

    bool isGuessed = false;

    CellButton(QWidget* parent, int size, int row, int col, std::string word, int serialNumber, QString colorName);

    CellButton(const CellButton& cellButton) = delete;

    CellButton(const CellButton&& cellButton) = delete;

    ~CellButton() override = default;

    CellButton& operator=(const CellButton& cellButton) = delete;

	/**
	 * \brief Функция, которая ставит кнопку в состояние "отгадана"
	 */
	void SetGuessed();

	/**
	 * \brief Функция, которая ставит кнопку в состояние "выделена" курсором при нажатой ЛКМ
	 */
	void SetSelected();

	/**
	 * \brief Функция, которая ставит кнопку в состояние "не выделена" при отжатии ЛКМ
	 */
	void SetUnSelected();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif //TESTQT_CELLBUTTON_HPP
