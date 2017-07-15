#include "mainwindow.h"
#include "start.h"
#include <QApplication>
#include <QMediaPlayer>
Start *start;
QMediaPlayer *player;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    start=new Start;
    start->setWindowFlags(Qt::FramelessWindowHint);
    start->setWindowTitle("Welcome");
    start->exec();
    player=new QMediaPlayer(0);
    QObject::connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),&w,SLOT(doplay()));
    player->setMedia(QUrl::fromLocalFile("BackMusic.mp3"));
    player->play();
    w.resize(631,452);
    w.show();
    return a.exec();
}
