#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w("/home/qywy/qt/1.wav");
    w.show();
    return a.exec();
}
