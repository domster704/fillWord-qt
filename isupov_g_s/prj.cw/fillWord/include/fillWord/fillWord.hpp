#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fillWord/cellButton.hpp"
#include "label.hpp"
#include "pointsMatrixGeneration/pointsMatrixGeneration.hpp"
#include "wordsGenerator.hpp"

#include <QHBoxLayout>
#include <QMainWindow>
#include <map>

/**
 * \brief Класс главного окна приложения.
 */
class FillWordApp final : public QMainWindow {
	Q_OBJECT

public:
	explicit FillWordApp(QWidget *parent = nullptr);

	~FillWordApp() override;

	/**
	 * \brief Проверка правильности выделенных ячеек, которые должны составлять правильное слово.
	 */
	void WordIsCorrect(const std::vector<std::array<int, 2>> &);

private:
	int width_ = 1200;
	int height_ = 800;

	Difficulty difficulty_{Difficulty::NORMAL};

	/// \brief Массив ячеек.
	std::vector<std::vector<CellButton *>> cellsMatrix{};
	///  \brief Массив текстовых полей с сгенерированными словами.
	std::map<std::string, WordLabel *> wordLabelMap{};

	QHBoxLayout *mainLayout;

	PointsMatrixGeneration pointsMatrixGeneration;
	WordsGenerator wordsGenerator;

	/**
	 * \brief Создание ячеек и текстовых полей с сгенерированными словами.
	 */
	void CreateButtonsAndWords();

	/**
	 * \brief Создание скриншота окна приложения.
	 * \return был ли создан скриншот или нет.
	 */
	bool MakeScreenshot();

	/**
	 * \brief Изменение сложности генерации поля.
	 */
	void ChangeDifficulty();

	/**
	 * \brief Перезагрузка поля и других параметров
	 */
	void ReloadMatrix();

	/**
	 * \brief Очистка всех массивов и других переменных.
	 */
	void ClearAllVariables();

protected:
	void mouseMoveEvent(QMouseEvent *event) override;

	void mousePressEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
