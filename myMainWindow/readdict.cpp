#include "readdict.h"
#include "ui_readdict.h"
#include <QMessageBox>
#include <QTime>
readDict::readDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readDict)
{
    ui->setupUi(this);
}

readDict::~readDict()
{
    delete ui;
}
void readDict::on_readDict_ok_btn_clicked()
{
//    QString str;
//    QByteArray byteArray=str.toLocal8Bit ();
//    char *c=byteArray.data();
     QString str1 = ui->dictPath->text();
     QByteArray ba = str1.toLatin1();
     char *c_str2 = ba.data();
    emit sendDictPath(str1);
    this->hide();
    QMessageBox::information(this, tr("Information"), tr("读取成功，正在建立Trie树..."));

}
