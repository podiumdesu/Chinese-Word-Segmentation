#ifndef DISPLAYDICT_H
#define DISPLAYDICT_H

#include <QDialog>

namespace Ui {
class displayDict;
}

class displayDict : public QDialog
{
    Q_OBJECT

public:
    explicit displayDict(QWidget *parent = 0);
    ~displayDict();

private:
    Ui::displayDict *ui;
};

#endif // DISPLAYDICT_H
