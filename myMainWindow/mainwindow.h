#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initView();

private slots:
    void on_test_clicked();

    void actionAddNewWord();
    void actionRemoveWord();
    void actionChangeWord();
    void actionReadDict();
    void actionDisplayDict();
    void actionReadFromFile();
    void actionReadFromInput();
    void on_renewDict_ok_btn_clicked();

    void on_renewDict_cancel_btn_clicked();

    void getDictPath(char *);
    void getAddNewWord(char *);
    void getChangeWord(char *, char *);
    void getRemoveWord(char *);
    void getReadFromFile(char *, int, char *);

private:
   // void on_actionaddNewWord_triggered();

    Ui::MainWindow *ui;

//public slots:
//    void actionAddNewWord();
//};
};

#endif // MAINWINDOW_H
