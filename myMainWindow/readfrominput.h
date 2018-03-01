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

private:
    Ui::readFromInput *ui;
};

#endif // READFROMINPUT_H
