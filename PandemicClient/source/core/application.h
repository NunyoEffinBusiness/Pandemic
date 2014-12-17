#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "../server/server.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);

    bool initialize();

private:
    Server *_server;

signals:

public slots:

};

#endif // APPLICATION_H
