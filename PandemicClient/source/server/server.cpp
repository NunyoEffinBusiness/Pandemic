#include "server.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    _socket = 0;
    _running = false;
    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(ping()));

    createSocket();
}

void Server::setHost(QString ip, quint16 port)
{
    _ip = ip;
    _port = port;
}

void Server::createSocket()
{
    qDebug() << "Creating the socket...";

    qDebug() << "Checking the socket...";
    if(_socket)
        deleteSocket();

    qDebug() << "Creating socket instance...";
    _socket = new Socket(this);

    qDebug() << "Connecting the socket signals";
    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Socket Created!";
}

void Server::deleteSocket()
{
    qDebug() << "Deleting the socket...";

    qDebug() << "Stopping the timer...";
    _timer->stop();

    qDebug() << "Checking the socket...";
    if(_socket)
    {
        qDebug() << "Disconnecting the socket...";
        try
        {
            disconnect(_socket, SIGNAL(connected()), this, SLOT(connected()));
            disconnect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
            disconnect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
            disconnect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        }
        catch(...){qDebug() << "Error disconnecting the socket!";}
        try { qDebug() << "Closing the socket..."; _socket->close(); } catch(...){qDebug() << "Error closing the socket!";}
        try { qDebug() << "Deleting the socket!"; _socket->deleteLater(); delete _socket; } catch(...){ qDebug() << "Error deleting the socket!"; }
    }

    qDebug() << "Socket Deleted!";
    _socket = 0;
}

void Server::start()
{
    qDebug() << "Starting Server...";
    _running = true;
    qDebug() << "Socket Created!";

    _socket->close();
    try
    {
        qDebug() << "Connecting to the host...";
        _socket->connectToHost(_ip, _port);
        qDebug() << "Connecting...";
    }catch(...){qDebug() << "Error connecting to the host!";}
}

void Server::stop()
{
    qDebug() << "Stopping Server...";
    _running = false;
    deleteSocket();
}

void Server::connected()
{
    qDebug() << "Connected to host!";
    _timer->start(1000);
    _connected = true;
}

void Server::disconnected()
{
    qDebug() << "Disconnected from host!";
    if(_running) start();
    _connected = false;
}

void Server::error(QAbstractSocket::SocketError error)
{
    qDebug() << "Server Error..." << error;
    if(error == QAbstractSocket::ConnectionRefusedError ||
       error == QAbstractSocket::HostNotFoundError ||
       error == QAbstractSocket::NetworkError)
        start();
}

void Server::readyRead()
{
    qDebug() << "Ready to read data...";
}

void Server::ping()
{
    if(_running)
        if(_socket)
            try
            {
                if(_socket->state() == QAbstractSocket::ConnectedState)
                {
                    qDebug() << "Pinging...";
                    send(QByteArray("%"));
                }
            } catch(...){}
}

void Server::send(QByteArray data)
{
    try{
        _timer->stop();
        _timer->start(1000);
        _socket->write(data);
    }catch(...){
        if(_running)
            start();
    }
}
