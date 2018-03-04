#ifndef READFROMFILE_H
#define READFROMFILE_H

#include <QDialog>

namespace Ui {
class readFromFile;
}

class readFromFile : public QDialog
{
    Q_OBJECT

public:
    explicit readFromFile(QWidget *parent = 0);
    ~readFromFile();

private slots:
    void on_readFromFile_ok_btn_clicked();
    int onStateChanged(void);

    void on_readFromFile_cancel_btn_clicked();

signals:
    void sendReadFromFile(char *, int, char *);
    void stateChanged(int);

private:
    Ui::readFromFile *ui;
};

#endif // READFROMFILE_H
