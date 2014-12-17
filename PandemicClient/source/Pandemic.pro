#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T19:09:58
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = Pandemic
TEMPLATE = app
CONFIG   += console

#QMAKE_LFLAGS += /MANIFESTUAC:"uiAccess='true'level='requireAdministrator'"



SOURCES += main.cpp \
    core/application.cpp \
    server/server.cpp \
    server/socket.cpp

HEADERS += \
    core/application.h \
    server/server.h \
    server/socket.h
