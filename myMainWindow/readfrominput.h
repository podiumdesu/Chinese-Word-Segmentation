#ifndef READFROMINPUT_H
#define READFROMINPUT_H

#include <QDialog>

namespace Ui {
class readFromInput;
}

class readFromInput : public QDialog
{
    Q_OBJECT

public:
    explicit readFromInput(QWidget *parent = 0);
    ~readFromInput();

private slots:
    void on_readFromInput_cancel_btn_clicked();

    void on_readFromInput_ok_btn_clicked();

signals:
    void sendReadFromInput(char *, int , char *);

private:
    Ui::readFromInput *ui;
};

#endif // READFROMINPUT_H
