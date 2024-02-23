#include "fillWord/fillWord.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
    srand((unsigned int) time(nullptr));
    QApplication a(argc, argv);
    FillWordApp w;
    w.show();
    return a.exec();
}
