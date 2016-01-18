#-------------------------------------------------
#
# Project created by QtCreator 2013-05-22T23:23:11
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multiCal
TEMPLATE = app
#QMAKE_LIBS += -lsyszuxpinyin

SOURCES += main.cpp\
        widget.cpp \
    clickedlabel.cpp \
    chinesecalendar.cpp \
    cal_label.cpp \
    birthdaymanager.cpp \
    todolist.cpp \
    cal2.cpp \
    birthitem.cpp \
    birthdayclass.cpp

HEADERS  += widget.h \
    clickedlabel.h \
    chinesecalendar.h \
    cal2.h \
    cal_label.h \
    birthdaymanager.h \
    birthdayclass.h \
    todolist.h \
    birthitem.h \
#    syszuxpinyin.h \
#    syszuxim.h

#FORMS += \
#    syszuxpinyin.ui

RESOURCES += \
    res.qrc
