#include "changeword.h"
#include "ui_changeword.h"
#include <qdebug.h>
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


void changeWord::on_changeWord_ok_btn_clicked()
{
    QString oldWord = ui->lineEdit_changeWord->text();
    QString newWord = ui->lineEdit_changeWord_2->text();
    //qDebug() << str1.length();
    //qDebug() << (str1.length() == 0);
    if (oldWord.length() == 0 || newWord.length() == 0) {
        ui->warning_info->setText("请正确输入词条！");
    } else {
        QByteArray oldWordStr = oldWord.toUtf8();
        QByteArray newWordStr = newWord.toUtf8();
        char * oldStr = oldWordStr.data();
        char * newStr = newWordStr.data();
        emit sendChangeWord(oldStr, newStr);
        ui->warning_info->setText("");
        this->hide();
    }
}

void changeWord::on_changeWord_cancel_btn_clicked()
{
    this->hide();
}
