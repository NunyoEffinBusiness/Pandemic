#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QTableWidgetItem>
#include <QObject>
#include "../../server/connection.h"

class ConnectionItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
    explicit ConnectionItem(int col, Connection *conn);

    Connection* connection(){ return _conn; }

private:
    Connection *_conn;
    int _col;

signals:

public slots:
    void setText(const QString &text);

};

#endif // CONNECTIONITEM_H
