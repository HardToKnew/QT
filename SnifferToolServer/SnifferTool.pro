#-------------------------------------------------
#
# Project created by QtCreator 2016-03-09T15:44:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SnifferTool
TEMPLATE = app


#-------------------------------------------------

QMAKE_CFLAGS += -std=gnu11  -D_GNU_SOURCE
QMAKE_CXXFLAGS += -std=gnu++11

#-------------------------------------------------
# WinPcap
INCLUDEPATH += $$PWD/WinPcap\Include
LIBS += -L$$PWD/WinPcap/Lib/ -lpacket -lwpcap

# WinSock
LIBS += -lws2_32
LIBS += -liphlpapi
#-------------------------------------------------
# libnet
LIBS += -L$$PWD/libnet/Lib/ -llibnet
INCLUDEPATH +=$$PWD/libnet/Include
DEPENDPATH +=$$PWD/libnet/Include
LIBS += -L$$PWD/WinPcap/libnet/Lib/ -llibnet
INCLUDEPATH += $$PWD/WinPcap\libnet\Include
#-------------------------------------------------


SOURCES += main.cpp\
        widget.cpp \
    NoFocusDelegate.cpp \
    pcapcommon.cpp \
    getmacthread.cpp \
    tcpipprotocol.cpp \
    sendpacketthread.cpp \
    receivepacketthread.cpp \
    trafficstatistic.cpp \
    filterthread.cpp \
    getallhostname.cpp \
    libping.cpp \
    syn_scan.cpp \
    portservicemap.cpp \
    aboutdialog.cpp

HEADERS  += widget.h \
    tcpipcommon.h \
    NoFocusDelegate.h \
    pcapcommon.h \
    getmacthread.h \
    tcpipprotocol.h \
    sendpacketthread.h \
    receivepacketthread.h \
    trafficstatistic.h \
    filterthread.h \
    getallhostname.h \
    libping.h \
    syn_scan.h \
    portservicemap.h \
    aboutdialog.h

FORMS    += widget.ui \
    aboutdialog.ui

DISTFILES += \
    readme.txt
