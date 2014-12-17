#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDebug>
#include <QDateTime>
#include <QHostAddress>
#include <QTcpSocket>
#include <QObject>
#include <QString>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QTcpSocket *socket);

    int lastPing();

    QString name(){ return _name; }
    void setName(QString name){ _name = name; emit nameChanged(name); }
    QString ipAddress(){ return _socket->peerAddress().toString(); }

private:
    qint64 _pingTime;
    QTcpSocket *_socket;
    QString _name;

signals:
    void finished();
    void nameChanged(QString);

public slots:
    void readyRead();
    void finish();
};

#endif // CONNECTION_H
