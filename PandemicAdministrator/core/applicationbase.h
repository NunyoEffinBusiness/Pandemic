#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H

#include <QDebug>
#include <QApplication>
#include <QFontDatabase>
#include <QStringList>
#include <QObject>
#include "outputlog.h"
#include "../gui/mainwindow.h"
#include "../server/connection.h"
#include "../server/server.h"

class ApplicationBase : public QApplication
{
    Q_OBJECT
public:
    explicit ApplicationBase(int argc, char *argv[]);
    OutputLog* outputLog(){ return _log; }
    Server* server(){ return _server; }

    bool initialize();

private:


protected:
    MainWindow *_mainWindow;
    OutputLog *_log;
    Server *_server;

signals:

public slots:
    void openConnection(Connection *connection);

};

#endif // APPLICATIONBASE_H
