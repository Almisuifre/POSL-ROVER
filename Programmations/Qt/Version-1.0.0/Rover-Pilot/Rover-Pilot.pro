#-------------------------------------------------
#
# Project created by QtCreator 2015-06-14T14:30:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rover-Pilot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    communicationserie.cpp \
    pilotagemoteurs.cpp \
    pilotageplateau.cpp \
    pilotagerover.cpp

HEADERS  += mainwindow.h \
    communicationserie.h \
    pilotagemoteurs.h \
    pilotageplateau.h \
    pilotagerover.h

FORMS    += mainwindow.ui \
    communicationserie.ui \
    pilotagemoteurs.ui \
    pilotageplateau.ui \
    pilotagerover.ui

RESOURCES += \
    ressources.qrc

DISTFILES +=
