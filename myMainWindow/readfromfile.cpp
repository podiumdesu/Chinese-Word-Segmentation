#include "readfromfile.h"
#include "ui_readfromfile.h"
#include <QMessageBox>
#include <qdebug.h>
readFromFile::readFromFile(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::readFromFile)
{
    ui->setupUi(this);
    ui->lineEdit_saveFilePath->setPlaceholderText("输入结果的保存文件名");
    //connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(void)));

}

readFromFile::~readFromFile()
{
    delete ui;
}


void readFromFile::on_readFromFile_ok_btn_clicked()
{
    int saveOrNot = 0;
    QString str1 = ui->lineEdit_readFromFile->text();
    QString saveFileName = ui->lineEdit_saveFilePath->text();
    if (str1.length() == 0) {
        ui->warning_info->setText("请正确输入哦！");
    } else {
        QByteArray ba = str1.toLatin1();
        QByteArray ba2 = saveFileName.toLatin1();
        char *c_str2 = ba.data();
        char *saveFileName1 = ba2.data();
        if (strlen(saveFileName1) == 0) {
            saveOrNot = 0;
        } else {
            saveOrNot = 1;
        }
        emit(sendReadFromFile(c_str2, saveOrNot, saveFileName1));
        QMessageBox::information(this, tr("Information"), "文件导入完毕！");

        if (saveOrNot) {
            QMessageBox::information(this, tr("Information"), "处理结果保存完毕！");
        }
        this->hide();
    }
}

void readFromFile::on_readFromFile_cancel_btn_clicked()
{
    this->hide();
}
