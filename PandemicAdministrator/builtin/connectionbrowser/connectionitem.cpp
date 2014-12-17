#include "connectionitem.h"

ConnectionItem::ConnectionItem(int col, Connection *conn) :
    QTableWidgetItem()
{
    _conn = conn;
    _col = col;

    setFlags(flags() & ~Qt::ItemIsEditable);

    if(col == 0)
    {
        setText(_conn->name());
        connect(_conn, SIGNAL(nameChanged(QString)), this, SLOT(setText(QString)));
        setFlags(flags() & ~Qt::ItemIsEditable);
    }
    else if(col == 1)
    {
        setText(_conn->ipAddress());
    }

}

void ConnectionItem::setText(const QString &text)
{
    QTableWidgetItem::setText(text);
}
