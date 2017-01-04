#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedWidth(600);
    w.setFixedHeight(650);
    w.show();

    return a.exec();
}
