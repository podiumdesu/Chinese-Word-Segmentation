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

private slots:
    void on_changeWord_ok_btn_clicked();

signals:
    void sendChangeWord(char * oldWord, char * newWord);

private:
    Ui::changeWord *ui;
};

#endif // CHANGEWORD_H
