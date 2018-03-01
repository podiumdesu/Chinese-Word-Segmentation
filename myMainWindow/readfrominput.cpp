#include "readfrominput.h"
#include "ui_readfrominput.h"

readFromInput::readFromInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readFromInput)
{
    ui->setupUi(this);
}

readFromInput::~readFromInput()
{
    delete ui;
}
