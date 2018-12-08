#-------------------------------------------------
#
# Project created by QtCreator 2013-04-22T14:23:15
#
#-------------------------------------------------

QT       += core gui

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HWStatus
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    hwstatusrequester.cpp \
    treemodel.cpp \
    treeitem.cpp

HEADERS  += widget.h \
    hwstatusrequester.h \
    treemodel.h \
    treeitem.h

FORMS    += widget.ui

INCLUDEPATH += ../../include/
INCLUDEPATH += ../../icore/

DEFINES += __x86__
unix {
    DEFINES += __OS_VERSION__=2 \
        __linux__
    OMNIBASE = /usr/local
    INCLUDEPATH += /usr/include/omniORB4 \
        /usr/include/COS
    LIBS += -L../../lib \
        -licore
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}
win32 {
    INCLUDEPATH += $$(OMNIORB_BASE)/include/
    DEFINES += __WIN32__ \
        WIN32 \
        _WIN32_WINNT=0x0400 \
        __NT__ \
        __OSVERSION__=4
    LIBS += -L$$(OMNIORB_BASE)/lib/x86_win32/ \
        -lomniDynamic4_rt \
        -lomniORB4_rt \
        -lomnithread_rt
    LIBS += ../../lib/icore.lib
    MOC_DIR = _moc
    OBJECTS_DIR = _obj
}
