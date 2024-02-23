#include "fillWord/fillWord.hpp"
#include "fillWord/swipeHandler.hpp"

#include <iostream>
#include <QApplication>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>

FillWordApp::FillWordApp(QWidget *parent)
        : QMainWindow(parent) {
    Q_INIT_RESOURCE(resources);
    setlocale(LC_ALL, "Russian");
    ReloadMatrix();

    // Screenshot actions
    auto *makeScreenshotAction = new QAction("Save screenshot", this);
    auto *settings = menuBar()->addMenu("Settings");
    settings->addAction(makeScreenshotAction);
    connect(makeScreenshotAction, &QAction::triggered, this, &FillWordApp::MakeScreenshot);

    // difficulty actions
    auto *veryEasyAction = new QAction("Very easy", this);
    auto *veryEasy = new QAction("Easy", this);
    auto *normalAction = new QAction("Normal", this);
    auto *hardAction = new QAction("Hard", this);
    auto *veryHardAction = new QAction("Very hard", this);

    auto *difficulty = menuBar()->addMenu("Level of difficulty");
    difficulty->addAction(veryEasyAction);
    difficulty->addAction(veryEasy);
    difficulty->addAction(normalAction);
    difficulty->addAction(hardAction);
    difficulty->addAction(veryHardAction);

    connect(veryEasyAction, &QAction::triggered, this, &FillWordApp::ChangeDifficulty);
    connect(veryEasy, &QAction::triggered, this, &FillWordApp::ChangeDifficulty);
    connect(normalAction, &QAction::triggered, this, &FillWordApp::ChangeDifficulty);
    connect(hardAction, &QAction::triggered, this, &FillWordApp::ChangeDifficulty);
    connect(veryHardAction, &QAction::triggered, this, &FillWordApp::ChangeDifficulty);
}

void FillWordApp::CreateButtonsAndWords() {
    for (int i = 0; i < pointsMatrixGeneration.rows; i++) {
        cellsMatrix.emplace_back();
        for (int j = 0; j < pointsMatrixGeneration.cols; ++j) {
            cellsMatrix[i].emplace_back(nullptr);
        }
    }

    auto *wordsVLayout = new QVBoxLayout();
    for (const auto &pair: pointsMatrixGeneration.pointMap) {
        int wordIndex = 0;
        std::string word = wordsGenerator.GetRandomWordByLength(pair.second.size());
        if (word[0] != '*') {
            wordLabelMap[word] = new WordLabel(wordsVLayout->widget(), word);
        } else {
            word = word.substr(1, word.size());
        }

        QColor color = QColor(rand() % 255, rand() % 255, rand() % 255);

        for (const auto &point: pair.second) {
            auto *button = new CellButton(this,
                                          static_cast<int>(0.6 * this->size().width() / pointsMatrixGeneration.rows),
                                          point.x,
                                          point.y, word, wordIndex++, color.name());
            cellsMatrix[point.x][point.y] = button;
        }
    }

    // Заполнение макета словами
    for (auto &pair: wordLabelMap) {
        wordsVLayout->addWidget(pair.second);
    }

    // Заполнение макета кнопками
    auto *buttonsVLayout = new QVBoxLayout();
    for (int i = 0; i < pointsMatrixGeneration.rows; i++) {
        auto *hLayout = new QHBoxLayout();
        for (int j = 0; j < pointsMatrixGeneration.cols; ++j) {
            hLayout->addWidget(cellsMatrix[i][j]);
        }
        buttonsVLayout->addLayout(hLayout);
    }
    mainLayout->addLayout(wordsVLayout);
    mainLayout->addLayout(buttonsVLayout);
}

void FillWordApp::mouseMoveEvent(QMouseEvent *event) {
    SwipeHandler *swipeHandler = SwipeHandler::getInstance();
    swipeHandler->mouseMove(event);
}

void FillWordApp::mousePressEvent(QMouseEvent *event) {
    SwipeHandler *swipeHandler = SwipeHandler::getInstance();
    swipeHandler->mousePress(event);
}

void FillWordApp::mouseReleaseEvent(QMouseEvent *event) {
    SwipeHandler *swipeHandler = SwipeHandler::getInstance();
    swipeHandler->mouseRelease(event);
}

FillWordApp::~FillWordApp() {
    ClearAllVariables();
}

void FillWordApp::WordIsCorrect(const std::vector<std::array<int, 2>> &cells) {
    for (auto &pos: cells) {
        cellsMatrix[pos[0]][pos[1]]->SetGuessed();
    }

    wordLabelMap[cellsMatrix[cells[0][0]][cells[0][1]]->word]->SetGuessed();
}

bool FillWordApp::MakeScreenshot() {
    const QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "",
                                                          "Image Files (*.png *.jpg *.bmp)");
    const QPixmap p = QPixmap::grabWidget(this);
    return p.save(fileName);
}

void FillWordApp::ChangeDifficulty() {
    const std::string newDifficulty = qobject_cast<QAction *>(sender())->text().toStdString();
    if (newDifficulty == "Very easy") {
        this->difficulty_ = Difficulty::VERY_EASY;
    } else if (newDifficulty == "Easy") {
        this->difficulty_ = Difficulty::EASY;
    } else if (newDifficulty == "Normal") {
        this->difficulty_ = Difficulty::NORMAL;
    } else if (newDifficulty == "Hard") {
        this->difficulty_ = Difficulty::HARD;
    } else if (newDifficulty == "Very hard") {
        this->difficulty_ = Difficulty::VERY_HARD;
    }

    ReloadMatrix();
}

void FillWordApp::ReloadMatrix() {
    pointsMatrixGeneration = PointsMatrixGeneration(10, 15, this->difficulty_);

    ClearAllVariables();
    QFile words(":/res/words.txt");
    words.open(QFile::ReadOnly);

    wordsGenerator = WordsGenerator(words.readAll().toStdString());

    this->setWindowTitle("FillWord");
    auto *widget = new QWidget();
    mainLayout = new QHBoxLayout(widget);

    setMinimumSize(width_, height_);
    CreateButtonsAndWords();

    setCentralWidget(widget);

    QFile style(":/style/app.qss");
    style.open(QFile::ReadOnly);
    const QString sty(style.readAll());
    this->setStyleSheet(sty);

    SwipeHandler::getInstance(this, [this](const std::vector<std::array<int, 2>> &cells) {
        this->WordIsCorrect(cells);
    }, {pointsMatrixGeneration.rows, pointsMatrixGeneration.cols});
}

void FillWordApp::ClearAllVariables() {
    for (auto &i: cellsMatrix) {
        for (auto &j: i) {
            delete j;
        }
    }
    cellsMatrix.clear();
    for (auto &pair: wordLabelMap) {
        delete pair.second;
    }
    wordLabelMap.clear();
}
