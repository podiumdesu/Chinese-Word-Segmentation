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

private:
    Ui::readFromFile *ui;
};

#endif // READFROMFILE_H
