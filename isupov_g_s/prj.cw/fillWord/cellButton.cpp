#include "fillWord/cellButton.hpp"
#include "fillWord/swipeHandler.hpp"

#include <QDebug>
#include <utility>

CellButton::CellButton(QWidget *parent, int size, int row, int col,
                       std::string word, int serialNumber, QString colorName)
    : QPushButton(parent), row(row), col(col), size(size),
      word(std::move(word)), colorName(std::move(colorName)),
      serialNumber(serialNumber) {
  letter = this->word[serialNumber];

  this->setFixedSize(QSize(size, size));

  this->setText(QString(letter));
}

void CellButton::mouseMoveEvent(QMouseEvent *event) {
  SwipeHandler *swipeHandler = SwipeHandler::getInstance();
  swipeHandler->mouseMove(event);
}

void CellButton::mousePressEvent(QMouseEvent *event) {
  SwipeHandler *swipeHandler = SwipeHandler::getInstance();
  swipeHandler->mousePress(event);
}

void CellButton::mouseReleaseEvent(QMouseEvent *event) {
  SwipeHandler *swipeHandler = SwipeHandler::getInstance();
  swipeHandler->mouseRelease(event);
}

void CellButton::SetGuessed() {
  this->setStyleSheet(QString::fromStdString("background-color: ") + colorName +
                      ";color: #333333;");
  isGuessed = true;
}

void CellButton::SetSelected() {
  if (isGuessed)
    return;
  this->setStyleSheet("background-color: #23ABDC;"
                      "color: white;");
}

void CellButton::SetUnSelected() {
  if (isGuessed)
    return;
  this->setStyleSheet("background-color: white;"
                      "color: #333333;");
}
