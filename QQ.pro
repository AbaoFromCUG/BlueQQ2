#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T13:01:34
#
#-------------------------------------------------

QT       += core gui
QT      +=network
QT      +=qml
QT += quickwidgets
QT   +=sql
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QQ
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    aimdialog.cpp \
    datamanager.cpp \
    downimg.cpp \
    groupbar.cpp \
    leftbar.cpp \
    listItem.cpp \
    logindialog.cpp \
    loginnetworkmanager.cpp \
    main.cpp \
    mydialogmanager.cpp \
    mylabel.cpp \
    mynetworkcookiejar.cpp \
    mynetworker.cpp \
    popup.cpp \
    talkview.cpp \
    threadmanager.cpp \
    topbar.cpp \
    welcomedialog.cpp \
    lib/framelesshelper.cpp \
    message/chatmessageinfo.cpp \
    message/databaseoperation.cpp \
    message/messagemanager.cpp \
    message/messageitem.cpp



HEADERS += \
    aimdialog.h \
    datamanager.h \
    downimg.h \
    groupbar.h \
    leftbar.h \
    listitem.h \
    logindialog.h \
    loginnetworkmanager.h \
    mydialogmanager.h \
    mylabel.h \
    mynetworkcookiejar.h \
    mynetworker.h \
    popup.h \
    talkview.h \
    threadmanager.h \
    topbar.h \
    welcomedialog.h \
    lib/framelesshelper.h \
    message/chatmessageinfo.h \
    message/databaseoperation.h \
    message/messagemanager.h \
    message/messageitem.h




FORMS += \
    aimdialog.ui \
    groupbar.ui \
    leftbar.ui \
    listitem.ui \
    logindialog.ui \
    maindialog.ui \
    popup.ui \
    talkview.ui \
    topbar.ui \
    welcomedialog.ui


RESOURCES += \
    res.qrc \
    qml.qrc

SUBDIRS += \
    QQ.pro

DISTFILES += \
    qml/ChatMessageInfo/FriendInfo.qml
