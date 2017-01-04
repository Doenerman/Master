#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedWidth(MAINWINDOW_WIDTH);
    w.setFixedHeight(MAINWINDOW_HEIGHT);
    w.show();

    return a.exec();
}
