#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QDebug>
#include <qdebug.h>
// my function head files
#include "mylib.h"
#include "mystd.h"
#include "trieTree.h"
#include "test.h"

// ui head files
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addnewword.h"
#include "removeword.h"
#include "changeword.h"
#include "readdict.h"
#include "displaydict.h"
#include "readfromfile.h"
#include "readfrominput.h"

//Node root = createTrieTreeRoot();
char dictFile[1000];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("欢迎使用中文分词系统"));
    ui->setupUi(this);
    connect(ui->actionaddNewWord, SIGNAL(triggered()), this, SLOT(actionAddNewWord()));
    connect(ui->actionremoveWord, SIGNAL(triggered()), this, SLOT(actionRemoveWord()));
    connect(ui->actionchangeWord, SIGNAL(triggered()), this, SLOT(actionChangeWord()));
    connect(ui->actionreadDict, SIGNAL(triggered()), this, SLOT(actionReadDict()));
    connect(ui->actiondisplayDict, SIGNAL(triggered()), this, SLOT(actionDisplayDict()));
    connect(ui->actionreadFromFile, SIGNAL(triggered()), this, SLOT(actionReadFromFile()));
    connect(ui->actionreadFromInput, SIGNAL(triggered()), this, SLOT(actionReadFromInput()));
//    QWidget *wdg_readDict = new readDict;
//    //MyDialog *dlg = new MyDialog(this);
//    // 将对话框中的自定义信号与主界面中的自定义槽进行关联
//    connect(wdg_readDict,SIGNAL(sendDictPath(char *)),this,SLOT(getDictPath(char*)));
}

void MainWindow::initView()
{
    QMainWindow *mainWin = new MainWindow;

    setWindowTitle(tr("欢迎使用中文分词系统"));
    ui->renewDict->setHidden(true);   // use `setHidden` to hide components
    ui->update_info->setHidden(true);
    ui->setupUi(this);
    mainWin->show();
    // add signals and slots
    connect(ui->actionaddNewWord, SIGNAL(triggered()), this, SLOT(actionAddNewWord()));
    connect(ui->actionremoveWord, SIGNAL(triggered()), this, SLOT(actionRemoveWord()));
    connect(ui->actionchangeWord, SIGNAL(triggered()), this, SLOT(actionChangeWord()));
    connect(ui->actionreadDict, SIGNAL(triggered()), this, SLOT(actionReadDict()));
    connect(ui->actiondisplayDict, SIGNAL(triggered()), this, SLOT(actionDisplayDict()));
    connect(ui->actionreadFromFile, SIGNAL(triggered()), this, SLOT(actionReadFromFile()));
    connect(ui->actionreadFromInput, SIGNAL(triggered()), this, SLOT(actionReadFromInput()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::actionAddNewWord() {
    QWidget *wdg_addNewWord = new addNewWord;
    connect(wdg_addNewWord,SIGNAL(sendAddNewWord(char *)),this,SLOT(getAddNewWord(char*)));
    wdg_addNewWord->show();
}
void MainWindow::actionRemoveWord(){
    QWidget *wdg_removeWord = new removeWord;
    wdg_removeWord->show();

}
void MainWindow::actionChangeWord(){
    QWidget *wdg_changeWord = new changeWord;
    qDebug() << tr("dddd");
    connect(wdg_changeWord, SIGNAL(sendChangeWord(char * oldWord, char * newWord)), this , SLOT(getChangeWord(char * oldWord, char * newWord)));
    qDebug() << tr("dddd");

    wdg_changeWord->show();
}

void MainWindow::actionReadDict(){
    QWidget *wdg_readDict = new readDict;
    //MyDialog *dlg = new MyDialog(this);
    // 将对话框中的自定义信号与主界面中的自定义槽进行关联
    connect(wdg_readDict,SIGNAL(sendDictPath(char *str)),this,SLOT(getDictPath(char * str)));
    wdg_readDict->show();
}

void MainWindow::actionDisplayDict(){
    QWidget *wdg_displayDict = new displayDict;
    wdg_displayDict->show();
}
void MainWindow::actionReadFromFile(){
    QWidget *wdg_readFromFile = new readFromFile;
    wdg_readFromFile->show();
}
void MainWindow::actionReadFromInput(){
    QWidget *wdg_readFromInput = new readFromInput;
    wdg_readFromInput->show();
}

void MainWindow::on_test_clicked()
{
    QWidget *wdg = new addNewWord;
    wdg->show();
    ui->renewDict->hide();
    ui->update_info->setText(tr("更新词典完毕"));
}

// menu 1 item 1    add new word
void MainWindow::getAddNewWord(char * newWord) {
    QString qString;
    qString.append(newWord);
    qDebug() << qString;
}

void MainWindow::getChangeWord(char * oldWord, char * newWord) {
    QString oldQstring, newQstring;
    qDebug() << tr(oldWord);
    qDebug() << tr(newWord);
}

void MainWindow::getDictPath(char *value) {
    strcpy(dictFile, value);
    QString qString;
    qString.append(value);
    qDebug()<<tr(value);
    qDebug()<<tr(dictFile);

    // qDebug()<<tr(str);
    ui->renewDict->hide();
    ui->update_info->show();
    ui->update_info->setText(tr("正在更新......"));
}

void MainWindow::on_renewDict_ok_btn_clicked()
{
    ui->renewDict->hide();
    ui->update_info->show();
    ui->update_info->setText(tr("正在更新......"));
}

void MainWindow::on_renewDict_cancel_btn_clicked()
{
    ui->renewDict->hide();
    ui->update_info->hide();
}


