#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QObject>
#include <QTimer>
#include "socket.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    void setHost(QString ip, quint16 port);

private:
    bool _running, _connected;
    QString _ip;
    quint16 _port;
    Socket *_socket;
    QTimer *_timer;

    void createSocket();
    void deleteSocket();

signals:

public slots:
    void start();
    void stop();
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError error);
    void readyRead();
    void send(QByteArray data);
    void ping();
};

#endif // SERVER_H
