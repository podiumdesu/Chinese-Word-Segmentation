#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T23:27:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myMainWindow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addnewword.cpp \
    removeword.cpp \
    changeword.cpp \
    readdict.cpp \
    displaydict.cpp \
    readfromfile.cpp \
    readfrominput.cpp \
    test.cpp

HEADERS += \
        mainwindow.h \
    addnewword.h \
    removeword.h \
    changeword.h \
    readdict.h \
    displaydict.h \
    readfromfile.h \
    readfrominput.h \
    test.h \
    mymain.h

FORMS += \
        mainwindow.ui \
    addnewword.ui \
    removeword.ui \
    changeword.ui \
    readdict.ui \
    displaydict.ui \
    readfromfile.ui \
    readfrominput.ui

RESOURCES += \
    actions/imgs.qrc \
    actions/myimages.qrc

LIBS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -mmacosx-version-min=10.13
QMAKE_LFLAGS += -mmacosx-version-min=10.13
