#ifndef CHANGEWORD_H
#define CHANGEWORD_H

#include <QDialog>

namespace Ui {
class changeWord;
}

class changeWord : public QDialog
{
    Q_OBJECT

public:
    explicit changeWord(QWidget *parent = 0);
    ~changeWord();

private:
    Ui::changeWord *ui;
};

#endif // CHANGEWORD_H
