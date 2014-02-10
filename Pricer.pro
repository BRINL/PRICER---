#-------------------------------------------------
#
# Project created by QtCreator 2013-07-25T20:43:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = scrollbar-axis-range-control
TEMPLATE = app


SOURCES += main.cpp\
    ../../qcustomplot.cpp \
    MonteCarlo.cpp \
    PayOff.cpp \
    Genealeatoire.cpp \
    Simu.cpp \
    Mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += \
    ../../qcustomplot.h \
    MonteCarlo.h \
    PayOff.h \
    Genealeatoire.h \
    Simu.h \
    Mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
