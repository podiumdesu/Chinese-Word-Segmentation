#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QDebug>
#include <qdebug.h>
#include <QString>
#include <string>
#include <fstream>
// my function head files
#include "mymain.h"

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



Node root = createTrieTreeRoot();
char dictFile[1000];
int dictHasChanged = 0;
char resolveFile[1000];
int maxLengthInDict;
QString str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return std::string(cdata);
}




// all files;
double buildDict(Node root, char * fileName) {
    char result[3000];
    FILE *fp;
    time_t start = clock();
    if ((fp = fopen(fileName, "r")) == NULL) {
        //printf("%s not open!\n", fileName);
        return WRONG;
    } else {
        //printf("读取词典成功！正在建立TRIE树......\n");
        while (fgets(result, 3000, fp) != NULL) {
            if (result[0] != '\n')
                buildTrieTree(root, result);
        }
    }
    time_t end = clock();
    //printf("Building time costs: %gs\n", (double)(end - start) / CLOCKS_PER_SEC);
    return ((double)(end - start) / CLOCKS_PER_SEC);
}

//////

int matchStringForMAX(Node root, char * resolveString, int length, int saveOrNot, char * saveFile) {   //最多传入maxLength个汉字->resolveString
    char tempStr[100];
    std::FILE *fp;
    if (saveOrNot) {
        fp = std::fopen(saveFile, "a");
    }
    my_strncpy(tempStr, resolveString, length);  //length目前有效长度
    while ((*tempStr != '\n') || (*tempStr != '\0') || (*tempStr != '\r')) {  //
        if (findNode(root, tempStr)) {
            //resolveString += letterLength(tempStr) * WORDCHAR;    //已经匹配完的剔除，对于剩下的字符串继续
            //printf("%s|", tempStr);
            if (saveOrNot) {
                qDebug() << tempStr;
                std::fprintf(fp, "%s|", tempStr);
                std::fclose(fp);
            }
            return (letterLength(tempStr) + 1);  //返回现在完成的长度
        } else { //如果目前tempStr不能匹配
            if (length == 1) { //如果现在长度为1，词典匹配失败，直接输出
                if (saveOrNot) {
                    qDebug() << tempStr;
                    std::fprintf(fp, "%s|", tempStr);
                    std::fclose(fp);
                }
                //printf("%s|", tempStr);
                return 1;
            }
            length--;
            my_strncpy(tempStr, tempStr, length);    //如果未查找到，将tempStr最后一位剔除
        }
    }
    return 0;
}

void matchUserInput(Node root, char * string, int maxLength, int fileOrNot, char * saveFile) {
    int removeLength = 0;
    std::FILE *tempFp;
    char temp[10];
    do {
        if (letterLength(string) > maxLength) {
            removeLength = matchStringForMAX(root, string, maxLength, fileOrNot, saveFile);
        } else {
            removeLength = matchStringForMAX(root, string, letterLength(string), fileOrNot, saveFile);
        }
        string += removeLength * WORDCHAR;
        //printf("now you need to resolve %s\n",string);
    } while ((*string != '\n') && (*string != '\0') && (*string != '\r'));
    if (fileOrNot) {
        tempFp = std::fopen(saveFile, "a");
        strcpy(temp, "\n");
        std::fprintf(tempFp, "%s", temp);
        fclose(tempFp);
    }
    //printf("\n");
}
int maxLength(char *fileName) {
    char result[1000];
    int maxlength = 0;
    int templen;
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("FILE: %s not open\n", fileName);
    } else {
        while(fgets(result, 10000, fp) != NULL) {
            if (result[0] != '\n') {
                templen = (int) ((strlen(result) - 1) / 3);
                // todo delete
                // printf("%d\n", templen);
                if (templen > maxlength) maxlength = templen;
            }
        }
    }
    return maxlength;
}

////share.c
void showAllContent(char * filename) {
    FILE *fp;
    char string[100];
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("FILE: %s not open\n", filename);
    } else {
        printf("****Here is the content*****\n");
        while(fgets(string,100, fp) != NULL) {
            printf("\t%s", string);
        }
        printf("****************************\n");
    }
}
char * my_strncpy(char * des, char * src, int length) {
    if (strcpy(des, src) == 0) {
        char temp[100];
        strncpy(temp, src, length * WORDCHAR);
        strncpy(des, temp, length * WORDCHAR);
    } else {
        strncpy(des, src, length * WORDCHAR);
    }
    des[length * WORDCHAR] = '\0';
    return des;
}

int letterLength(char * string) {
    return (strlen(string) - 1) / 3;
}

char * resolveInputDictName(char * string) {
    char temp[1000];
    strcpy(temp, string);
    if ((*string == 'q' || *string == 'Q') && (strlen(string) < 3)) {
        strcpy(string, temp);
        printf("仍使用%s词典文件\n", string);
    }
    free(temp);
    return string;
}

void pressAnyKeyToContinue(void) {
    printf("\n请按任意键继续...");
    getchar();
    getchar();
}

Node initTrieTreeNode(char * word, bool isWord) {
    Node pnode = (Node)malloc(sizeof(struct TrieNode));
    if (pnode) {
        strcpy(pnode->word, word);
        pnode->isWord = isWord;
        pnode->child = NULL;
        pnode->childNum = 0;
    }
    return pnode;
}

Node buildTreeNode(Node root, char *string) {
    bool isWord = *(string + 3) == '\n' || *(string + 3) == '\0' || *(string + 3) == '\r';
    char *tmpStr = charcpy(string);
    Node node = initTrieTreeNode(tmpStr, isWord);
    free(tmpStr);
    if (root->childNum == 0)
        root->child = (Node * )malloc(sizeof(struct TrieNode));
    else
        root->child = (Node * )realloc(root->child, sizeof(struct TrieNode) * (root->childNum + 1));
    root->child[root->childNum] = node;
    root->childNum++;
    return node;
}

Node updateTreeNode(Node node, char *string) {
    if (node->isWord == false)
        node->isWord = *(string + 3) == '\n' || *(string + 3) == '\0' || *(string + 3) == '\r';
    return node;
}

void buildTrieTree(Node root, char * string) {
    while((*string != '\0') && (*string != '\n') && (*string != '\r'))  {    // whether it is a whole word
        Node child;
        bool found = false;
        char *tmpStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if (root->child[i] && (strcmp(root->child[i]->word,tmpStr) == 0)) {
                found = true;
                child = updateTreeNode(root->child[i], string);
            }
        }
        free(tmpStr);
        if (!found)
            child = buildTreeNode(root, string);
        root = child;
        string += 3;
    }
}

Node createTrieTreeRoot() {
    Node root = initTrieTreeNode("root", false);
    return root;
}

char * charcpy(char * str) {
    char * tmpStr = (char *)malloc(sizeof(char) * 4);
    strncpy(tmpStr, str, 3);
    tmpStr[3] = '\0';
    return tmpStr;
}

bool findNode (Node root, char * string) {
    bool found = false;
    Node child;
    while((*string != '\r') && (*string != '\n') && (*string != '\0') && (*string)) {// whether it is a whole word
        char *tempStr = charcpy(string);
        for (int i = 0; i < root->childNum; i++) {
            if ((root->child[i]) && strcmp(root->child[i]->word, tempStr) == 0) {
                child = root->child[i];
                root = child;
                found = true;
                break;
            } else {
                found = false;
                if (i == root->childNum - 1) {
                    return found;
                }
            }
        }
        string += 3;
        if (((*string != '\r') && (*string != '\n') && (*string != '\0')) && (root->childNum == 0)) {
            found = false;
            free(tempStr);
            break;
        }
        free(tempStr);
    }
    if (!found) {
        return false;
    } else {
        return (root->isWord) ? true : false;
    }
}

status addNewNode (Node root, char * string, char * fileName) {
    FILE *fp;
    if ((fp = fopen(fileName, "a")) == NULL) {
        qDebug() << "addNewNode: File open wrong";
        //printf("FILE: open %s wrong", fileName);
        return WRONG;
    } else {
        buildTrieTree(root, string);
        //todo inspect the end of the file to add '\n'
        fwrite(string, 3*sizeof(char), strlen(string) / 3, fp);
        fwrite("\n", sizeof(char), 1, fp);
        fclose(fp);
        printf("%s 添加成功\n", string);
        return OK;
    }

}

void Delete(char* filename, int n){
    FILE *fp1, *fp2;
    char c[100];
    int del_line, temp = 1;
    fp1 = fopen(filename, "r");
    del_line = n;
    fp2 = fopen("temp.txt", "w");
    while (fgets(c, 100, fp1) != NULL) {
        if (temp != del_line) {
            fputs(c, fp2);
        }
        temp++;
    }
    fputs("\n", fp2);
    fclose(fp1);
    fclose(fp2);
    //remove original file
    remove(filename);
    //rename the file temp.txt to original name
    rename("temp.txt", filename);
}

status removeNode (Node root, char * string, char * fileName) {
    Node test;
    test = root;
    FILE *fp;
    char result[100];
    int rowNum = 1;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("FILE: %s not open\n", fileName);
        return WRONG;
    } else {
        while(fgets(result, 100, fp) != NULL) {
            result[strlen(result) - 1] ='\0';
            if (strcmp(result, string) == 0) {
                //printf("%s row num is: %d\n", string , rowNum);
                break;
            }
            rowNum++;
        }
        QString qString;
        qString = QString(str2qstr(std::string("删除词条的行数在 %1 行"))).arg(rowNum);
        //printf("%d\n", rowNum);
        Delete(fileName, rowNum);
        //printf("REMOVE DONE\n");
        return OK;
    }

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("欢迎使用中文分词系统"));
    ui->setupUi(this);
    //remove(ui->renewDict);
    ui->renewDict->hide();
    ui->textEdit->hide();
    connect(ui->actionaddNewWord, SIGNAL(triggered()), this, SLOT(actionAddNewWord()));
    connect(ui->actionremoveWord, SIGNAL(triggered()), this, SLOT(actionRemoveWord()));
    connect(ui->actionchangeWord, SIGNAL(triggered()), this, SLOT(actionChangeWord()));
    connect(ui->actionreadDict, SIGNAL(triggered()), this, SLOT(actionReadDict()));
    //connect(ui->actiondisplayDict, SIGNAL(triggered()), this, SLOT(actionDisplayDict()));
    connect(ui->actionreadFromFile, SIGNAL(triggered()), this, SLOT(actionReadFromFile()));
    connect(ui->actionreadFromInput, SIGNAL(triggered()), this, SLOT(actionReadFromInput()));
}

void MainWindow::initView()
{
    QMainWindow *mainWin = new MainWindow;

    setWindowTitle(tr("欢迎使用中文分词系统"));
    ui->renewDict->setHidden(true);   // use `setHidden` to hide components
    ui->update_info->setHidden(true);

    ui->setupUi(this);
    ui->textEdit->hide();

    mainWin->show();
    // add signals and slots
    connect(ui->actionaddNewWord, SIGNAL(triggered()), this, SLOT(actionAddNewWord()));
    connect(ui->actionremoveWord, SIGNAL(triggered()), this, SLOT(actionRemoveWord()));
    connect(ui->actionchangeWord, SIGNAL(triggered()), this, SLOT(actionChangeWord()));
    connect(ui->actionreadDict, SIGNAL(triggered()), this, SLOT(actionReadDict()));
   // connect(ui->actiondisplayDict, SIGNAL(triggered()), this, SLOT(actionDisplayDict()));
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
    connect(wdg_removeWord, SIGNAL(sendRemoveWord(char *)), this , SLOT(getRemoveWord(char *)));
    wdg_removeWord->show();
}

void MainWindow::actionChangeWord(){
    QWidget *wdg_changeWord = new changeWord;
    connect(wdg_changeWord, SIGNAL(sendChangeWord(char *, char * )), this , SLOT(getChangeWord(char *, char *)));
    wdg_changeWord->show();
}

void MainWindow::actionReadDict(){
    QWidget *wdg_readDict = new readDict;
    //MyDialog *dlg = new MyDialog(this);
    // 将对话框中的自定义信号与主界面中的自定义槽进行关联
    connect(wdg_readDict,SIGNAL(sendDictPath(char *)),this,SLOT(getDictPath(char *)));
    wdg_readDict->show();
}

//void MainWindow::actionDisplayDict(){
//    QWidget *wdg_displayDict = new displayDict;
//    wdg_displayDict->show();
//}
void MainWindow::actionReadFromFile(){
    QWidget *wdg_readFromFile = new readFromFile;
    connect(wdg_readFromFile, SIGNAL(sendReadFromFile(char *, int , char *)), this, SLOT(getReadFromFile(char *, int, char *)));
    wdg_readFromFile->show();
}
void MainWindow::actionReadFromInput(){
    QWidget *wdg_readFromInput = new readFromInput;
    qDebug() << "ds";
    connect(wdg_readFromInput, SIGNAL(sendReadFromInput(char *, int, char *)), this, SLOT(getReadFromInput(char*,int,char*)));
    qDebug() << "dss";
    wdg_readFromInput->show();
}


// menu 1 item 1    add new word
void MainWindow::getAddNewWord(char * newWord) {
    if (findNode(root, newWord) == true) {
        QMessageBox::information(this, tr("Information"), "该词已经在词典中了哦，请勿重复添加！");
    } else {
        if (addNewNode(root, newWord, dictFile) == WRONG) {
            QMessageBox::information(this, tr("Information"), "打开词典失败！请重新加载词典！");
        } else {
            QMessageBox::information(this, tr("Information"), QString(str2qstr(std::string("%1 添加成功！"))).arg(newWord));
            ui->renewDict->show();
        }
    }
}

void MainWindow::getRemoveWord(char * removeWord) {
    qDebug() << tr(removeWord);
    if (findNode(root, removeWord) == false) {
        QMessageBox::information(this, tr("Information"), "该词不在词典中哦");
    } else {
        if (removeNode(root, removeWord, dictFile) == WRONG) {
            QMessageBox::information(this, tr("Information"), "打开词典失败！请重新加载词典！");
        } else {
            QMessageBox::information(this, tr("Information"), QString(str2qstr(std::string("%1 删除成功！"))).arg(removeWord));
            ui->renewDict->show();
        }
    }
}

void MainWindow::getChangeWord(char * oldWord, char * newWord) {
    qDebug() << tr(oldWord);
    qDebug() << tr(newWord);
    if (findNode(root, oldWord) == false) {
        QString qString = QString(str2qstr(std::string("%1 不在词典中哦"))).arg(oldWord);
        QMessageBox::information(this, tr("Information"), qString);
    } else {
        if (findNode(root, newWord) == true) {
            QMessageBox::information(this, tr("Information"), "操作无效，想要替换的词已经在词典中了哦");
        } else {
            removeNode(root, oldWord, dictFile);
            addNewNode(root, newWord, dictFile);
            QString qString = QString(str2qstr(std::string("%1 已成功替换为 %2"))).arg(oldWord).arg(newWord);
            QMessageBox::information(this, tr("Information"), qString);
            ui->renewDict->show();
        }
    }
}

void MainWindow::getDictPath(char *value) {
    strcpy(dictFile, value);
    QString qString;
    qString.append(value);
    double time;
    if ((time = buildDict(root, value)) == WRONG) {
        QMessageBox::information(this, tr("Information"), "读取词典失败，请正确输入路径！");
        QWidget *wdg_readDict = new readDict;
        wdg_readDict->show();

    } else {
        QString qString;
        qDebug() << time;
        maxLengthInDict = maxLength(dictFile);
        qString = QString(str2qstr(std::string("词典树构建成功，共计构建时间：%1s"))).arg(time);
        QMessageBox::information(this, tr("Information"), qString);
    }
}

void MainWindow::getReadFromFile(char * resolveFilePath, int saveOrNot, char * saveFile) {
    ui->textEdit->show();

    QString qString2 = QString(str2qstr(std::string("词典树构建成功，共计构建时间：%1s"))).arg(strlen("你好"));
    qDebug() << qString2;

    char result[10000];
    int fgets_count = 0;
    qDebug() << tr(resolveFilePath);
    qDebug() << tr(saveFile);

    QString qString = QString(str2qstr(std::string("%1"))).arg(saveOrNot);
    qDebug() << qString;
    saveOrNot = 1;  //先保存成临时文件
    qDebug() << qString;
    std::ifstream fin(resolveFilePath);
    const int LINE_LENGTH = 10000;
    char str[LINE_LENGTH];

    if (strlen(saveFile) == 0) {
        saveOrNot = 0;
    } else {
        saveOrNot = 1;
    }
    int temp = 1;
    if (saveOrNot) {
        remove(saveFile);
    } else {
        temp ^= saveOrNot;
        saveOrNot ^= temp;
        temp ^= saveOrNot;
        saveFile = (char *)malloc(sizeof(char) * 200);
        strcpy(saveFile, "/Users/petnakanojo/c_design/tempSave.txt");
    }
    while(fin.getline(str,LINE_LENGTH) )
    {
        str[strlen(str) + 1] = '\0';
        str[strlen(str)] = '\n';
        matchUserInput(root, str, maxLengthInDict, saveOrNot, saveFile);
    }
    fin.close();
    std::ifstream t;
    int length;
    t.open(saveFile);      // open input file
    t.seekg(0, std::ios::end);    // go to the end
    length = t.tellg();           // report location (this is the length)
    t.seekg(0, std::ios::beg);    // go back to the beginning
    char buffer[length];    // allocate memory for a buffer of appropriate dimension
    t.read(buffer, length);       // read the whole file into the buffer
    t.close();                    // close file handle
    //ui->plainTextEdit->setPlainText(tr(buffer));
    buffer[length] = '\0';
    ui->textEdit->setText(tr(buffer));
    saveOrNot = temp;
    qDebug() << buffer;
    if (saveOrNot == 0) {
        remove(saveFile);
    }

}

void MainWindow::getReadFromInput(char * string, int saveOrNot, char * saveFile) {
    ui->textEdit->show();

    qDebug() << saveFile;
    char input[10000];
    char str[10000];
    int LINE_LENGTH = 10000;
    std::FILE * fp;
    char tempFile[100] = "/Users/petnakanojo/c_design/tempFile.txt";
    fp = std::fopen(tempFile, "w+");
    std::fprintf(fp, "%s", string);
    std::fclose(fp);

    std::ifstream fin(tempFile);

    int temp = 1;
    if (saveOrNot) {
        remove(saveFile);
    } else {
        temp ^= saveOrNot;
        saveOrNot ^= temp;
        temp ^= saveOrNot;
        saveFile = (char *)malloc(sizeof(char) * 200);
        strcpy(saveFile, "/Users/petnakanojo/c_design/tempSave.txt");
    }
    qDebug() <<"saveFile done";
    qDebug() << saveFile;
    while(fin.getline(str,LINE_LENGTH) )
    {
        //qDebug() << str;
        str[strlen(str) + 1] = '\0';
        str[strlen(str)] = '\n';
       // qDebug() << str;
        matchUserInput(root, str, maxLengthInDict, saveOrNot, saveFile);
    }
    fin.close();
    qDebug() << "fin.close";

    std::ifstream t;
    int length;
    t.open(saveFile);      // open input file
    t.seekg(0, std::ios::end);    // go to the end
    length = t.tellg();           // report location (this is the length)
    t.seekg(0, std::ios::beg);    // go back to the beginning
    char buffer[length];    // allocate memory for a buffer of appropriate dimension
    t.read(buffer, length);       // read the whole file into the buffer
    t.close();                    // close file handle
    //ui->plainTextEdit->setPlainText(tr(buffer));
    buffer[length] = '\0';
    ui->textEdit->setText(tr(buffer));
    qDebug() << buffer;
    saveOrNot = temp;
    if (saveOrNot == 0) {
        remove(saveFile);
    }
}

// 当词典出现修改时，是否重新生成Trie树
void MainWindow::on_renewDict_ok_btn_clicked()
{
    ui->renewDict->hide();
    ui->update_info->show();
    ui->update_info->setText(tr("正在更新......"));
    free(root);
    root = createTrieTreeRoot();
    buildDict(root, dictFile);
    maxLengthInDict = maxLength(dictFile);
    ui->update_info->setText("");
}

void MainWindow::on_renewDict_cancel_btn_clicked()
{
    ui->renewDict->hide();
    ui->update_info->hide();
}
