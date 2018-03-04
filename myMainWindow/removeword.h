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

signals:
    void sendRemoveWord(char * str);

private slots:
    void on_remove_ok_btn_clicked();

    void on_remove_cancel_btn_clicked();

private:
    Ui::removeWord *ui;
};



#endif // REMOVEWORD_H
