#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <fstream>
#include <qinputdialog.h>
#include <QApplication>
#include "calculate.h"
#include <QDialog>
#include <QTimer>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include "fraction.h"
#include "const.h"
using namespace _Action;
using namespace std;


bool shiftdown=false;
bool poweron=false;
extern bool isActive;
double ans=0;
int prec=8;
double memory=0;
stringstream *buffer;
QTimer *timer;
bool initgraph=true;
extern QString Vd;

void MainWindow::setshift()
{
    shiftdown=false;
    ui->ShiftOn->setVisible(false);
}

void MainWindow::minus1s()
{
    int v=ui->Battery->value();
    if (v)
        ui->Battery->setValue(v-1);
    else
    {
        init(false);
        QMessageBox::critical(NULL,"Battery","Battery Low!Calculator now power off!");
    }
}

void MainWindow::init(bool input)
{
    if (initgraph)
    {
        ui->groupBox->setStyleSheet("border:none");
        this->setWindowTitle("CASIO FX-575MS (WINDOWS XP 64-BIT) VERSION 5.0");
        buffer=new stringstream("");
        timer=new QTimer();
        timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),this,SLOT(minus1s()));
        initgraph=false;
        QFile input("DataV.dat");
        QString read;
        if(!input.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            cout << "Open failed." << endl;
        }
        QTextStream txtInput(&input);
        read=txtInput.readLine();
        if (read==Vd)
            isActive=true;
    }
    setContentsMargins(0,0,0,0);
    shiftdown=false;
    poweron=input;
    ans=0;
    ui->InputScreen->setText("");
    ui->ResultScreen->setText("0");
    ui->InputScreen->setVisible(input);
    ui->ResultScreen->setVisible(input);
    ui->ShiftOn->setVisible(shiftdown);
    ui->AcAdapter->setVisible(isActive);
    ui->Active->setVisible(!isActive);
    ui->Charge->setVisible(!isActive);
    prec=ui->Precision->value();
    if (isActive)
    {
         ui->Battery->setValue(100);
    }
    else
    {
         if (input)
             timer->start();
         else
             timer->stop();
    }
    if (input)
    {
        ui->Memory_Show->setVisible(judge_m());
    }
    else
    {
        ui->Memory_Show->setVisible(false);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ResultScreen->setAlignment(Qt::AlignRight);
    init(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Number0_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"0");
}

void MainWindow::on_Number1_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"1");
}
void MainWindow::on_Number2_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"2");
}

void MainWindow::on_Number3_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"3");
}
void MainWindow::on_Number4_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"4");
}

void MainWindow::on_Number5_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"5");
}


void MainWindow::on_Number6_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"6");
}

void MainWindow::on_Number7_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"7");
}

void MainWindow::on_Number8_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"8");
}

void MainWindow::on_Number9_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"9");
}

void MainWindow::on_Dot_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+".");
}

void MainWindow::on_Plus_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"+");
}

void MainWindow::on_Minus_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"-");
}

void MainWindow::on_Multiple_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"x");
}

void MainWindow::on_Divide_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"/");
}

void MainWindow::on_Del_clicked()
{
    QString Screentext=ui->InputScreen->text();
    int len=Screentext.length();
    if (len)
    {
        if (Screentext[len-1].isDigit())
        {
            len--;
        }
        else
        {
            do
            {
                len--;
            }
            while (len>0 && (Screentext[len-1].isLetter() || Screentext[len-1]=='\\'));
        }
        Screentext=Screentext.mid(0,len);
        ui->InputScreen->setText(Screentext);
    }
    setshift();
}

void MainWindow::on_Ac_clicked()
{
    if (shiftdown)
        init(false);
    else
        ui->InputScreen->setText("");
    setshift();
}

void MainWindow::on_Shift_clicked()
{
    if (poweron)
    {
        shiftdown=!shiftdown;
        ui->ShiftOn->setVisible(shiftdown);
    }
}

void MainWindow::on_On_clicked()
{
    if (ui->Battery->value()<10 && ui->Battery->value()>0)
    {
        QMessageBox::warning(NULL,"Battery","Battery Low!Please Charge!");
        init(true);
    }
    else if (ui->Battery->value()<=0)
    {
        QMessageBox::critical(NULL,"Battery","Battery Low!Calculator can not start!");
    }
    else
    {
        init(true);
    }
}


void MainWindow::on_LeftSign_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+"(");
}

void MainWindow::on_RightSign_clicked()
{
    ui->InputScreen->setText(ui->InputScreen->text()+")");
}



void MainWindow::on_GetAnswer_clicked()
{
    string p=(ui->InputScreen->text()).toStdString();
    p="0+"+p;
    delete buffer;
    buffer=new stringstream(p);
    char t[1000];
    try
    {
        ans=limit();
        sprintf(t,"%.*g",prec,ans);
        QString qs(t);
        ui->ResultScreen->setText(qs);
    }
    catch(Syntax_Error)
    {
        ui->ResultScreen->setText("Syntax_Error");
    }
    catch(Math_Error)
    {
        ui->ResultScreen->setText("Math_Error");
    }
    setshift();
}



void MainWindow::on_Const_clicked()
{

    if (ui->ResultScreen->isVisible())
    {
        QString q=QInputDialog::getText(NULL,QString("InputConstOrder"),QString("1-20"));
        short t=q.toShort();
        if (t>0 && t<=20)
        {
            QString a=tr(name[t-1].c_str());
            char b[1000];
            sprintf(b,"%.*g",prec,value[t-1]);
            a=a+QString("=")+QString(b);
            ui->ResultScreen->setText(a);
        }
        else
            ui->ResultScreen->setText("Stack_Error");
    }
    setshift();
}

void MainWindow::on_Sin_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"arcsin(");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"sin(");
    }
    setshift();
}

void MainWindow::on_Cos_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"arccos(");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"cos(");
    }
    setshift();
}

void MainWindow::on_Tan_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"arctan(");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"tan(");
    }
    setshift();
}

void MainWindow::on_Log_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"10^");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"log(");
    }
    setshift();
}

void MainWindow::on_Ln_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"e^");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"In(");
    }
    setshift();
}

void MainWindow::on_Charge_clicked()
{
    ui->Battery->setValue(100);
    if (ui->ResultScreen->isVisible()==false)
    {
        init(true);
    }
}

void MainWindow::on_About_clicked()
{
    char *lab="Powered By Windows 5.1\n\nVersion 5.0\n\n1992-2004, All Rights Reserved.";
    QMessageBox::information(NULL,"About",lab,0);
}

void MainWindow::on_Answer_clicked()
{

    ui->InputScreen->setText(ui->InputScreen->text()+"ANS");
    setshift();
}

void MainWindow::on_SetPrecision_clicked()
{
    if (poweron)
    {
        prec=ui->Precision->value();
        QMessageBox::information(NULL,"Success","Operation Confirmed!");
        setshift();
    }
}

void MainWindow::on_Active_clicked()
{
    QMessageBox::information(NULL,"Activate","After Activation you won't need to charge the battery!");
    dialog.setWindowTitle("ActiveWindow");
    dialog.exec();
    if (isActive)
    {
        ui->AcAdapter->setVisible(true);
        ui->Battery->setValue(100);
        timer->stop();
        ui->Active->setVisible(false);
        ui->Charge->setVisible(false);
    }
}

void MainWindow::on_Square_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"^3");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"^2");
    }
    setshift();
}


void MainWindow::on_Power_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+tr("X√"));
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"^");
    }
    setshift();
}

void MainWindow::on_Inverse_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"!");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"^-1");
    }
    setshift();
}

void MainWindow::on_Radical_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+tr("3X√"));
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+tr("2X√"));
    }
    setshift();
}


void MainWindow::on_E_pi_clicked()
{

    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+tr("pi"));
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+tr("e"));
    }
    setshift();
}

void MainWindow::on_TimeFormat_clicked()
{

    int hh,mm;
    double ss;
    get_timeformat(hh,mm,ss);
    string output;
    stringstream streamout;
    if (ans<0)
        streamout<<"-";
    streamout<<hh<<" H "<<mm<<" M "<<ss<<" S ";
    getline(streamout,output);
    ui->ResultScreen->setText(QString::fromStdString(output));
    setshift();
}

void MainWindow::on_Fraction_clicked()
{
    Frac resultfrac(ans);
    if(shiftdown)
    {
        resultfrac.set_out_statue(false);
    }
    else
    {
        resultfrac.set_out_statue(true);
    }
    string output;
    stringstream streamout;
    streamout<<resultfrac;
    getline(streamout,output);
    ui->ResultScreen->setText(QString::fromStdString(output));
    setshift();
}

void MainWindow::on_Negative_clicked()
{
    if(shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"M");
    }
    else
    {
        ui->InputScreen->setText("-("+ui->InputScreen->text());
    }
    setshift();
}

void MainWindow::on_Memory_clicked()
{
    if(shiftdown)
    {
        memory-=ans;
        ui->Memory_Show->setVisible(judge_m());
    }
    else
    {
        memory+=ans;
        ui->Memory_Show->setVisible(judge_m());
    }
    setshift();
}

void MainWindow::on_Integral_clicked()
{
    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"d\\du(");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"S(");
    }
    setshift();
}

void MainWindow::on_Y_clicked()
{
    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+",");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"U");
    }
    setshift();
}
void MainWindow::on_Rand_clicked()
{
    if (shiftdown)
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"Rnd#");
    }
    else
    {
        ui->InputScreen->setText(ui->InputScreen->text()+"Rnd(");
    }
    setshift();
}
