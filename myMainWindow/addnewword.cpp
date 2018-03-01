#include "addnewword.h"
#include "ui_addnewword.h"

addNewWord::addNewWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewWord)
{
//    ui->pushButton->setAutoFillBackground(true);
//       QPalette testpalette = ui->pushButton->palette();
//   //    testpalette.setBrush(ui->TH_2->backgroundRole(), QBrush(QColor(255, 0, 0)));
//       testpalette.setColor(QPalette::Background, QColor(255,0,0));
//       ui->pushButton->setPalette(testpalette);
    ui->setupUi(this);
}

addNewWord::~addNewWord() {
    delete ui;
}


void addNewWord::on_pushButton_clicked()
{
    accept();
}
