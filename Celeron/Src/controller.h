#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDialog>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLineEdit>
#include <QRect>
#include <iostream>
#include "fraction.h"
#include <vector>
using namespace std;
namespace Ui {
class Controller;
}

class Controller : public QDialog
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();
    void do_keys();
    void init();

private slots:
    void on_Plus_clicked();

    void on_Minus_clicked();

    void on_Multiple_clicked();

    void on_Divide_clicked();

    void on_Number1_clicked();

    void on_Number2_clicked();

    void on_Number3_clicked();

    void on_Number4_clicked();

    void on_Number5_clicked();

    void on_Number6_clicked();

    void on_Number7_clicked();

    void on_Number8_clicked();

    void on_Number9_clicked();

    void on_Number0_clicked();

    void on_Dot_clicked();

    void on_GetAnswer_clicked();

    void on_LeftSign_clicked();

    void on_RightSign_clicked();

    void on_Answer_clicked();

    void on_Sin_clicked();

    void on_Cos_clicked();

    void on_Tan_clicked();

    void on_Arcsin_clicked();

    void on_Arccos_clicked();

    void on_Arctan_clicked();

    void on_Sqr_clicked();

    void on_Tri_clicked();

    void on_Pow_clicked();

    void on_Sqrt_clicked();

    void on_Trit_clicked();

    void on_Powt_clicked();

    void on_Time_clicked();

    void on_Mixed_clicked();

    void on_Impor_clicked();

    void on_Deri_clicked();

    void on_Inte_clicked();

    void on_Y_clicked();

    void on_comma_clicked();

    void on_SetPrecision_clicked();

    void on_RandX_clicked();

    void on_RandS_clicked();

    void on_Comma2_clicked();

    void on_Delete_clicked();

    void on_Clear_clicked();

    void on_Deg_clicked();

    void on_Rad_clicked();

    void on_GetConst_clicked();

    void on_StopMusic_clicked();

    void on_ChangeMusic_clicked();

    void on_Settle_clicked();

    void on_Science_clicked();

    void on_X1_clicked();

    void on_X2_clicked();

    void on_Solve_clicked();

    void on_X3_clicked();

    void on_CLR1_clicked();

    void on_CLR2_clicked();

    void on_CLR3_clicked();

    void on_X4_clicked();

    void on_CLR4_clicked();

    void on_Base_clicked();

    void on_Bs2_clicked();

    void on_Bs8_clicked();

    void on_Bs10_clicked();

    void on_Bs16_clicked();

    void on_Bsn_clicked();

    void on_Baser_editingFinished();

    void on_NumberA_clicked();

    void on_NumberB_clicked();

    void on_NumberC_clicked();

    void on_NumberD_clicked();

    void on_NumberE_clicked();

    void on_NumberF_clicked();

    void on_NumberG_clicked();

    void on_NumberH_clicked();

    void on_NumberI_clicked();

    void on_NumberJ_clicked();

    void on_NumberK_clicked();

    void on_NumberL_clicked();

    void on_NumberM_clicked();

    void on_NumberN_clicked();

    void on_NumberO_clicked();

    void on_NumberP_clicked();

    void on_NumberQ_clicked();

    void on_NumberR_clicked();

    void on_NumberS_clicked();

    void on_NumberT_clicked();

    void on_NumberU_clicked();

    void on_NumberV_clicked();

    void on_NumberW_clicked();

    void on_NumberX_clicked();

    void on_NumberZ_clicked();

    void on_PutSV_clicked();

    void on_GetSV_clicked();

    void on_DelSV_clicked();


    void on_InteHelp_clicked();

    void on_Unknowned_clicked();

    void on_Equaled_clicked();

    void on_Clear_2_clicked();

    void on_DoSolve_clicked();

    void on_SolveHelp_clicked();

    void on_Log_clicked();

    void on_Ln_clicked();

private:
    Ui::Controller *ui;
    int prec;
    bool isPlayingMusic;
    QMediaPlayer *player;
    QRect now;
    vector<vector<QLineEdit *> > chk;
    QPushButton *base_buttons[36];
    vector<_Action::Frac> pSV;
};

#endif // CONTROLLER_H
