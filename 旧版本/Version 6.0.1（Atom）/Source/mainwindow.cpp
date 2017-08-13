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
#include <QDebug>
#include <QDialog>
#include <QTimer>
#include <QTextStream>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QFile>
#include <QUrl>
#include <QEvent>
#include <QFileDialog>
#include <QMimeData>
#include <QPainter>
#include <QImage>
#include <QDragEnterEvent>
#include "fraction.h"
#include "const.h"
using namespace _Action;
using namespace std;

extern QMediaPlayer *player;
bool shiftdown=false;
bool poweron=false;
bool CanbeConvert=true;
bool isPlayingMusic=true;
extern bool isActive;
Frac ans=0;
int prec=8;
Frac memory=0;
stringstream *buffer;
QTimer *timer;
bool initgraph=true;
extern QString Vd;
bool expanded=false;
QString imageName=QString("BACK.jpg");
bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
     if (target==this)
     {
         if (event->type() == QEvent::DragEnter)
         {
             QDragEnterEvent *keyEvent = static_cast<QDragEnterEvent *>(event);
             keyEvent->acceptProposedAction();
             QList<QUrl> *filename=new QList<QUrl>(keyEvent->mimeData()->urls());
             if (filename->empty()==false)
             {
                 imageName=filename->first().toLocalFile();
                 repaint();
             }
         }
     }
     return QMainWindow::eventFilter(target, event);
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(imageName));
}

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
        this->setWindowTitle("CASIO FX-575MS (WINDOWS Vista) VERSION Atom");
        buffer=new stringstream("");
        timer=new QTimer();
        timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),this,SLOT(minus1s()));
        initgraph=false;
        QFile input("DataV.dat");
        QString read;
        QTextStream txtInput(&input);
        input.open(QIODevice::ReadOnly | QIODevice::Text);
        read=txtInput.readLine();
        if (read==Vd)
            isActive=true;
    }
    setContentsMargins(0,0,0,0);
    shiftdown=false;
    poweron=input;
    ans=0;
    ui->InputScreen->setText("");
    ui->ResultScreen->display("0");
    ui->InputScreen->setVisible(input);
    ui->ResultScreen->setVisible(input);
    ui->StateScreen->setVisible(input);
    ui->ShiftOn->setVisible(shiftdown);
    ui->AcAdapter->setVisible(isActive);
    ui->Active->setVisible(!isActive);
    ui->Charge->setVisible(!isActive);
    ui->StateScreen->setText("Answer");
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
    setAcceptDrops(true);
    installEventFilter(this);
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
    {
        ui->InputScreen->setText("");
    }
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
    CanbeConvert=true;
    string p=(ui->InputScreen->text()).toStdString();
    p="0+"+p;
    delete buffer;
    buffer=new stringstream(p);
    char t[1000];
    try
    {
        ans=limit();
       //if (_isnan(double(ans)))
           // throw Math_Error();
        ui->StateScreen->setText("Answer");
        sprintf(t,"%.*g",prec,double(ans));
        ui->ResultScreen->display(t);
    }
    catch(Syntax_Error)
    {
        ui->StateScreen->setText("Syn_Err");
        ui->ResultScreen->display(0);
    }
    catch(Math_Error)
    {
        ui->StateScreen->setText("Mth_Err");
        ui->ResultScreen->display(0);
    }
    setshift();
}


void MainWindow::on_Const_clicked()
{

    if (ui->ResultScreen->isVisible())
    {
        QString q=QInputDialog::getText(NULL,QString("InputConstOrder"),QString("1-40"));
        short t=q.toShort();
        if (t>0 && t<=40)
        {
            QString a=tr(name[t-1].c_str());
            ui->StateScreen->setText(a);
            char b[100];
            sprintf(b,"%.*g",prec,value[t-1]);
            ans=value[t-1];
            ui->ResultScreen->display(b);
        }
        else
            ui->StateScreen->setText("Stk_Err");
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
    char *lab="Powered By Windows 5.1\n\nVersion ATOM\n\n1992-2004, All Rights Reserved.";
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
    streamout<<hh<<" ' "<<mm<<" ' "<<ss<<" ' ";
    getline(streamout,output);
    ui->ResultScreen->display(QString::fromStdString(output));
    setshift();
}

void MainWindow::on_Fraction_clicked()
{
    if (CanbeConvert)
    {
        Frac resultfrac(ans);
        resultfrac.YF();
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
        ui->ResultScreen->display(QString::fromStdString(output));
    }
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

void MainWindow::on_More_clicked()
{
    if (expanded==false)
    {
        expanded=true;
        this->resize(631,671);
        ui->More->setStyleSheet("background-image: url(:/new/prefix1/up.ico);");
    }
    else
    {
        expanded=false;
        this->resize(631,452);
        ui->More->setStyleSheet("background-image: url(:/new/prefix1/down.ico);");
    }
}

void MainWindow::on_StopMedia_clicked()
{
    if (isPlayingMusic)
    {
        isPlayingMusic=false;
        ui->StopMedia->setText("StartMusic");
        player->stop();
    }
    else
    {
        isPlayingMusic=true;
        ui->StopMedia->setText("StopMusic");
        player->play();
    }
}

void MainWindow::doplay()
{
    if (isPlayingMusic==false)
    {
        player->stop();
    }
    else
    {
        player->play();
    }
}

void MainWindow::on_ChangeMedia_clicked()
{
    QString MusicName=QFileDialog::getOpenFileName(this,NULL,NULL,"*.mp3 *.wav *.ogg");
    if (!MusicName.isEmpty())
        player->setMedia(QUrl::fromLocalFile(MusicName));
}
