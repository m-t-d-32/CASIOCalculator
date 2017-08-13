#include "dialog.h"
#include "ui_dialog.h"
#include <string>
#include <iostream>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFile>
using namespace std;
#include "active.h"
bool isActive=false;
QString Vd="2041558087";
//extern MainWindow *mainConsole;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::MakeItActive()
{
    QFile input("DataV.dat");
    input.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream txtOutput(&input);
    txtOutput<<Vd;
    input.close();
    isActive=true;
}

void Dialog::on_Confirm_clicked()
{
    string getnum=(ui->lineEdit->text()).toStdString();
    if (judge(getnum))
    {
        QMessageBox::information(NULL,"Success!","Congratulations!");
        MakeItActive();
        this->close();
    }
    else
    {
        QMessageBox::warning(NULL,"Failed","Wrong Number!Please check!");
    }
}

void Dialog::on_Cancel_clicked()
{
    this->close();
}

void Dialog::on_commandLinkButton_clicked()
{
    QMessageBox::information(NULL,"Help","For more help,please refer to the following website!",64);
    QDesktopServices::openUrl(QUrl("http://windows2009.ys168.com"));
}

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    static QString old=ui->lineEdit->text();
    QString temp=ui->lineEdit->text();
    for (int i=0;i<temp.length();i++)
    {
        if (isValid(temp[i])==false)
        {
           QMessageBox::information(NULL,"Warning!","invalid input!");
           ui->lineEdit->setText(old);
           break;
        }
    }
    old=ui->lineEdit->text();
}

