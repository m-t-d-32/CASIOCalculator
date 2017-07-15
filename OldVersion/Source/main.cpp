#include "mainwindow.h"
#include "start.h"
#include <QApplication>
Start *start;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    start=new Start;
    start->setWindowFlags(Qt::FramelessWindowHint);
    start->setWindowTitle("Welcome");
    start->exec();
    w.show();
    return a.exec();
}
