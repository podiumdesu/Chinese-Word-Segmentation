#ifndef ADDNEWWORD_H
#define ADDNEWWORD_H

#include <QDialog>

namespace Ui {
class addNewWord;
}

class addNewWord : public QDialog
{
    Q_OBJECT

public:
    explicit addNewWord(QWidget *parent = 0);
    ~addNewWord();

private slots:
    void on_addNewWord_ok_btn_clicked();

    void on_addNewWord_cancel_btn_clicked();

signals:
    void sendAddNewWord(char * str);

private:
    Ui::addNewWord *ui;
};

#endif // ADDNEWWORD_H
