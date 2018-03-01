#include "readfromfile.h"
#include "ui_readfromfile.h"

readFromFile::readFromFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readFromFile)
{
    ui->setupUi(this);
}

readFromFile::~readFromFile()
{
    delete ui;
}
