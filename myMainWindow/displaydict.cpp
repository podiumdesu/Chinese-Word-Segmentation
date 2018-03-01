#include "displaydict.h"
#include "ui_displaydict.h"

displayDict::displayDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displayDict)
{
    ui->setupUi(this);
}

displayDict::~displayDict()
{
    delete ui;
}
