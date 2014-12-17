#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T21:56:08
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = PandemicAdministrator
TEMPLATE = app
CONFIG += console

#require admin use
#QMAKE_LFLAGS += /MANIFESTUAC:"uiAccess='true'level='requireAdministrator'"

SOURCES += main.cpp \
    api/pandemicmodulebase.cpp \
    api/pandemicmodule.cpp \
    api/pandemicwindow.cpp \
    core/applicationbase.cpp \
    core/application.cpp \
    gui/mainwindow.cpp \
    server/connection.cpp \
    server/server.cpp \
    widgets/taskbar.cpp \
    widgets/taskbarmenubutton.cpp \
    widgets/subwindowtitlebar.cpp \
    builtin/connectionbrowser/connectionbrowser.cpp \
    builtin/connectionbrowser/connectionitem.cpp \
    builtin/connectionbrowser/connectionlistwidget.cpp \
    core/moduleloader.cpp \
    builtin/modulemanager/modulemanager.cpp \
    core/outputlog.cpp \
    builtin/consolelog/consolelog.cpp
    widgets/windowarea.cpp

HEADERS  += \
    api/pandemicmodulebase.h \
    api/pandemicmodule.h \
    api/pandemicwindow.h \
    core/applicationbase.h \
    core/application.h \
    gui/mainwindow.h \
    server/connection.h \
    server/server.h \
    widgets/taskbar.h \
    widgets/taskbarmenubutton.h \
    widgets/subwindowtitlebar.h \
    builtin/connectionbrowser/connectionbrowser.h \
    builtin/connectionbrowser/connectionitem.h \
    builtin/connectionbrowser/connectionlistwidget.h \
    core/moduleloader.h \
    builtin/modulemanager/modulemanager.h \
    core/outputlog.h \
    builtin/consolelog/consolelog.h \
    api/moduleinterface.h
    widgets/windowarea.h

RESOURCES += res/resources.qrc
