#-------------------------------------------------
#
# Project created by QtCreator 2018-01-06T03:53:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Library
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
    get_text_from_file.cpp \
    book.cpp \
    logging.cpp \
    db.cpp \
    library.cpp \
    book_search.cpp \
    login.cpp \
    edit.cpp

HEADERS += \
        mainwindow.h \
    get_text_from_file.h \
    book.h \
    logging.h \
    db.h \
    library.h \
    book_search.h \
    login.h \
    edit.h

FORMS += \
        mainwindow.ui \
    book.ui \
    library.ui \
    book_search.ui \
    login.ui \
    edit.ui

RESOURCES += \
    resources.qrc

DEFINES += Q_COMPILER_INITIALIZER_LISTS

CONFIG += c++11

RC_FILE = library.rc
