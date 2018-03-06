#include "removeword.h"
#include "ui_removeword.h"

removeWord::removeWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::removeWord)
{
    ui->setupUi(this);
    setWindowTitle(tr("删除词条"));
}

removeWord::~removeWord()
{
    delete ui;
}

void removeWord::on_remove_ok_btn_clicked()
{
    QString str1 = ui->lineEdit_removeWord->text();
    if (str1.length() == 0) {
        ui->warning_info->setText("请正确输入词条！");
    } else {
        QByteArray ba = str1.toUtf8();
        char * c_str2 = ba.data();
        emit sendRemoveWord(c_str2);
        ui->warning_info->setText("");
        this->hide();
    }
}

void removeWord::on_remove_cancel_btn_clicked()
{
    this->hide();
}
