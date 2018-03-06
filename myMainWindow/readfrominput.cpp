#include "readfrominput.h"
#include "ui_readfrominput.h"
#include <qdebug.h>
#include <qmessagebox.h>

readFromInput::readFromInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readFromInput)
{

    ui->setupUi(this);
    setWindowTitle(tr("手动输入"));
    ui->textEdit_readFromInput->setPlaceholderText("输入想要处理的段落");
    ui->lineEdit_saveReadFromInput->setPlaceholderText("输入结果的保存文件名");

}

readFromInput::~readFromInput()
{
    delete ui;
}

void readFromInput::on_readFromInput_cancel_btn_clicked()
{
    this->hide();
}

void readFromInput::on_readFromInput_ok_btn_clicked()
{
    int saveOrNot = 0;
    QString str1 = ui->textEdit_readFromInput->toPlainText();
    QString str2 = ui->lineEdit_saveReadFromInput->text();
    qDebug() << str1;
    QByteArray ba = str1.toUtf8();
    QByteArray ba2 = str2.toLatin1();
    char * string = ba.data();
    char * saveFilePath = ba2.data();
    if (strlen(saveFilePath) == 0) {
        saveOrNot = 0;
    } else {
        saveOrNot = 1;
    }
    emit(sendReadFromInput(string, saveOrNot, saveFilePath));
    if (saveOrNot) {
        QMessageBox::information(this, tr("Information"), "文件已经保存完毕");
    }
    this->hide();
}
