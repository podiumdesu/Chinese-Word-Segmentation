#include "removeword.h"
#include "ui_removeword.h"

removeWord::removeWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removeWord)
{
    ui->setupUi(this);
}

removeWord::~removeWord()
{
    delete ui;
}
