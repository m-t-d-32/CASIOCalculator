#include "controller.h"
#include "calculate.h"
#include "baseconv.h"
#include "const.h"
#include "fraction.h"
#include "ui_controller.h"
#include <QtGui>
#include <QTextCodec>
#include <QMediaPlayer>
#include <QFile>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#define eps 1e-9
using namespace _Action;
Frac ans;
Frac memory;
stringstream *buffer;
enum exp_value{Rad,Deg};
int express;
int num_base=10;
int basing=false;

Controller::Controller(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Controller)
{
    ui->setupUi(this);
    init();
}

void Controller::init()
{
    this->setWindowTitle("CASIO Celeron");
    ui->Y->setWhatsThis("用这个按钮代表表达式中的字母");
    QPushButton *temp[]={
            ui->Number0,ui->Number1,ui->Number2,ui->Number3,
            ui->Number4,ui->Number5,ui->Number6,ui->Number7,
            ui->Number8,ui->Number9,ui->NumberA,ui->NumberB,
            ui->NumberC,ui->NumberD,ui->NumberE,ui->NumberF,
            ui->NumberG,ui->NumberH,ui->NumberI,ui->NumberJ,
            ui->NumberK,ui->NumberL,ui->NumberM,ui->NumberN,
            ui->NumberO,ui->NumberP,ui->NumberQ,ui->NumberR,
            ui->NumberS,ui->NumberT,ui->NumberU,ui->NumberV,
            ui->NumberW,ui->NumberX,ui->NumberY,ui->NumberZ
        };
    for (int i=0;i<36;i++)
    {
        base_buttons[i]=temp[i];
    }
    now=geometry();
    player=new QMediaPlayer(0);
    player->setMedia(QUrl::fromLocalFile("BackMusic.mp3"));
    player->play();
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),player,SLOT(play()));
    prec=8;
    ui->InputScreen->setText("");
    ui->ResultScreen->setText("0");\

    setTabOrder(ui->X11,ui->X12);
    setTabOrder(ui->X12,ui->X13);

    setTabOrder(ui->X21,ui->X22);
    setTabOrder(ui->X22,ui->X23);

    setTabOrder(ui->X31,ui->X32);
    setTabOrder(ui->X32,ui->X33);
    setTabOrder(ui->X33,ui->X34);
    setTabOrder(ui->X34,ui->X35);
    setTabOrder(ui->X35,ui->X36);

    setTabOrder(ui->X41,ui->X42);
    setTabOrder(ui->X42,ui->X43);
    setTabOrder(ui->X43,ui->X44);
    setTabOrder(ui->X44,ui->X45);
    setTabOrder(ui->X45,ui->X46);
    setTabOrder(ui->X46,ui->X47);
    setTabOrder(ui->X47,ui->X48);
    setTabOrder(ui->X48,ui->X49);
    setTabOrder(ui->X49,ui->X4A);
    setTabOrder(ui->X4A,ui->X4B);
    setTabOrder(ui->X4B,ui->X4C);

    vector<QLineEdit *>temp1;
    temp1.push_back(ui->X11);
    temp1.push_back(ui->X12);
    temp1.push_back(ui->X13);
    vector<QLineEdit *>temp2;
    temp2.push_back(ui->X21);
    temp2.push_back(ui->X22);
    temp2.push_back(ui->X23);
    vector<QLineEdit *>temp3;
    temp3.push_back(ui->X31);
    temp3.push_back(ui->X32);
    temp3.push_back(ui->X33);
    temp3.push_back(ui->X34);
    temp3.push_back(ui->X35);
    temp3.push_back(ui->X36);
    vector<QLineEdit *>temp4;
    temp4.push_back(ui->X41);
    temp4.push_back(ui->X42);
    temp4.push_back(ui->X43);
    temp4.push_back(ui->X44);
    temp4.push_back(ui->X45);
    temp4.push_back(ui->X46);
    temp4.push_back(ui->X47);
    temp4.push_back(ui->X48);
    temp4.push_back(ui->X49);
    temp4.push_back(ui->X4A);
    temp4.push_back(ui->X4B);
    temp4.push_back(ui->X4C);
    chk.push_back(temp1);
    chk.push_back(temp2);
    chk.push_back(temp3);
    chk.push_back(temp4);
}

Controller::~Controller()
{
    delete ui;
}

void Controller::do_keys()
{
    for (int i=0;i<num_base;i++)
    {
        base_buttons[i]->setEnabled(true);
    }
    for (int i=num_base;i<36;i++)
    {
        base_buttons[i]->setEnabled(false);
    }
}

bool judge_if_number(QString t)
{
    string m=t.toStdString();
    if (m.size()==0)
        return false;
    for (int i=0;i<m.size();i++)
    {
        if (m[i]<'0' || m[i]>'9')
        {
            return false;
        }
    }
    return true;
}

void Controller::on_Number0_clicked()
{
    ui->InputScreen->insert("0");
}

void Controller::on_Number1_clicked()
{
    ui->InputScreen->insert("1");
}
void Controller::on_Number2_clicked()
{
    ui->InputScreen->insert("2");
}

void Controller::on_Number3_clicked()
{
    ui->InputScreen->insert("3");
}
void Controller::on_Number4_clicked()
{
    ui->InputScreen->insert("4");
}

void Controller::on_Number5_clicked()
{
    ui->InputScreen->insert("5");
}


void Controller::on_Number6_clicked()
{
    ui->InputScreen->insert("6");
}

void Controller::on_Number7_clicked()
{
    ui->InputScreen->insert("7");
}

void Controller::on_Number8_clicked()
{
    ui->InputScreen->insert("8");
}

void Controller::on_Number9_clicked()
{
    ui->InputScreen->insert("9");
}

void Controller::on_Dot_clicked()
{
    ui->InputScreen->insert(".");
}

void Controller::on_Plus_clicked()
{
    ui->InputScreen->insert("+");
}

void Controller::on_Minus_clicked()
{
    ui->InputScreen->insert("-");
}

void Controller::on_Multiple_clicked()
{
    ui->InputScreen->insert("x");
}

void Controller::on_Divide_clicked()
{
    ui->InputScreen->insert("/");
}

void Controller::on_GetAnswer_clicked()
{
    string str=ui->InputScreen->text().toStdString();
    if (basing)
    {
        str=convertwhole(str,num_base);
    }
    stringstream streamt(str);
    buffer=&streamt;
    try
    {
        ans=limit();
        if (basing)
        {
            int t=(int)(double)(ans);
            string abb=tobs(t,num_base);
            ui->ResultScreen->setText(QString::fromStdString(abb));
        }
        else
        {
            char chrs[1000];
            sprintf(chrs,"%.*g",prec,double(ans));
            ui->ResultScreen->setText(chrs);
        }
    }
    catch (Syntax_Error)
    {
        ui->ResultScreen->setText("语法错误");
    }
    catch (...)
    {
        ui->ResultScreen->setText("数学错误");
    }
}

void Controller::on_LeftSign_clicked()
{
    ui->InputScreen->insert("(");
}

void Controller::on_RightSign_clicked()
{
    ui->InputScreen->insert(")");
}

void Controller::on_Answer_clicked()
{
    ui->InputScreen->insert("ANS");
}

void Controller::on_Sin_clicked()
{
    ui->InputScreen->insert("sin(");
}

void Controller::on_Cos_clicked()
{
    ui->InputScreen->insert("cos(");
}

void Controller::on_Tan_clicked()
{
    ui->InputScreen->insert("tan(");
}

void Controller::on_Arcsin_clicked()
{
    ui->InputScreen->insert("arcsin(");
}

void Controller::on_Arccos_clicked()
{
    ui->InputScreen->insert("arccos(");
}

void Controller::on_Arctan_clicked()
{
    ui->InputScreen->insert("arctan(");
}

void Controller::on_Sqr_clicked()
{
    ui->InputScreen->insert("^2");
}

void Controller::on_Tri_clicked()
{
    ui->InputScreen->insert("^3");
}

void Controller::on_Pow_clicked()
{
    ui->InputScreen->insert("^");
}

void Controller::on_Sqrt_clicked()
{
    ui->InputScreen->insert("2X√");
}


void Controller::on_Trit_clicked()
{
    ui->InputScreen->insert("3X√");
}

void Controller::on_Powt_clicked()
{
    ui->InputScreen->insert("X√");
}


void Controller::on_Time_clicked()
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
    ui->ResultScreen->setText(QString::fromStdString(output));
}

void Controller::on_Mixed_clicked()
{
    Frac resultfrac(ans);
    resultfrac.set_out_statue(true);
    string output;
    stringstream streamout;
    streamout<<resultfrac;
    getline(streamout,output);
    ui->ResultScreen->setText(QString::fromStdString(output));
}

void Controller::on_Impor_clicked()
{
    Frac resultfrac(ans);
    resultfrac.set_out_statue(false);
    string output;
    stringstream streamout;
    streamout<<resultfrac;
    getline(streamout,output);
    ui->ResultScreen->setText(QString::fromStdString(output));
}

void Controller::on_Deri_clicked()
{
    ui->InputScreen->insert("d\\du(");
}

void Controller::on_Inte_clicked()
{
    ui->InputScreen->insert("S(");
}

void Controller::on_Y_clicked()
{
    ui->InputScreen->insert("U");
}

void Controller::on_comma_clicked()
{
    ui->InputScreen->insert(",");
}

void Controller::on_InteHelp_clicked()
{
    QMessageBox::information(0,"帮助","这里的求导符号是d/du，函数中的参数是\
U，举个例子，如果我们要求f(u)=u^3+8u在\
u=4处的导数，我们需要输入d/du(u^3+8*u,\
4)然后按下等号即可。\n\n这里的积分符号是\
S，函数中的参数是U，举个例子，如果我们要求\
f(u)=u^4+8从u=3到u=4的积分，我们需要输入\
S(u^4+8,3,4)，然后按下等号即可。积分可能需\
要较长时间，请耐心等待。");
}

void Controller::on_SetPrecision_clicked()
{
    prec=ui->Precision->value();
    QMessageBox::information(NULL,"Success","Operation Confirmed!");
}

void Controller::on_RandX_clicked()
{
    ui->InputScreen->insert("Rnd#");
}

void Controller::on_RandS_clicked()
{
    ui->InputScreen->insert("Rnd(");
}

void Controller::on_Comma2_clicked()
{
    ui->InputScreen->insert(",");
}


void Controller::on_Delete_clicked()
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
}

void Controller::on_Clear_clicked()
{
    ui->InputScreen->setText("");
    ui->ResultScreen->setText("0");
    ans=0;
}

void Controller::on_Deg_clicked()
{
    express=Deg;
}

void Controller::on_Rad_clicked()
{
    express=Rad;
}

void Controller::on_GetConst_clicked()
{
    int t=ui->Const->value();
    QString a=tr(name[t-1].c_str());
    ui->ResultScreen->setText(a+"=");
    char b[100];
    sprintf(b,"%.*g",prec,value[t-1]);
    ans=value[t-1];
    ui->ResultScreen->insert(b);
}

void Controller::on_StopMusic_clicked()
{
    if (isPlayingMusic)
    {
        isPlayingMusic=false;
        ui->StopMusic->setText("开始音乐");
        disconnect(player,SIGNAL(stateChanged(QMediaPlayer::State)),player,SLOT(play()));
        player->stop();
    }
    else
    {
        isPlayingMusic=true;
        ui->StopMusic->setText("停止音乐");
        connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),player,SLOT(play()));
        player->play();
    }
}

void Controller::on_ChangeMusic_clicked()
{
    QString MusicName=QFileDialog::getOpenFileName(this,NULL,NULL,"*.mp3 *.wav *.ogg");
    if (!MusicName.isEmpty())
        player->setMedia(QUrl::fromLocalFile(MusicName));
    if (isPlayingMusic)
    {
        player->play();
    }
}

void Controller::on_Settle_clicked()
{
    ui->science->hide();
    ui->solve->hide();
    ui->base->hide();
    ui->settle->setGeometry(30,310,451,121);
    ui->settle->show();
    ui->Dot->setEnabled(true);
    basing=false;
    num_base=10;
}

void Controller::on_Science_clicked()
{
    ui->settle->hide();
    ui->solve->hide();
    ui->base->hide();
    ui->science->setGeometry(30,310,451,121);
    ui->science->show();
    ui->Dot->setEnabled(true);
    basing=false;
    num_base=10;
}

void Controller::on_Solve_clicked()
{
    ui->settle->hide();
    ui->science->hide();
    ui->base->hide();
    ui->solve->setGeometry(30,310,451,121);
    ui->solve->show();
    ui->Dot->setEnabled(true);
    basing=false;
    num_base=10;
}

void Controller::on_Base_clicked()
{
    ui->settle->hide();
    ui->science->hide();
    ui->solve->hide();
    ui->base->setGeometry(30,310,451,121);
    ui->base->show();
    ui->Dot->setEnabled(false);
    ui->Bs10->setChecked(true);
    basing=true;
    num_base=10;
    do_keys();
    ui->InputScreen->setText("");
}


void Controller::on_X1_clicked()
{
    bool canbesolve=true;
    for (vector<QLineEdit *>::iterator it=chk[0].begin();it!=chk[0].end();it++)
    {
        if (judge_if_number((*it)->text())==false)
        {
            canbesolve=false;
        }
    }
    if (canbesolve)
    {
        double x11=ui->X11->text().toDouble();
        if (!x11)
        {
            ui->ResultScreen->setText("数学错误");
        }
        else
        {
            double x12=ui->X12->text().toDouble();
            double x13=ui->X13->text().toDouble();
            ui->ResultScreen->setText("x="+QString::number((x13-x12)/x11));
        }
    }
    else
    {
        ui->ResultScreen->setText("语法错误");
    }
}


void Controller::on_X2_clicked()
{
    bool canbesolve=true;
    for (vector<QLineEdit *>::iterator it=chk[1].begin();it!=chk[1].end();it++)
    {
        if (judge_if_number((*it)->text())==false)
        {
            canbesolve=false;
        }
    }
    if (canbesolve)
    {
        double a=ui->X21->text().toDouble();
        if (!a)
        {
            ui->ResultScreen->setText("数学错误");
        }
        else
        {
            double b=ui->X22->text().toDouble();
            double c=ui->X23->text().toDouble();
            if (b*b-4*a*c<0)
            {
                ui->ResultScreen->setText("无实数解");
            }
            else if (fabs(b*b-4*a*c)<eps)
            {
                ui->ResultScreen->setText("x1=x2="+QString::number(-b/2/a));
            }
            else
            {
                ui->ResultScreen->setText("x1="+QString::number((-b+sqrt(b*b-4*a*c))/2/a));
                ui->ResultScreen->insert(",x2="+QString::number((-b-sqrt(b*b-4*a*c))/2/a));
            }
        }
    }
    else
    {
        ui->ResultScreen->setText("语法错误");
    }
}

void Controller::on_X3_clicked()
{
    bool canbesolve=true;
    for (vector<QLineEdit *>::iterator it=chk[2].begin();it!=chk[2].end();it++)
    {
        if (judge_if_number((*it)->text())==false)
        {
            canbesolve=false;
        }
    }
    if (canbesolve)
    {
        double a1=ui->X31->text().toDouble();
        double b1=ui->X32->text().toDouble();
        double c1=ui->X33->text().toDouble();
        double a2=ui->X34->text().toDouble();
        double b2=ui->X35->text().toDouble();
        double c2=ui->X36->text().toDouble();
        if (fabs(a1*b2-a2*b1)<eps && fabs(b2*c1-b1*c2)>eps)
        {
            ui->ResultScreen->setText("无解");
        }
        else if(fabs(a1*b2-a2*b1)<eps && fabs(b2*c1-b1*c2)<eps)
        {
            ui->ResultScreen->setText("无数多解");
        }
        else
        {
            double x=(b2*c1-b1*c2)/(a1*b2-a2*b1);
            double y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
            ui->ResultScreen->setText("x="+QString::number(x)+",y="+QString::number(y));
        }
    }
    else
    {
        ui->ResultScreen->setText("语法错误");
    }
}

void Controller::on_X4_clicked()
{
    bool canbesolve=true;
    for (vector<QLineEdit *>::iterator it=chk[3].begin();it!=chk[3].end();it++)
    {
        if (judge_if_number((*it)->text())==false)
        {
            canbesolve=false;
        }
    }
    if (canbesolve)
    {
        double a1=ui->X41->text().toDouble();
        double b1=ui->X42->text().toDouble();
        double c1=ui->X43->text().toDouble();
        double d1=ui->X44->text().toDouble();
        double a2=ui->X45->text().toDouble();
        double b2=ui->X46->text().toDouble();
        double c2=ui->X47->text().toDouble();
        double d2=ui->X48->text().toDouble();
        double a3=ui->X49->text().toDouble();
        double b3=ui->X4A->text().toDouble();
        double c3=ui->X4B->text().toDouble();
        double d3=ui->X4C->text().toDouble();
        double H=a1*(b2*c3-c2*b3)-a2*(b1*c3-c1*b3)+a3*(b1*c2-c1*b2);
        double H1=d1*(b2*c3-c2*b3)-d2*(b1*c3-c1*b3)+d3*(b1*c2-c1*b2);
        double H2=d1*(c2*a3-a2*c3)+d2*(a1*c3-c1*a3)-d3*(a1*c2-c1*a2);
        double H3=d1*(a2*b3-b2*a3)-d2*(a1*b3-b1*a3)+d3*(a1*b2-b1*a2);
        if(fabs(H)<eps)
        {
            if (fabs(H1)<eps && fabs(H2)<eps && fabs(H3)<eps)
            {
                ui->ResultScreen->setText("无数多解");
            }
            else
            {
                ui->ResultScreen->setText("无解");
            }
        }
        else
        {
            double x=H1/H;
            double y=H2/H;
            double z=H3/H;
            ui->ResultScreen->setText("x="+QString::number(x)+",y="+QString::number(y)+",z="+QString::number(z));
        }
    }
    else
    {
        ui->ResultScreen->setText("语法错误");
    }
}

void Controller::on_CLR1_clicked()
{
    ui->X11->setText("");
    ui->X12->setText("");
    ui->X13->setText("");
}

void Controller::on_CLR2_clicked()
{
    ui->X21->setText("");
    ui->X22->setText("");
    ui->X23->setText("");
}

void Controller::on_CLR3_clicked()
{
    ui->X31->setText("");
    ui->X32->setText("");
    ui->X33->setText("");
    ui->X34->setText("");
    ui->X35->setText("");
    ui->X36->setText("");
}

void Controller::on_CLR4_clicked()
{
    ui->X41->setText("");
    ui->X42->setText("");
    ui->X43->setText("");
    ui->X44->setText("");
    ui->X45->setText("");
    ui->X46->setText("");
    ui->X47->setText("");
    ui->X48->setText("");
    ui->X49->setText("");
    ui->X4A->setText("");
    ui->X4B->setText("");
    ui->X4C->setText("");
}

void Controller::on_Unknowned_clicked()
{
    ui->InputScreen->insert("U");
}
void Controller::on_Equaled_clicked()
{
    ui->InputScreen->insert("=0");
}

void Controller::on_Clear_2_clicked()
{
    ui->InputScreen->setText("");
}

void Controller::on_DoSolve_clicked()
{
    string t=ui->InputScreen->text().toStdString();
    int i=0,max=t.size();
    for (;i<max;i++)
    {
        if (t[i]=='=')
        {
            break;
        }
    }
    if (i!=max && i+2==max && t[i+1]=='0')
    {
        string m(t.begin(),t.end()-2);
        stringstream temp(m);
        buffer=&temp;
        bool syerr=false;
        double x=0;
        double y;
        for (int i=0;i<1e6;i++)
        {
            try
            {
                y=funclnte(m,x);
                if (fabs(y)<1e-6) break;
                x=x-y/RealVite(x);
            }
            catch (Syntax_Error)
            {
                syerr=true;
                break;
            }
            catch (...)
            {

            }
        }
        if (syerr==true)
        {
            ui->ResultScreen->setText("语法错误");
        }
        else
        {
            if (fabs(y)>1e-4)
            {
                ui->ResultScreen->setText("未解出有效解");
            }
            else
            {
                ui->ResultScreen->setText("u="+QString::number(x));
            }
        }
    }
}

void Controller::on_SolveHelp_clicked()
{
    QMessageBox::information(0,"帮助","这里的方程可以是\
多项式方程，超越方程等，但是在解方程之前，我们\
必须先把方程化为f(u)=0的形式，其中f(u)是关于\
未知数u的一个函数式，比如我们想要求解方程sin(u)=0.5\
需要先手动移项变成sin(u)-0.5=0，我们可以在这里用\
science模式中的sin符号以及通用模块中的减号和数字等\
输入sin(u)-0.5，然后按下“输入=0”这个符号，在屏幕上\
写下这个式子“sin(u)-0.5=0”，按下求解按钮求出方程的\
解，求解用牛顿法需要较长时间，准确性和求解成功率也不一\
定很高，如果要求解简单的方程（如一元二次方程）不建议\
使用这个功能。");

}

void Controller::on_Bs2_clicked()
{
    num_base=2;
    do_keys();
    int t=(int)(double)(ans);
    string abb=tobs(t,num_base);
    ui->InputScreen->setText("");
    ui->ResultScreen->setText(QString::fromStdString(abb));
}

void Controller::on_Bs8_clicked()
{
    num_base=8;
    do_keys();
    int t=(int)(double)(ans);
    string abb=tobs(t,num_base);
    ui->InputScreen->setText("");
    ui->ResultScreen->setText(QString::fromStdString(abb));
}

void Controller::on_Bs10_clicked()
{
    num_base=10;
    do_keys();
    int t=(int)(double)(ans);
    string abb=tobs(t,num_base);
    ui->InputScreen->setText("");
    ui->ResultScreen->setText(QString::fromStdString(abb));
}

void Controller::on_Bs16_clicked()
{
    num_base=16;
    do_keys();
    int t=(int)(double)(ans);
    string abb=tobs(t,num_base);
    ui->InputScreen->setText("");
    ui->ResultScreen->setText(QString::fromStdString(abb));
}

void Controller::on_Bsn_clicked()
{
    num_base=ui->Baser->value();
    do_keys();
    int t=(int)(double)(ans);
    string abb=tobs(t,num_base);
    ui->InputScreen->setText("");
    ui->ResultScreen->setText(QString::fromStdString(abb));
}

void Controller::on_Baser_editingFinished()
{
    if (ui->Bsn->isChecked())
    {
        num_base=ui->Baser->value();
        do_keys();
        int t=(int)(double)(ans);
        string abb=tobs(t,num_base);
        ui->InputScreen->setText("");
        ui->ResultScreen->setText(QString::fromStdString(abb));
    }
}

void Controller::on_NumberA_clicked()
{
    ui->InputScreen->insert("A");
}

void Controller::on_NumberB_clicked()
{
    ui->InputScreen->insert("B");
}

void Controller::on_NumberC_clicked()
{
    ui->InputScreen->insert("C");
}

void Controller::on_NumberD_clicked()
{
    ui->InputScreen->insert("D");
}

void Controller::on_NumberE_clicked()
{
    ui->InputScreen->insert("E");
}

void Controller::on_NumberF_clicked()
{
    ui->InputScreen->insert("F");
}

void Controller::on_NumberG_clicked()
{
    ui->InputScreen->insert("G");
}

void Controller::on_NumberH_clicked()
{
    ui->InputScreen->insert("H");
}

void Controller::on_NumberI_clicked()
{
    ui->InputScreen->insert("I");
}

void Controller::on_NumberJ_clicked()
{
    ui->InputScreen->insert("J");
}


void Controller::on_NumberK_clicked()
{
    ui->InputScreen->insert("K");
}

void Controller::on_NumberL_clicked()
{
    ui->InputScreen->insert("L");
}

void Controller::on_NumberM_clicked()
{
    ui->InputScreen->insert("M");
}

void Controller::on_NumberN_clicked()
{
    ui->InputScreen->insert("N");
}

void Controller::on_NumberO_clicked()
{
    ui->InputScreen->insert("O");
}

void Controller::on_NumberP_clicked()
{
    ui->InputScreen->insert("P");
}

void Controller::on_NumberQ_clicked()
{
    ui->InputScreen->insert("Q");
}

void Controller::on_NumberR_clicked()
{
    ui->InputScreen->insert("R");
}

void Controller::on_NumberS_clicked()
{
    ui->InputScreen->insert("S");
}

void Controller::on_NumberT_clicked()
{
    ui->InputScreen->insert("T");
}

void Controller::on_NumberU_clicked()
{
    ui->InputScreen->insert("U");
}

void Controller::on_NumberV_clicked()
{
    ui->InputScreen->insert("V");
}

void Controller::on_NumberW_clicked()
{
    ui->InputScreen->insert("W");
}

void Controller::on_NumberX_clicked()
{
    ui->InputScreen->insert("Y");
}

void Controller::on_NumberZ_clicked()
{
    ui->InputScreen->insert("Z");
}

void Controller::on_PutSV_clicked()
{
    pSV.push_back(ans);
    ui->SValue->addItem(ui->SVName->text());
    ui->SVName->setText("Name");
}

void Controller::on_GetSV_clicked()
{
    int n=ui->SValue->currentRow();
    if (n<0 || n>=ui->SValue->count())
    {
        return;
    }
    ui->InputScreen->insert(QString::number((double)pSV[n]));
}

void Controller::on_DelSV_clicked()
{
    int n=ui->SValue->currentRow();
    if (n<0 || n>=ui->SValue->count())
    {
        return;
    }
    vector<Frac>::iterator it;
    for (it=pSV.begin();n--;it++){}
    pSV.erase(it);
    ui->SValue->takeItem(ui->SValue->currentRow());
}


