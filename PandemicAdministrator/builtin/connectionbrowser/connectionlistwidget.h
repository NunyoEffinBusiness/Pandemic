#ifndef CONNECTIONLISTWIDGET_H
#define CONNECTIONLISTWIDGET_H

#include <QHeaderView>
#include <QList>
#include <QMap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "../../server/connection.h"
#include "connectionitem.h"

class ConnectionListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ConnectionListWidget();

private:
    QList<Connection *> _connList;

signals:

private slots:
    void openConnection(QTableWidgetItem *item);

public slots:
    void updateConnectionList(QList<Connection *> connList);

};

#endif // CONNECTIONLISTWIDGET_H
