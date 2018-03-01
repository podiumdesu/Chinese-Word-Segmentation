#ifndef REMOVEWORD_H
#define REMOVEWORD_H

#include <QDialog>

namespace Ui {
class removeWord;
}

class removeWord : public QDialog
{
    Q_OBJECT

public:
    explicit removeWord(QWidget *parent = 0);
    ~removeWord();

private:
    Ui::removeWord *ui;
};

#endif // REMOVEWORD_H
