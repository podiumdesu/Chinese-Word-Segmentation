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
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(void)));

}

readFromFile::~readFromFile()
{
    delete ui;
}

//void MyWidget::someSlot() {
//  QMessageBox::StandardButton reply;
//  reply = QMessageBox::question(this, "Test", "Quit?",
//                                QMessageBox::Yes|QMessageBox::No);
//  if (reply == QMessageBox::Yes) {
//    qDebug() << "Yes was clicked";
//    QApplication::quit();
//  } else {
//    qDebug() << "Yes was *not* clicked";
//  }
//}

int readFromFile::onStateChanged(void) {
    int state;
    if (state == Qt::Checked) {
        return 1;
    } else {
        return 0;
    }
}
void readFromFile::on_readFromFile_ok_btn_clicked()
{
    int saveOrNot = 0;
    QString str1 = ui->lineEdit_readFromFile->text();
    QString saveFileName = ui->lineEdit_saveFilePath->text();
    if (str1.length() == 0) {
        ui->warning_info->setText("请正确输入路径！");
    } else {
        QByteArray ba = str1.toLatin1();
        QByteArray ba2 = saveFileName.toLatin1();
        char *c_str2 = ba.data();
        char *saveFileName = ba2.data();
//        QMessageBox::StandardButton reply;
//        reply = QMessageBox::question(this, "Test", "保存成文件？", QMessageBox::Yes|QMessageBox::No);
//        if (reply == QMessageBox::Yes) {
//            qDebug() << "Yes was clicked";
//        } else {
//            qDebug() << "Yes was *not* clicked";
//        }
        if (onStateChanged() == 1) {
            saveOrNot = 1;
            qDebug() << "yes";
        }
        emit(sendReadFromFile(c_str2, saveOrNot, saveFileName));
        QMessageBox::information(this, tr("Information"), "处理文件导入完毕");
        this->hide();
    }
}

void readFromFile::on_readFromFile_cancel_btn_clicked()
{
    this->hide();
}
