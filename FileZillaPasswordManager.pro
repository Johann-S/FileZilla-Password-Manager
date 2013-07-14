#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T19:10:17
#
#-------------------------------------------------

QT       += core gui

TARGET = FileZillaPasswordManager
TEMPLATE = app


SOURCES += main.cpp\
        qmanager.cpp \
    threadxml.cpp \
    editdialog.cpp \
    editthreadxml.cpp \
    suppthread.cpp \
    displaythread.cpp

HEADERS  += qmanager.h \
    threadxml.h \
    editdialog.h \
    editthreadxml.h \
    suppthread.h \
    displaythread.h

FORMS    += qmanager.ui \
    editdialog.ui


LIBS += tinyxml.lib

RESOURCES += \
    resources.qrc
