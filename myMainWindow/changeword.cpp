#include "changeword.h"
#include "ui_changeword.h"

changeWord::changeWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeWord)
{
    ui->setupUi(this);
}

changeWord::~changeWord()
{
    delete ui;
}
