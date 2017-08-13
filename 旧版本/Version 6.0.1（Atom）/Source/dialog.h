#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void MakeItActive();
    void on_Confirm_clicked();
    void on_Cancel_clicked();

    void on_commandLinkButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
