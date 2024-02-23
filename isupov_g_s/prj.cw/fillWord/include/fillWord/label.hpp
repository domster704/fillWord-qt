#ifndef TESTQT_LABEL_HPP
#define TESTQT_LABEL_HPP

#include <QLabel>

/**
 * \brief Класс для отображения текстового поля
 */
class WordLabel final : public QLabel {
Q_OBJECT

public:
    WordLabel(QWidget* parent, std::string word);

    ~WordLabel() override = default;

    WordLabel(const WordLabel& wordLabel) = delete;

    WordLabel(const WordLabel&& wordLabel) = delete;

    WordLabel& operator=(const WordLabel& wordLabel) = delete;

	/**
	 * \brief Функция, которая ставит текстовое поле в состояние "отгадано" и зачерквает текст.
	 */
	void SetGuessed();

private:
    std::string word;
};

#endif //TESTQT_LABEL_HPP
