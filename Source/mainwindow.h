#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void setshift();
    void init(bool);
    void minus1s();

    void on_Number0_clicked();

    void on_Number1_clicked();

    void on_Number2_clicked();

    void on_Number3_clicked();

    void on_Number4_clicked();

    void on_Number5_clicked();

    void on_Number6_clicked();

    void on_Number7_clicked();

    void on_Number8_clicked();

    void on_Number9_clicked();

    void on_Dot_clicked();

    void on_Plus_clicked();

    void on_Minus_clicked();

    void on_Multiple_clicked();

    void on_Divide_clicked();

    void on_Del_clicked();

    void on_Ac_clicked();

    void on_Shift_clicked();

    void on_On_clicked();

    void on_LeftSign_clicked();

    void on_RightSign_clicked();

    void on_GetAnswer_clicked();

    void on_Const_clicked();

    void on_Sin_clicked();

    void on_Cos_clicked();

    void on_Tan_clicked();

    void on_Log_clicked();

    void on_Ln_clicked();

    void on_Charge_clicked();

    void on_About_clicked();

    void on_Answer_clicked();

    void on_SetPrecision_clicked();

    void on_Square_clicked();

    void on_Power_clicked();

    void on_Inverse_clicked();

    void on_Radical_clicked();

    void on_E_pi_clicked();

    void on_TimeFormat_clicked();

    void on_Fraction_clicked();

    void on_Negative_clicked();

    void on_Memory_clicked();

    void on_Integral_clicked();

    void on_Y_clicked();

    void on_Rand_clicked();

    void on_More_clicked();

    void on_StopMedia_clicked();

    bool eventFilter(QObject *, QEvent *);
    void on_ChangeMedia_clicked();

protected:
    void paintEvent(QPaintEvent *event);
public slots:
    void on_Active_clicked();
    void doplay();
private:
    Ui::MainWindow *ui;  
    Dialog dialog;
};

#endif // MAINWINDOW_H
