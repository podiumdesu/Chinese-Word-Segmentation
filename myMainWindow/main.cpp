
#include <QApplication>
#include <QPushButton>


// my function head files
#include "mylib.h"
#include "mystd.h"
#include "trieTree.h"


#include "addnewword.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    //Node root = createTrieTreeRoot();

    //addNewWord addNewWord;
    mainWin.initView();
//    if (addNewWord.exec() == QDialog::Accepted) {
//        addNewWord.close();
//    }





//    if (addNewWord.exec() == mainWin.accept()) {
//        addNewWord.show();

//    }

//    QPushButton button("欢迎使用中文分词系统！");
//    QObject::connect(&button, &QPushButton::clicked, &QApplication::quit);
//    button.show();

    return app.exec();

}

