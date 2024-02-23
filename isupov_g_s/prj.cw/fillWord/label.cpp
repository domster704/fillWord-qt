#include <utility>

#include "fillWord/label.hpp"

WordLabel::WordLabel(QWidget* parent, std::string word) : QLabel(parent), word(std::move(word)) {
    this->setText(QString::fromStdString(this->word));
}

void WordLabel::SetGuessed() {
    this->setStyleSheet("text-decoration: line-through");
}