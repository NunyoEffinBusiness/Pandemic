#include "server.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));

    createServer();
    _timer->start(1000);
    qDebug() << "Starting server...";
}

void Server::createServer()
{
    _server = new QTcpServer();
    _server->listen(QHostAddress::Any, 4456);
}

bool Server::newConnections()
{
    bool updated = false;
    while(_server->hasPendingConnections())
    {
        qDebug() << "New Connection!";
        _connList.append(new Connection(_server->nextPendingConnection()));
        updated = true;
    }
    return updated;
}

void Server::update()
{
    bool updated = newConnections();


    Connection *conn;
    for(int i = 0; i < _connList.length(); i++)
    {
        conn = _connList.at(i);
        if(conn->lastPing() >= 5000)
        {
            _connList.removeAll(conn);
            conn->finish();
            conn->deleteLater();
            i--;
            updated = true;
            qDebug() << "Removed Connection";
        }
    }

    if(updated) emit connectionListUpdated(_connList);

}
