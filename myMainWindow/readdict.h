#ifndef READDICT_H
#define READDICT_H

#include <QDialog>

namespace Ui {
class readDict;
}

class readDict : public QDialog
{
    Q_OBJECT

public:
    explicit readDict(QWidget *parent = 0);
    ~readDict();

private slots:
    void on_readDict_ok_btn_clicked();

signals:
    void sendDictPath(QString);

private:
    Ui::readDict *ui;
};

#endif // READDICT_H
