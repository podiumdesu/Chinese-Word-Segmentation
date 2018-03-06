#include "readdict.h"
#include "ui_readdict.h"
#include <QMessageBox>
#include <QTime>
#include <QDebug>
readDict::readDict(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readDict)
{
    ui->setupUi(this);
    setWindowTitle(tr("读取词典"));
}

readDict::~readDict()
{
    delete ui;
}

void readDict::on_readDict_ok_btn_clicked()
{
     QString str1 = ui->dictPath->text();
     if (str1.length() == 0) {
         ui->warning_info->setText("请正确输入路径！");
     } else {
        QByteArray ba = str1.toLatin1();
        char *c_str2 = ba.data();
        emit sendDictPath(c_str2);
        str1.append(" 读取成功，正在建立Trie树...");
        this->hide();
     }
}


void readDict::on_readDict_cancel_btn_clicked()
{
    this->hide();
}
