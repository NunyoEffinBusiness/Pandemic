#include "connection.h"

Connection::Connection(QTcpSocket *socket) :
    QObject()
{
    _socket = socket;

    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    _pingTime = QDateTime::currentMSecsSinceEpoch();
}

int Connection::lastPing() { return QDateTime::currentMSecsSinceEpoch() - _pingTime; }

void Connection::readyRead()
{
    _pingTime = QDateTime::currentMSecsSinceEpoch();
    QByteArray data = _socket->readAll();

    if(QString(data.data()) == "%")
        qDebug() << "Ping received!";
}

void Connection::finish()
{
    try { _socket->close(); } catch(...){}
    try { _socket->deleteLater(); } catch(...){}
    try { delete _socket; } catch(...){}

    emit finished();
}
