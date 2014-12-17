#ifndef SERVER_H
#define SERVER_H

#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QList>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "connection.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

private:
    QList<Connection *> _connList;
    QTcpServer *_server;
    QTimer *_timer;

    void createServer();

signals:
    void connectionListUpdated(QList<Connection *>);

public slots:
    bool newConnections();
    void update();

};

#endif // SERVER_H
