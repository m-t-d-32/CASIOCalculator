#include "start.h"
#include "ui_start.h"
#include <QTimer>
QTimer *sometime;
Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    sometime=new QTimer;
    connect(sometime,SIGNAL(timeout()),this,SLOT(close()));
    sometime->setInterval(2000);
    sometime->start();
}

Start::~Start()
{
    delete ui;
}
