#include "addnewword.h"
#include "ui_addnewword.h"
#include <qdebug.h>
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
    setWindowTitle(tr("添加新词条"));

}

addNewWord::~addNewWord() {
    delete ui;
}

void addNewWord::on_addNewWord_ok_btn_clicked()
{
    QString str1 = ui->lineEdit_addNewWord->text();
    //qDebug() << str1.length();
    //qDebug() << (str1.length() == 0);
    if (str1.length() == 0) {
        ui->warning_info->setText("请正确输入词条！");
    } else {
        QByteArray ba = str1.toUtf8();
        char * c_str2 = ba.data();
        emit sendAddNewWord(c_str2);
        ui->warning_info->setText("");
        this->hide();
    }
}

void addNewWord::on_addNewWord_cancel_btn_clicked()
{
    this->hide();
}
